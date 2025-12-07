# Linux Kernel Module for FM56USB Gnet AM5067

## Overview
This directory contains the Linux kernel module source code for the Gnet FM56USB V.92 56K USB Modem with AM5067 chipset.

## Important Note
Most modern Linux distributions (kernel 2.6.x and later) include the `cdc_acm` (Communications Device Class Abstract Control Model) driver, which provides automatic support for USB modems including the FM56USB. **In most cases, you do not need to compile or install this custom kernel module.**

## When to Use This Module
Use this custom kernel module only if:
- The standard `cdc_acm` driver does not work with your system
- You need custom functionality not provided by `cdc_acm`
- You are working with an older kernel that lacks proper CDC ACM support
- You need debugging or development features

## Quick Start

### Prerequisites
```bash
# Ubuntu/Debian
sudo apt-get install build-essential linux-headers-$(uname -r)

# Fedora/RHEL/CentOS
sudo dnf install gcc make kernel-devel kernel-headers

# Arch Linux
sudo pacman -S base-devel linux-headers
```

### Building
```bash
make
```

### Installing
```bash
sudo make install
```

### Loading
```bash
sudo make load
# or
sudo modprobe fm56usb
```

### Unloading
```bash
sudo make unload
# or
sudo modprobe -r fm56usb
```

### Checking Status
```bash
lsmod | grep fm56usb
dmesg | tail -20
```

## Files

- **fm56usb.c** - Main kernel module source code
- **Makefile** - Build and installation script
- **README.md** - This file

## Module Information

**Module Name:** fm56usb  
**Version:** 1.0.0  
**License:** GPL  
**Supported Device:** Gnet FM56USB (VID:0572 PID:1329)

## Building for Different Kernels

### For Current Kernel
```bash
make
```

### For Specific Kernel Version
```bash
make KDIR=/lib/modules/5.15.0-generic/build
```

### Cross-Compilation
```bash
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
```

## Troubleshooting

### Module Won't Load
```bash
# Check kernel ring buffer
dmesg | tail -20

# Check module dependencies
modinfo fm56usb

# Try loading with verbose output
sudo insmod fm56usb.ko
```

### Compilation Errors
```bash
# Ensure kernel headers are installed and match running kernel
uname -r
ls /lib/modules/$(uname -r)/build

# Clean and rebuild
make clean
make
```

### USB Device Not Recognized
```bash
# Check if USB device is visible
lsusb | grep 0572:1329

# Check USB subsystem messages
dmesg | grep usb

# Verify module is loaded
lsmod | grep fm56usb
```

## Using cdc_acm Instead (Recommended)

For most users, the standard `cdc_acm` driver is sufficient:

```bash
# Load cdc_acm driver
sudo modprobe cdc_acm

# Check if device is recognized
ls -l /dev/ttyACM*

# Test with minicom or screen
minicom -D /dev/ttyACM0
# or
screen /dev/ttyACM0 115200
```

## Development

### Enable Debug Messages
Edit `fm56usb.c` and rebuild:
```c
#define DEBUG 1
```

### Testing Changes
```bash
sudo make unload
make clean
make
sudo make load
dmesg | tail -20
```

### Kernel Module Parameters
Currently, this module does not accept parameters. To add parameters:
```c
static int debug = 0;
module_param(debug, int, 0644);
MODULE_PARM_DESC(debug, "Debug level (0-3)");
```

## Module vs. Built-in Driver

| Feature | Custom Module | cdc_acm |
|---------|--------------|---------|
| Automatic detection | Manual load | Automatic |
| Maintenance | User maintains | Kernel maintains |
| Updates | Manual rebuild | Automatic with kernel |
| Compatibility | Specific device | Wide compatibility |
| **Recommendation** | Development only | Production use |

## Kernel Compatibility

This module has been tested with:
- Linux kernel 2.6.x
- Linux kernel 3.x
- Linux kernel 4.x
- Linux kernel 5.x
- Linux kernel 6.x

## Technical Details

### Device Interface
- **USB Class:** Communications Device Class (CDC)
- **USB Subclass:** Abstract Control Model (ACM)
- **Interface Type:** Control + Data
- **Endpoints:** Interrupt IN, Bulk IN, Bulk OUT

### Device Operations
The module implements:
- USB device probe and disconnect
- Device initialization
- Basic device management

For full functionality (TTY operations, data transmission), the standard `cdc_acm` driver is more complete.

## Contributing

To contribute improvements to this driver:
1. Test thoroughly on multiple kernel versions
2. Follow Linux kernel coding style
3. Document changes clearly
4. Test with actual hardware

## License

This driver is licensed under the GNU General Public License v2 (GPLv2).

## Support

For issues specific to this kernel module:
1. Check `dmesg` output
2. Verify kernel headers are installed
3. Ensure USB device is functioning (test with `lsusb`)
4. Try the standard `cdc_acm` driver first
5. Consult the main TROUBLESHOOTING.md document

## References

- Linux USB Driver Documentation: `/usr/src/linux/Documentation/usb/`
- CDC ACM Specification: USB Class Definitions for Communications Devices
- Linux Device Drivers, 3rd Edition (O'Reilly)
- Kernel source: `drivers/usb/class/cdc-acm.c`
