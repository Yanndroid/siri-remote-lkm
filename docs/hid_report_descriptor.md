# HID Report Descriptors

Linux: `hexdump -C "/sys/bus/hid/devices/.../report_descriptor"`

## Gen 1

### Linux

`06 00 ff 09 0b a1 01 09 01 85 fc 75 08 95 14 82 03 01 09 02 85 f0 75 08 95 d0 b2 02 01 c0`

```
0x06, 0x00, 0xFF, // Usage Page (Vendor Defined 0xFF00)
0x09, 0x0B, // Usage (0x0B)
0xA1, 0x01, // Collection (Application)
0x09, 0x01, // Usage (0x01)
0x85, 0xFC, // Report ID (0xFC)
0x75, 0x08, // Report Size (8)
0x95, 0x14, // Report Count (20)
0x82, 0x03, 0x01, // Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Buffered Bytes)
0x09, 0x02, // Usage (0x02)
0x85, 0xF0, // Report ID (0xF0)
0x75, 0x08, // Report Size (8)
0x95, 0xD0, // Report Count (208)
0xB2, 0x02, 0x01, // Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile,Buffered Bytes)
0xC0, // End Collection
```

### MacOS

`05 20 09 e0 a1 01 09 e0 85 ff 76 80 06 95 01 82 03 01 09 e0 85 ff 76 80 06 95 01 b2 02 01 c0`

```
0x05, 0x20, // Usage Page (0x20)
0x09, 0xE0, // Usage (0xE0)
0xA1, 0x01, // Collection (Application)
0x09, 0xE0, // Usage (0xE0)
0x85, 0xFF, // Report ID (0xFF)
0x76, 0x80, 0x06, // Report Size (1664)
0x95, 0x01, // Report Count (1)
0x82, 0x03, 0x01, // Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Buffered Bytes)
0x09, 0xE0, // Usage (0xE0)
0x85, 0xFF, // Report ID (0xFF)
0x76, 0x80, 0x06, // Report Size (1664)
0x95, 0x01, // Report Count (1)
0xB2, 0x02, 0x01, // Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile,Buffered Bytes)
0xC0, // End Collection
```

## Gen 2

### Linux

`06 00 ff 09 0b a1 01 06 00 ff 09 0b 15 00 26 ff 00 75 32 96 06 00 85 b8 b2 01 00 85 04 75 08 96 11 00 82 22 01 c0`

```
0x06, 0x00, 0xFF, // Usage Page (Vendor Defined 0xFF00)
0x09, 0x0B, // Usage (0x0B)
0xA1, 0x01, // Collection (Application)
0x06, 0x00, 0xFF, // Usage Page (Vendor Defined 0xFF00)
0x09, 0x0B, // Usage (0x0B)
0x15, 0x00, // Logical Minimum (0)
0x26, 0xFF, 0x00, // Logical Maximum (255)
0x75, 0x32, // Report Size (50)
0x96, 0x06, 0x00, // Report Count (6)
0x85, 0xB8, // Report ID (0xB8)
0xB2, 0x01, 0x00, // Feature (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile,Bit Field)
0x85, 0x04, // Report ID (0x04)
0x75, 0x08, // Report Size (8)
0x96, 0x11, 0x00, // Report Count (17)
0x82, 0x22, 0x01, // Input (Data,Var,Abs,No Wrap,Linear,No Preferred State,No Null Position,Buffered Bytes)
0xC0, // End Collection
```

### MacOS

TODO

## Gen 3

Most likely identical to [Gen 2](#gen-2).
