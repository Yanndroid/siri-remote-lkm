# Packets

The 1st gen remote uses `0xFC` report id for all packets and always includes the two bytes for key press status. The 2nd and 3rd gen uses `0xFA` for audio, `0xFB` for keys and `0xFC` for touchpad.

## Keys

### Gen 1

- Home: `0x00 0x01`
- Vol+: `0x00 0x02`
- Vol-: `0x00 0x04`
- Play/Pause: `0x00 0x08`
- Siri: `0x00 0x10`
- Menu: `0x00 0x20`
- Touchpad: `0x00 0x80`

### Gen 2 & 3

- Home: `0x01 0x00`
- Vol+: `0x02 0x00`
- Vol-: `0x04 0x00`
- Touchpad: `0x08 0x00`
- Power: `0x10 0x00`
- Siri: `0x20 0x00`
- Back: `0x40 0x00`
- Mute: `0x80 0x00`
- Play/Pause: `0x00 0x01`
- Up: `0x00 0x02`
- Right: `0x00 0x04`
- Down: `0x00 0x08`
- Left: `0x00 0x10`

## Touchpad

Packet size is 13/21 bytes (gen 1) and 11/18 bytes (gen 2 & 3) depending on finger count.

- Report ID (1): always 0xFC
- Keys (0/2): gen 1 only (see [Keys](#keys))
- Timestamp (2): increasing number, starts at 0
- Status (1): bits 0x0F for 1st finger, 0xF0 for 2nd finger
  - b0: tip of finger (larger touch surface resets this bit)
  - b1: unknown
  - b2: previously on edge (gen 1 only)
  - b3: edge detection (gen 1 only)
- 1st finger (7): see [Finger](#finger)
- 2nd finder (7): optional, see [Finger](#finger)

### Finger

- Low X (1): lower 8 bits for X coordinate
- High Y | Low X (1): bits 0x0F higher 4 bits for X coord | bits 0xF0 lower 4 bits for Y coord
- High Y (1): higher 8 bits for Y coordinate
- Major (1): finger ellipse major
- Pressure (1)
- Minor (1): finger ellipse minor
- Status (1):
  - b0-b3: unknown
  - b4: finger id (can alternate)
  - b5-b7: orientation

## Audio

- Report ID (1): 0xFC (gen 1) or 0xFC (gen 2 & 3)
- Keys (0/2): gen 1 only (see [Keys](#keys))
- Unknown (2)
- Frame number (2)
- Opus frame size (1)
- Opus frame (94): Can be decoded to PCM 48kHz, 2BpS, 1Ch

The 1st gen remote advertises an insufficient MTU size of 23 bytes and unlike Windows and MacOS, Linux (bluez) actually meets the official bluetooth protocol specs and truncates the packet to the MTU size. So even though the system receives the full frame, our driver only receives the first part of every frame. This can be patched but will unlikely ever go upstream (see this [issue](https://github.com/bluez/bluez/issues/576)).

Another problem that I have encountered, is that after exactly 75 packets, a lot of packets are being dropped and I haven't found a solution for this yet.

## Motion

The 1st gen remote has a gyro and accelerometer. I haven't explored this part yet.
