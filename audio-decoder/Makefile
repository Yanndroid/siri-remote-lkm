MODULE_NAME := siriremote-audio-decoder
UDEV_RULE_NAME := 99-siriremote-audio.rules
SERVICE_NAME := siriremote-audio-decoder@.service

all:
	gcc -O2 $(shell pkg-config --cflags --libs opus libspa-0.2 libpipewire-0.3) -o $(MODULE_NAME) $(MODULE_NAME).c
	chmod +x $(MODULE_NAME)

install:
	make
	sudo cp $(MODULE_NAME) /usr/local/bin/
	sudo cp $(SERVICE_NAME) /etc/systemd/user/
	systemctl --user daemon-reload
	sudo cp $(UDEV_RULE_NAME) /etc/udev/rules.d/
	sudo udevadm control --reload
	sudo udevadm trigger

uninstall:
	sudo rm -f /usr/local/bin/$(MODULE_NAME)
	sudo rm -f /etc/systemd/user/$(SERVICE_NAME)
	systemctl --user daemon-reload
	sudo rm -f /etc/udev/rules.d/$(UDEV_RULE_NAME)
	sudo udevadm control --reload