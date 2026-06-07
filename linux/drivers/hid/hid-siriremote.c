#include <linux/hid.h>
#include <linux/input/mt.h>

#include "hid-ids.h"

#define TOUCH_MAX_FINGERS 2

#define GEN1_TOUCH_X_MIN 2278
#define GEN1_TOUCH_X_MAX 3914
#define GEN1_TOUCH_Y_MIN 3022
#define GEN1_TOUCH_Y_MAX 4710
#define GEN1_TOUCH_RES 45

#define GEN2_TOUCH_X_MIN 3056
#define GEN2_TOUCH_X_MAX 4414
#define GEN2_TOUCH_Y_MIN 3058
#define GEN2_TOUCH_Y_MAX 4408
#define GEN2_TOUCH_RES 15

static const __u8 hid_custom_report_desc[] = {0x05, 0x01, 0x09, 0x00, 0xA1, 0x01, 0x06, 0x00, 0xFF, 0x75, 0x08, 0x85, 0xF0, 0x95, 0x01, 0xB2, 0x02, 0x01, 0x85, 0xFA,
                                              0x95, 0x63, 0x82, 0x03, 0x01, 0x85, 0xFB, 0x95, 0x02, 0x82, 0x03, 0x01, 0x85, 0xFC, 0x95, 0x12, 0x82, 0x03, 0x01, 0xC0};

struct siriremote_config {
  u8 hid_report_id_keys, hid_report_id_touch, hid_report_id_audio;

  bool is_gen_1;

  const struct siriremote_key_map {
    u16 keycode;
    u16 mask;
  } *key_map;

  u16 button_mouse_mask;
};

struct siriremote_drvdata {
  struct hid_device *hdev;
  struct input_dev *idev_keys, *idev_touch;

  struct siriremote_config config;
};

static const struct siriremote_config siriremote_config_gen1 = {
    .hid_report_id_audio = 0xfc,
    .hid_report_id_keys = 0xfc,
    .hid_report_id_touch = 0xfc,

    .is_gen_1 = true,

    .key_map =
        (struct siriremote_key_map[]){
            {KEY_PVR, 0x01},          // Home
            {KEY_VOLUMEUP, 0x02},     // Volume Up
            {KEY_VOLUMEDOWN, 0x04},   // Volume Down
            {KEY_PLAYPAUSE, 0x08},    // Play/Pause
            {KEY_VOICECOMMAND, 0x10}, // Siri/Mic
            {KEY_MENU, 0x20},         // Menu
            // {BTN_MOUSE, 0x80},        // Touchpad
            {},
        },
    .button_mouse_mask = 0x80,
};

static const struct siriremote_config siriremote_config_gen2 = {
    .hid_report_id_audio = 0xfa,
    .hid_report_id_keys = 0xfb,
    .hid_report_id_touch = 0xfc,

    .is_gen_1 = false,

    .key_map =
        (struct siriremote_key_map[]){
            {KEY_PVR, 0x0100},        // Home
            {KEY_VOLUMEUP, 0x0200},   // Volume Up
            {KEY_VOLUMEDOWN, 0x0400}, // Volume Down
            // {BTN_MOUSE, 0x0800},        // Touchpad
            {KEY_SCREENSAVER, 0x1000},  // Power
            {KEY_VOICECOMMAND, 0x2000}, // Siri/Mic
            {KEY_BACK, 0x4000},         // Back
            {KEY_MUTE, 0x8000},         // Mute
            {KEY_PLAYPAUSE, 0x01},      // Play/Pause
            {KEY_UP, 0x02},             // Up
            {KEY_RIGHT, 0x04},          // Right
            {KEY_DOWN, 0x08},           // Down
            {KEY_LEFT, 0x10},           // Left
            {},
        },
    .button_mouse_mask = 0x0800,
};

static const struct siriremote_config siriremote_config_gen3 = siriremote_config_gen2;

static void siri_remote_idev_keys_config(struct siriremote_drvdata *drvdata) {
  const struct siriremote_key_map *key;
  for (key = drvdata->config.key_map; key->keycode; key++)
    input_set_capability(drvdata->idev_keys, EV_KEY, key->keycode);
}

static void siri_remote_idev_keys_report(struct siriremote_drvdata *drvdata, u16 keys) {
  const struct siriremote_key_map *key;
  for (key = drvdata->config.key_map; key->keycode; key++) {
    input_report_key(drvdata->idev_keys, key->keycode, keys & key->mask);
  }
  input_sync(drvdata->idev_keys);

  // touchpad separately
  input_report_key(drvdata->idev_touch, BTN_MOUSE, keys & drvdata->config.button_mouse_mask);
  input_sync(drvdata->idev_touch);
}

