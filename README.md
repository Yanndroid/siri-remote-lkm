# Apple Siri Remote Linux Driver

A Linux Kernel Module Driver that adds support for most Apple TV Siri Remotes. Following models are supported (see which one you have [here](https://support.apple.com/103233)):

- Gen 1 (A1513 and A1962)
- Gen 2 (A2540)
- Gen 3 (A2854)

This project is heavily based on my [previous work](https://github.com/Yanndroid/SiriRemote-Linux).

This repo also contains extensive [documentation](/docs/readme.md) about the remotes communication protocol.

## Features

- All buttons
- Multitouch

## TODO

- Audio
- Motion (gen 1)
- Pairing tool
- DKMS or merge into the Linux Kernel

## Usage

### Pairing

Unfortunately the remotes don't show up the bluetooth settings, so you have to use `bluetoothctl` to pair them for the first time. See [here](https://support.apple.com/en-us/102569) to put the remotes in pairing mode.

### Using the Driver

You can install the Linux Kernel Module by cloning this repo and running `make install`.

## Related work

- [Jack-R1/SiriRemoteDriver](https://github.com/Jack-R1/SiriRemoteDriver)
- [retsyx/SiriRemote](https://github.com/retsyx/SiriRemote)
- [azais-corentin/siri-remote](https://github.com/azais-corentin/siri-remote)
- [henaxxx/a2854-siri-remote-linux](https://github.com/henaxxx/a2854-siri-remote-linux)
