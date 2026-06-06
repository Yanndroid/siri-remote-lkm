# GATT Attributes

Commands

```
bluetoothctl
> list-attributes
> select-attribute /org/bluez/hci0/dev_.../service00../char00../desc00..
> read
```

## Gen 1

### HID

```
Primary Service (Handle 0x0015)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0015
	00001812-0000-1000-8000-00805f9b34fb
	Human Interface Device
Characteristic (Handle 0x0022)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0015/char0022
	00002a4d-0000-1000-8000-00805f9b34fb
	Report
Descriptor (Handle 0x0025)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0015/char0022/desc0025
	00002908-0000-1000-8000-00805f9b34fb
	Report Reference
Descriptor (Handle 0x0024)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0015/char0022/desc0024
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
Characteristic (Handle 0x001f)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0015/char001f
	00002a4d-0000-1000-8000-00805f9b34fb
	Report
Descriptor (Handle 0x0021)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0015/char001f/desc0021
	00002908-0000-1000-8000-00805f9b34fb
	Report Reference
Characteristic (Handle 0x001c)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0015/char001c
	00002a4d-0000-1000-8000-00805f9b34fb
	Report
Descriptor (Handle 0x001e)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0015/char001c/desc001e
	00002908-0000-1000-8000-00805f9b34fb
	Report Reference
Characteristic (Handle 0x001a)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0015/char001a
	00002a4c-0000-1000-8000-00805f9b34fb
	HID Control Point
Characteristic (Handle 0x0018)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0015/char0018
	00002a4b-0000-1000-8000-00805f9b34fb
	Report Map
Characteristic (Handle 0x0016)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0015/char0016
	00002a4a-0000-1000-8000-00805f9b34fb
	HID Information
```

#### Report Descriptors

- desc0025: fc 01 (input) -> keys, touch, audio
- desc0021: f1 03 (feature)
- desc001e: f0 03 (feature) -> magic byte 0xAF

### Battery

```
Primary Service (Handle 0x0026)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0026
	0000180f-0000-1000-8000-00805f9b34fb
	Battery Service
Characteristic (Handle 0x002a)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0026/char002a
	00002a1a-0000-1000-8000-00805f9b34fb
	Unknown
Descriptor (Handle 0x002c)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0026/char002a/desc002c
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
Characteristic (Handle 0x0027)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0026/char0027
	00002a19-0000-1000-8000-00805f9b34fb
	Battery Level
Descriptor (Handle 0x0029)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0026/char0027/desc0029
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
```

### Misc

```
Primary Service (Handle 0x0032)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0032
	8341f2b4-c013-4f04-8197-c4cdb42e26dc
	Vendor specific
Characteristic (Handle 0x0039)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0032/char0039
	30e69638-3752-4feb-a3aa-3226bcd05ace
	Vendor specific
Descriptor (Handle 0x003b)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0032/char0039/desc003b
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
Characteristic (Handle 0x0037)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0032/char0037
	2bdcaebe-8746-45df-a841-96b840980fb8
	Vendor specific
Characteristic (Handle 0x0035)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0032/char0035
	2bdcaebe-8746-45df-a841-96b840980fb7
	Vendor specific
Characteristic (Handle 0x0033)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0032/char0033
	9fbf120d-6301-42d9-8c58-25e699a21dbd
	Vendor specific
```

```
Primary Service (Handle 0x002d)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service002d
	0000181e-0000-1000-8000-00805f9b34fb
	Bond Management
Characteristic (Handle 0x0030)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service002d/char0030
	00002aa5-0000-1000-8000-00805f9b34fb
	Bond Management Feature
Characteristic (Handle 0x002e)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service002d/char002e
	00002aa4-0000-1000-8000-00805f9b34fb
	Bond Management Control Point
```

```
Primary Service (Handle 0x000a)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service000a
	0000180a-0000-1000-8000-00805f9b34fb
	Device Information
Characteristic (Handle 0x0013)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service000a/char0013
	00002a50-0000-1000-8000-00805f9b34fb
	PnP ID
Characteristic (Handle 0x0011)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service000a/char0011
	00002a29-0000-1000-8000-00805f9b34fb
	Manufacturer Name String
Characteristic (Handle 0x000f)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service000a/char000f
	00002a26-0000-1000-8000-00805f9b34fb
	Firmware Revision String
Characteristic (Handle 0x000d)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service000a/char000d
	00002a27-0000-1000-8000-00805f9b34fb
	Hardware Revision String
Characteristic (Handle 0x000b)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service000a/char000b
	00002a25-0000-1000-8000-00805f9b34fb
	Serial Number String
```

