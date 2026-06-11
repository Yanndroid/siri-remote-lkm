#include "pipewire/stream.h"
#include "spa/param/audio/raw.h"
#include <fcntl.h>
#include <opus/opus.h>
#include <pipewire-0.3/pipewire/pipewire.h>
#include <pipewire-0.3/pipewire/properties.h>
#include <spa/param/audio/format-utils.h>
#include <spa/pod/builder.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#define OPUS_FRAME_SIZE 95

#define SAMPLE_RATE 48000
#define BYTES_PER_SAMPLE 2
#define CHANNELS 1

#define PCM_FRAME_SIZE 960

struct app_data {
  int fd;
  OpusDecoder *decoder;
  struct pw_stream *stream;
  struct pw_main_loop *pw_loop;
};

static int audio_quit(struct spa_loop *loop, bool async, uint32_t seq, const void *data, size_t size, void *user_data) {
  pw_main_loop_quit(((struct app_data *)user_data)->pw_loop);
  return 0;
}

static void audio_task(void *data) {
  struct app_data *app = data;
  struct pw_buffer *pw_buf = pw_stream_dequeue_buffer(app->stream);
  if (!pw_buf)
    return;

  struct spa_data *spa_data = &pw_buf->buffer->datas[0];

  void *pcm_buf = spa_data->data;
  uint32_t pcm_buf_size = spa_data->maxsize;

  if (!pcm_buf)
    goto audio_task_exit;

  uint8_t opus_buf[OPUS_FRAME_SIZE];
  ssize_t opus_read_size = read(app->fd, opus_buf, OPUS_FRAME_SIZE);

  if (opus_read_size == -1) { // siriremote disconnected
    pw_loop_invoke(pw_main_loop_get_loop(app->pw_loop), audio_quit, 0, NULL, 0, true, app);
    goto audio_task_exit;
  }

  if (opus_read_size != OPUS_FRAME_SIZE) {
    fprintf(stderr, "read error: %d", (int)opus_read_size);
    goto audio_task_exit;
  }

  memset(pcm_buf, 0, pcm_buf_size);

  int pcm_frame_size = opus_decode(app->decoder, &opus_buf[1], opus_buf[0], pcm_buf, PCM_FRAME_SIZE, 0);
  if (pcm_frame_size < 0) {
    fprintf(stderr, "decode error: %s\n", opus_strerror(pcm_frame_size));
    goto audio_task_exit;
  }
  uint32_t pcm_decode_size = pcm_frame_size * CHANNELS * BYTES_PER_SAMPLE;

  spa_data->chunk->offset = 0;
  spa_data->chunk->stride = CHANNELS * BYTES_PER_SAMPLE;
  spa_data->chunk->size = pcm_decode_size;

audio_task_exit:
  pw_stream_queue_buffer(app->stream, pw_buf);
}

struct app_data app = {0};

static void main_exit(int signum) {
  pw_main_loop_quit(app.pw_loop);
}

static void signals_init() {
  struct sigaction sa = {0};
  sa.sa_handler = main_exit;
  sigaction(SIGTERM, &sa, NULL);
  sigaction(SIGINT, &sa, NULL);
}

int main(int argc, char *argv[]) {
  signals_init();

  if (argc != 2) {
    printf("Usage: %s <device>\n", argv[0]);
    return -1;
  }

  char *device = argv[1];
  printf("Start siriremote audio decoder: %s\n", device);

  app.fd = open(device, O_RDONLY);
  if (app.fd < 0) {
    fprintf(stderr, "Failed to open device: %s\n", device);
    return -1;
  }

  int err;
  app.decoder = opus_decoder_create(SAMPLE_RATE, CHANNELS, &err);
  if (err != OPUS_OK) {
    fprintf(stderr, "Failed to create Opus decoder: %s\n", opus_strerror(err));
    close(app.fd);
    return -1;
  }

  pw_init(&argc, &argv);
  app.pw_loop = pw_main_loop_new(NULL);

  struct pw_properties *props = pw_properties_new(PW_KEY_MEDIA_TYPE, "Audio", PW_KEY_MEDIA_CATEGORY, "Playback", PW_KEY_MEDIA_CLASS, "Audio/Source", PW_KEY_MEDIA_ROLE,
                                                  "Communication", PW_KEY_NODE_NAME, "Siri Remote Mic", PW_KEY_AUDIO_CHANNELS, "1", NULL);
  struct pw_stream_events stream_events = {.process = audio_task};
  app.stream = pw_stream_new_simple(pw_main_loop_get_loop(app.pw_loop), "siriremote-mic", props, &stream_events, &app);

  uint8_t pod_buffer[1024];
  struct spa_pod_builder builder = SPA_POD_BUILDER_INIT(pod_buffer, sizeof(pod_buffer));
  struct spa_audio_info_raw info = {.format = SPA_AUDIO_FORMAT_S16_LE, .rate = SAMPLE_RATE, .channels = CHANNELS, .position = {SPA_AUDIO_CHANNEL_MONO}};
  const struct spa_pod *params = spa_format_audio_raw_build(&builder, SPA_PARAM_EnumFormat, &info);

  pw_stream_connect(app.stream, PW_DIRECTION_OUTPUT, PW_ID_ANY, PW_STREAM_FLAG_AUTOCONNECT | PW_STREAM_FLAG_MAP_BUFFERS | PW_STREAM_FLAG_RT_PROCESS, &params, 1);

  pw_main_loop_run(app.pw_loop);

  printf("Exit siriremote audio decoder: %s\n", device);

  pw_stream_destroy(app.stream);
  pw_main_loop_destroy(app.pw_loop);
  pw_deinit();
  opus_decoder_destroy(app.decoder);
  close(app.fd);

  return 0;
}