static void siri_remote_idev_touch_config(struct siriremote_drvdata *drvdata) {
  struct input_dev *idev = drvdata->idev_touch;
  input_mt_init_slots(idev, 2, INPUT_MT_POINTER | INPUT_MT_DROP_UNUSED | INPUT_MT_TRACK);

  input_set_abs_params(idev, ABS_MT_PRESSURE, 0, 255, 0, 0);
  input_set_abs_params(idev, ABS_MT_ORIENTATION, 0, 7, 0, 0);
  input_set_abs_params(idev, ABS_MT_TOUCH_MAJOR, 0, 255, 0, 0);
  input_set_abs_params(idev, ABS_MT_TOUCH_MINOR, 0, 255, 0, 0);

  if (drvdata->config.is_gen_1) {
    input_set_abs_params(idev, ABS_MT_POSITION_X, GEN1_TOUCH_X_MIN, GEN1_TOUCH_X_MAX, 0, 0);
    input_set_abs_params(idev, ABS_MT_POSITION_Y, -GEN1_TOUCH_Y_MAX, -GEN1_TOUCH_Y_MIN, 0, 0);

    input_abs_set_res(idev, ABS_MT_POSITION_X, GEN1_TOUCH_RES);
    input_abs_set_res(idev, ABS_MT_POSITION_Y, GEN1_TOUCH_RES);
  } else {
    input_set_abs_params(idev, ABS_MT_POSITION_X, GEN2_TOUCH_X_MIN, GEN2_TOUCH_X_MAX, 0, 0);
    input_set_abs_params(idev, ABS_MT_POSITION_Y, -GEN2_TOUCH_Y_MAX, -GEN2_TOUCH_Y_MIN, 0, 0);

    input_abs_set_res(idev, ABS_MT_POSITION_X, GEN2_TOUCH_RES);
    input_abs_set_res(idev, ABS_MT_POSITION_Y, GEN2_TOUCH_RES);
  }

  input_set_capability(idev, EV_KEY, BTN_MOUSE);
}

static void siri_remote_idev_touch_report(struct siriremote_drvdata *drvdata, u8 *rd, int size) {
  // gen 1 contains keys in same packet, remove it
  if (drvdata->config.is_gen_1) {
    rd += 2;
    size -= 2;
  }

  if (rd[0] != 0x32 || (size - 4) % 7 != 0)
    return;

  u16 timestamp = rd[1] | (rd[2] << 8);

  int num_fingers = (size - 4) / 7;
  if (num_fingers > TOUCH_MAX_FINGERS)
    return;

  // remove header
  rd += 4;
  size -= 4;

  struct input_dev *idev = drvdata->idev_touch;

  for (int i = 0; i < num_fingers && i < 2; i++) {
    u8 *fing = &rd[i * 7];

    int x = fing[0] | ((fing[1] & 0x0f) << 8);
    int y = ((fing[1] & 0xf0) >> 4) | (fing[2] << 4);
    int maj = fing[3];
    int pressure = fing[4];
    int min = fing[5];
    int orientation = fing[6] >> 5;
    // TODO: use id from (fing[6] >> 3) & 1?

    if (x < 0x800)
      x += 0x1000;
    if (y < 0x800)
      y += 0x1000;

    bool down = pressure > 0;

    input_mt_slot(idev, i);
    input_mt_report_slot_state(idev, MT_TOOL_FINGER, down);

    if (down) {
      input_report_abs(idev, ABS_MT_POSITION_X, x);
      input_report_abs(idev, ABS_MT_POSITION_Y, -y); // invert y
      input_report_abs(idev, ABS_MT_TOUCH_MAJOR, maj);
      input_report_abs(idev, ABS_MT_TOUCH_MINOR, min);
      input_report_abs(idev, ABS_MT_PRESSURE, pressure);
      input_report_abs(idev, ABS_MT_ORIENTATION, orientation);
    }
  }

  // release remaining fingers
  for (int i = num_fingers; i < TOUCH_MAX_FINGERS; i++) {
    input_mt_slot(idev, i);
    input_mt_report_slot_state(idev, MT_TOOL_FINGER, false);
  }

  input_mt_sync_frame(idev);
  input_sync(idev);
}

static int siri_remote_idev_create(struct siriremote_drvdata *drvdata, struct input_dev **dest, u8 id) {
  struct hid_device *hdev = drvdata->hdev;

  struct input_dev *idev;
  int ret;

  idev = devm_input_allocate_device(&hdev->dev);
  if (!idev)
    return -ENOMEM;

  idev->id.bustype = hdev->bus;
  idev->id.vendor = hdev->vendor;
  idev->id.product = hdev->product;
  idev->id.version = hdev->version;
  idev->name = hdev->name;
  idev->phys = hdev->phys;
  idev->uniq = hdev->uniq;

  ret = input_register_device(idev);
  if (ret)
    return ret;

  input_set_drvdata(idev, drvdata);
  *dest = idev;

  return 0;
}

static int siri_remote_raw_event(struct hid_device *hdev, struct hid_report *report, u8 *rd, int size) {
  // print_hex_dump(KERN_INFO, "hid-siriremote dump ", DUMP_PREFIX_OFFSET, 16, 1, rd, size, true);

  struct siriremote_drvdata *drvdata = hid_get_drvdata(hdev);

  u8 report_id = rd[0];
  rd++;
  size--;

  if (report_id == drvdata->config.hid_report_id_keys) {
    siri_remote_idev_keys_report(drvdata, (rd[0] << 8) + rd[1]);
  }

  if (report_id == drvdata->config.hid_report_id_touch) {
    siri_remote_idev_touch_report(drvdata, rd, size);
  }

  if (report_id == drvdata->config.hid_report_id_audio) {
    // TODO: audio stuff
  }

  return 0;
}

