# Makefile for FM56USB Gnet AM5067 Modem Driver
# Copyright (c) Gnet Communications

# Module name
MODULE_NAME := fm56usb

# Kernel module object
obj-m := $(MODULE_NAME).o

# Kernel build directory
KDIR := /lib/modules/$(shell uname -r)/build

# Module installation directory
INSTALL_MOD_DIR := kernel/drivers/usb/class

# Current directory
PWD := $(shell pwd)

# Default target
all: module

# Build the kernel module
module:
	@echo "Building $(MODULE_NAME) kernel module..."
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -f *.o *.ko *.mod.c *.mod.o .*.cmd *.markers *.order *.symvers
	rm -rf .tmp_versions

# Install the module
install: module
	@echo "Installing $(MODULE_NAME) module..."
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install
	depmod -a
	@echo "Module installed. Load with: modprobe $(MODULE_NAME)"

# Uninstall the module
uninstall:
	@echo "Uninstalling $(MODULE_NAME) module..."
	rm -f $(DESTDIR)/lib/modules/$(shell uname -r)/$(INSTALL_MOD_DIR)/$(MODULE_NAME).ko
	depmod -a
	@echo "Module uninstalled."

# Load the module
load:
	@echo "Loading $(MODULE_NAME) module..."
	modprobe $(MODULE_NAME)
	@echo "Module loaded. Check dmesg for messages."

# Unload the module
unload:
	@echo "Unloading $(MODULE_NAME) module..."
	modprobe -r $(MODULE_NAME)
	@echo "Module unloaded."

# Help target
help:
	@echo "FM56USB Driver Makefile"
	@echo ""
	@echo "Available targets:"
	@echo "  all      - Build the kernel module (default)"
	@echo "  module   - Build the kernel module"
	@echo "  clean    - Remove build artifacts"
	@echo "  install  - Install the module to system"
	@echo "  uninstall- Remove the module from system"
	@echo "  load     - Load the module"
	@echo "  unload   - Unload the module"
	@echo "  help     - Display this help message"
	@echo ""
	@echo "Usage:"
	@echo "  make              # Build module"
	@echo "  sudo make install # Install module"
	@echo "  sudo make load    # Load module"

.PHONY: all module clean install uninstall load unload help