```
Primary Service (Handle 0x0006)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0006
	00001801-0000-1000-8000-00805f9b34fb
	Generic Attribute Profile
Characteristic (Handle 0x0007)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0006/char0007
	00002a05-0000-1000-8000-00805f9b34fb
	Service Changed
Descriptor (Handle 0x0009)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0006/char0007/desc0009
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
```

```
Primary Service (Handle 0x0001)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0001
	00001800-0000-1000-8000-00805f9b34fb
	Generic Access Profile
Characteristic (Handle 0x0004)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0001/char0004
	00002a01-0000-1000-8000-00805f9b34fb
	Appearance
Characteristic (Handle 0x0002)
	/org/bluez/hci0/dev_14_9D_99_48_D0_6F/service0001/char0002
	00002a00-0000-1000-8000-00805f9b34fb
	Device Name
```

## Gen 2

### HID

```
Primary Service (Handle 0x0033)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033
	00001812-0000-1000-8000-00805f9b34fb
	Human Interface Device
Characteristic (Handle 0x0056)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0056
	00002a4c-0000-1000-8000-00805f9b34fb
	HID Control Point
Characteristic (Handle 0x0054)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0054
	00002a4a-0000-1000-8000-00805f9b34fb
	HID Information
Characteristic (Handle 0x0052)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0052
	00002a4b-0000-1000-8000-00805f9b34fb
	Report Map
Characteristic (Handle 0x004f)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char004f
	00002a4d-0000-1000-8000-00805f9b34fb
	Report
Descriptor (Handle 0x0051)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char004f/desc0051
	00002908-0000-1000-8000-00805f9b34fb
	Report Reference
Characteristic (Handle 0x004c)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char004c
	00002a4d-0000-1000-8000-00805f9b34fb
	Report
Descriptor (Handle 0x004e)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char004c/desc004e
	00002908-0000-1000-8000-00805f9b34fb
	Report Reference
Characteristic (Handle 0x0048)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0048
	00002a4d-0000-1000-8000-00805f9b34fb
	Report
Descriptor (Handle 0x004b)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0048/desc004b
	00002908-0000-1000-8000-00805f9b34fb
	Report Reference
Descriptor (Handle 0x004a)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0048/desc004a
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
Characteristic (Handle 0x0044)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0044
	00002a4d-0000-1000-8000-00805f9b34fb
	Report
Descriptor (Handle 0x0047)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0044/desc0047
	00002908-0000-1000-8000-00805f9b34fb
	Report Reference
Descriptor (Handle 0x0046)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0044/desc0046
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
Characteristic (Handle 0x0040)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0040
	00002a4d-0000-1000-8000-00805f9b34fb
	Report
Descriptor (Handle 0x0043)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0040/desc0043
	00002908-0000-1000-8000-00805f9b34fb
	Report Reference
Descriptor (Handle 0x0042)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0040/desc0042
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
Characteristic (Handle 0x003c)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char003c
	00002a4d-0000-1000-8000-00805f9b34fb
	Report
Descriptor (Handle 0x003f)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char003c/desc003f
	00002908-0000-1000-8000-00805f9b34fb
	Report Reference
Descriptor (Handle 0x003e)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char003c/desc003e
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
Characteristic (Handle 0x0038)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0038
	00002a4d-0000-1000-8000-00805f9b34fb
	Report
Descriptor (Handle 0x003b)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0038/desc003b
	00002908-0000-1000-8000-00805f9b34fb
	Report Reference
Descriptor (Handle 0x003a)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0038/desc003a
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
Characteristic (Handle 0x0034)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0034
	00002a4d-0000-1000-8000-00805f9b34fb
	Report
Descriptor (Handle 0x0037)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0034/desc0037
	00002908-0000-1000-8000-00805f9b34fb
	Report Reference
Descriptor (Handle 0x0036)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0033/char0034/desc0036
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
```

#### Report Descriptors

- desc0051: f1 03 (feature)
- desc004e: f0 03 (feature)
- desc004b: fe 01 (input)
- desc0047: fd 01 (input)
- desc0043: 60 01 (input)
- desc003f: fc 01 (input) -> touch
- desc003b: fb 01 (input) -> keys
- desc0037: fa 01 (input) -> audio