static int siri_remote_magic_byte(struct hid_device *hdev) {
  __u8 buf[] = {0xf0, 0xaf};
  return hid_hw_raw_request(hdev, buf[0], buf, 2, HID_FEATURE_REPORT, HID_REQ_SET_REPORT);
}

static void siri_remote_remove_keys(struct siriremote_drvdata *drvdata) {
  input_unregister_device(drvdata->idev_keys);
}

static void siri_remote_remove_touch(struct siriremote_drvdata *drvdata) {
  input_unregister_device(drvdata->idev_touch);
}

static int siri_remote_probe(struct hid_device *hdev, const struct hid_device_id *id) {
  int ret;
  struct siriremote_drvdata *drvdata;

  drvdata = devm_kzalloc(&hdev->dev, sizeof(struct siriremote_drvdata), GFP_KERNEL);
  if (!drvdata) {
    hid_err(hdev, "siriremote drvdata allocation failed\n");
    return -ENOMEM;
  }

  drvdata->hdev = hdev;
  hid_set_drvdata(hdev, drvdata);

  ret = hid_parse(hdev);
  if (ret) {
    hid_err(hdev, "siriremote hid parse failed\n");
    return ret;
  }

  ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
  if (ret) {
    hid_err(hdev, "siriremote hw start failed\n");
    return ret;
  }

  switch (hdev->product) {
  case BT_DEVICE_ID_APPLE_SIRI_REMOTE_A1513:
  case BT_DEVICE_ID_APPLE_SIRI_REMOTE_A1962:
    drvdata->config = siriremote_config_gen1;
    break;
  case BT_DEVICE_ID_APPLE_SIRI_REMOTE_A2540:
    drvdata->config = siriremote_config_gen2;
    break;
  case BT_DEVICE_ID_APPLE_SIRI_REMOTE_A2854:
    drvdata->config = siriremote_config_gen3;
    break;
  default:
    ret = -ENODEV;
    hid_err(hdev, "siriremote unknown device\n");
    goto err_stop_hw;
  }

  ret = siri_remote_idev_create(drvdata, &drvdata->idev_keys, 0);
  if (ret) {
    hid_err(hdev, "siriremote keys input device creation failed\n");
    goto err_stop_hw;
  }

  ret = siri_remote_idev_create(drvdata, &drvdata->idev_touch, 1);
  if (ret) {
    hid_err(hdev, "siriremote touch input device creation failed\n");
    goto err_cleanup_keys;
  }

  siri_remote_idev_keys_config(drvdata);
  siri_remote_idev_touch_config(drvdata);

  hid_device_io_start(hdev);

  // TODO: not always receiving first report, this somehow takes too long?
  ret = siri_remote_magic_byte(hdev);
  if (ret < 0) {
    hid_err(hdev, "siriremote magic byte failed\n");
    goto err_cleanup_touch;
  }

  return 0;
err_cleanup_touch:
  siri_remote_remove_touch(drvdata);
err_cleanup_keys:
  siri_remote_remove_keys(drvdata);
err_stop_hw:
  hid_hw_stop(hdev);
  return ret;
}

static void siri_remote_remove(struct hid_device *hdev) {
  struct siriremote_drvdata *drvdata = hid_get_drvdata(hdev);

  siri_remote_remove_keys(drvdata);
  siri_remote_remove_touch(drvdata);

  hid_hw_stop(hdev);
}

static const __u8 *siri_remote_report_fixup(struct hid_device *hdev, __u8 *buf, unsigned int *size) {
  *size = sizeof(hid_custom_report_desc);
  return hid_custom_report_desc;
}

static const struct hid_device_id siri_remote_devices[] = {
    {HID_BLUETOOTH_DEVICE(BT_VENDOR_ID_APPLE, BT_DEVICE_ID_APPLE_SIRI_REMOTE_A1513)},
    {HID_BLUETOOTH_DEVICE(BT_VENDOR_ID_APPLE, BT_DEVICE_ID_APPLE_SIRI_REMOTE_A1962)},
    {HID_BLUETOOTH_DEVICE(BT_VENDOR_ID_APPLE, BT_DEVICE_ID_APPLE_SIRI_REMOTE_A2540)},
    {HID_BLUETOOTH_DEVICE(BT_VENDOR_ID_APPLE, BT_DEVICE_ID_APPLE_SIRI_REMOTE_A2854)},
    {},
};

MODULE_DEVICE_TABLE(hid, siri_remote_devices);

static struct hid_driver siri_remote_driver = {
    .name = "hid-siriremote",
    .id_table = siri_remote_devices,
    .probe = siri_remote_probe,
    .remove = siri_remote_remove,
    .raw_event = siri_remote_raw_event,
    .report_fixup = siri_remote_report_fixup,
};

module_hid_driver(siri_remote_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yanndroid");
MODULE_DESCRIPTION("HID driver for Apple Siri Remote");
MODULE_VERSION("0.1");
