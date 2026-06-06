# Documentation

Everything I have found out so far about the remotes is here.

- [GATT](./gatt_attributes.md)
- [HID](./hid_report_descriptor.md)
- [Packets](./packtes.md)

## Custom HID report descriptor

In order to make the remotes work properly, I'm using a custom HID report descriptor.

`05 01 09 00 A1 01 06 00 FF 75 08 85 F0 95 01 B2 02 01 85 FA 95 63 82 03 01 85 FB 95 02 82 03 01 85 FC 95 12 82 03 01 C0`

```
0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
0x09, 0x00,        // Usage (Undefined)
0xA1, 0x01,        // Collection (Application)
0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
0x75, 0x08,        //   Report Size (8)
0x85, 0xF0,        //   Report ID (0xF0)
0x95, 0x01,        //   Report Count (1)
0xB2, 0x02, 0x01,  //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile,Buffered Bytes)
0x85, 0xFA,        //   Report ID (0xFA)
0x95, 0x63,        //   Report Count (99)
0x82, 0x03, 0x01,  //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Buffered Bytes)
0x85, 0xFB,        //   Report ID (0xFB)
0x95, 0x02,        //   Report Count (2)
0x82, 0x03, 0x01,  //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Buffered Bytes)
0x85, 0xFC,        //   Report ID (0xFC)
0x95, 0x12,        //   Report Count (18)
0x82, 0x03, 0x01,  //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Buffered Bytes)
0xC0,              // End Collection
```