### Battery

```
Primary Service (Handle 0x002c)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service002c
	0000180f-0000-1000-8000-00805f9b34fb
	Battery Service
Characteristic (Handle 0x0030)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service002c/char0030
	00002a1a-0000-1000-8000-00805f9b34fb
	Unknown
Descriptor (Handle 0x0032)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service002c/char0030/desc0032
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
Characteristic (Handle 0x002d)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service002c/char002d
	00002a19-0000-1000-8000-00805f9b34fb
	Battery Level
Descriptor (Handle 0x002f)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service002c/char002d/desc002f
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
```

### Misc

```
Primary Service (Handle 0x0026)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0026
	0000181e-0000-1000-8000-00805f9b34fb
	Bond Management
Characteristic (Handle 0x0029)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0026/char0029
	00002aa4-0000-1000-8000-00805f9b34fb
	Bond Management Control Point
Descriptor (Handle 0x002b)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0026/char0029/desc002b
	00002900-0000-1000-8000-00805f9b34fb
	Characteristic Extended Properties
Characteristic (Handle 0x0027)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0026/char0027
	00002aa5-0000-1000-8000-00805f9b34fb
	Bond Management Feature
```

```
Primary Service (Handle 0x0018)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0018
	8341f2b4-c013-4f04-8197-c4cdb42e26dc
	Vendor specific
Characteristic (Handle 0x0023)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0018/char0023
	30e69638-3752-4feb-a3aa-3226bcd05ace
	Vendor specific
Descriptor (Handle 0x0025)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0018/char0023/desc0025
	00002902-0000-1000-8000-00805f9b34fb
	Client Characteristic Configuration
Characteristic (Handle 0x0021)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0018/char0021
	2bdcaebe-8746-45df-a841-96b840980fb8
	Vendor specific
Characteristic (Handle 0x001f)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0018/char001f
	2bdcaebe-8746-45df-a841-96b840980fb7
	Vendor specific
Characteristic (Handle 0x001d)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0018/char001d
	0188bf68-463a-405d-91fd-0b8940b92254
	Vendor specific
Characteristic (Handle 0x001b)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0018/char001b
	0188bf67-463a-405d-91fd-0b8940b92254
	Vendor specific
Characteristic (Handle 0x0019)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0018/char0019
	0188bf66-463a-405d-91fd-0b8940b92254
	Vendor specific
```

```
Primary Service (Handle 0x000b)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service000b
	0000180a-0000-1000-8000-00805f9b34fb
	Device Information
Characteristic (Handle 0x0016)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service000b/char0016
	00002a50-0000-1000-8000-00805f9b34fb
	PnP ID
Characteristic (Handle 0x0014)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service000b/char0014
	00002a26-0000-1000-8000-00805f9b34fb
	Firmware Revision String
Characteristic (Handle 0x0012)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service000b/char0012
	00002a27-0000-1000-8000-00805f9b34fb
	Hardware Revision String
Characteristic (Handle 0x0010)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service000b/char0010
	00002a25-0000-1000-8000-00805f9b34fb
	Serial Number String
Characteristic (Handle 0x000e)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service000b/char000e
	00002a24-0000-1000-8000-00805f9b34fb
	Model Number String
Characteristic (Handle 0x000c)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service000b/char000c
	00002a29-0000-1000-8000-00805f9b34fb
	Manufacturer Name String
```

```
Primary Service (Handle 0x000a)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service000a
	00001801-0000-1000-8000-00805f9b34fb
	Generic Attribute Profile
```

```
Primary Service (Handle 0x0001)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0001
	00001800-0000-1000-8000-00805f9b34fb
	Generic Access Profile
Characteristic (Handle 0x0008)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0001/char0008
	00002aa6-0000-1000-8000-00805f9b34fb
	Central Address Resolution
Characteristic (Handle 0x0006)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0001/char0006
	00002a04-0000-1000-8000-00805f9b34fb
	Peripheral Preferred Connection Parameters
Characteristic (Handle 0x0004)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0001/char0004
	00002a01-0000-1000-8000-00805f9b34fb
	Appearance
Characteristic (Handle 0x0002)
	/org/bluez/hci0/dev_58_0A_D4_9C_A3_4C/service0001/char0002
	00002a00-0000-1000-8000-00805f9b34fb
	Device Name
```

## Gen 3

Most likely identical to [Gen 2](#gen-2).
