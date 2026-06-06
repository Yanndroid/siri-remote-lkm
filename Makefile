MODULE_NAME := hid-siriremote

SRC_DIR := linux/drivers/hid
BUILD_DIR := $(PWD)/build

MODULE_OUTPUT := $(BUILD_DIR)/$(SRC_DIR)/$(MODULE_NAME).ko

obj-m += $(SRC_DIR)/$(MODULE_NAME).o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) MO=$(BUILD_DIR) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) MO=$(BUILD_DIR) clean

load:
	make
	sudo insmod $(MODULE_OUTPUT)
unload:
	sudo rmmod $(MODULE_OUTPUT)

install:
	make
	sudo mkdir -p /lib/modules/$(shell uname -r)/extra/
	sudo cp $(MODULE_OUTPUT) /lib/modules/$(shell uname -r)/extra/
	sudo depmod -a
	echo $(MODULE_NAME) | sudo tee /etc/modules-load.d/$(MODULE_NAME).conf
	sudo modprobe $(MODULE_NAME)
uninstall:
	sudo rm -f /lib/modules/$(shell uname -r)/extra/$(MODULE_NAME).ko
	sudo depmod -a
	sudo rm -f /etc/modules-load.d/$(MODULE_NAME).conf
	sudo rmmod $(MODULE_NAME)

log:
	sudo dmesg -W