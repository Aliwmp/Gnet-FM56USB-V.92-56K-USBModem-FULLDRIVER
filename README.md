# Gnet FM56USB V.92 56K USB Modem - Full Driver Package

[![License](https://img.shields.io/badge/license-GPL%2FProprietary-blue.svg)](LICENSE)
[![Version](https://img.shields.io/badge/version-1.0.0-green.svg)](CHANGELOG.md)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-lightgrey.svg)](#supported-platforms)

Full driver package for the **Gnet FM56USB V.92 56K USB Modem** with **LSI/Agere AM5067** chipset.

## Overview

This repository contains comprehensive drivers, documentation, and utilities for the Gnet FM56USB V.92 56K USB Modem. The modem uses the reliable LSI/Agere AM5067 chipset and provides full V.92 dial-up connectivity with advanced features like QuickConnect and Modem on Hold.

### Key Features

- ✅ **V.92/V.90 Support** - Maximum 56K downstream, 48K upstream
- ✅ **USB Interface** - USB 1.1/2.0 compatible, bus-powered
- ✅ **Hardware Error Correction** - V.42 LAPM and MNP 2-4
- ✅ **Data Compression** - V.42bis and MNP5
- ✅ **QuickConnect** - Faster connection establishment
- ✅ **Modem on Hold** - Suspend modem connection for incoming calls
- ✅ **Fax Support** - Class 1 fax capability
- ✅ **Full AT Command Set** - Standard Hayes commands plus V.92 extensions
- ✅ **Cross-Platform** - Windows, Linux, and macOS support

## Hardware Specifications

| Specification | Details |
|--------------|---------|
| **Model** | Gnet FM56USB V.92 56K USB Modem |
| **Chipset** | LSI/Agere AM5067 |
| **USB IDs** | VID: 0x0572, PID: 0x1329 |
| **Interface** | USB 1.1/2.0 compatible |
| **Power** | USB bus-powered (5V, <500mA) |
| **Data Rate** | Up to 56 Kbps download, 48 Kbps upload |
| **Standards** | V.92, V.90, V.34, V.32bis, Bell 103/212A |
| **Fax** | T.30/T.31 Class 1 (up to 14.4 Kbps) |

## Supported Platforms

### Windows
- ✅ Windows 11 (32/64-bit)
- ✅ Windows 10 (32/64-bit)
- ✅ Windows 8/8.1 (32/64-bit)
- ✅ Windows 7 (32/64-bit)
- ✅ Windows Vista (32/64-bit)
- ✅ Windows XP (32/64-bit)
- ✅ Windows 2000
- ✅ Windows ME
- ✅ Windows 98 SE

### Linux
- ✅ Kernel 2.6.x and later
- ✅ All major distributions (Ubuntu, Debian, Fedora, Arch, etc.)
- ✅ Raspberry Pi (Raspbian)

### macOS
- ✅ Compatible via built-in CDC ACM driver

## Quick Start

### Windows Installation

1. **Download** the driver package
2. **Extract** all files to a folder
3. **Connect** the modem to a USB port
4. **Run** `setup.exe` as Administrator (or manually install from Device Manager)
5. **Follow** the installation wizard
6. **Restart** if prompted

For detailed instructions, see [Windows Installation Guide](Documentation/INSTALLATION_WINDOWS.md)

### Linux Installation

Modern Linux systems automatically recognize the modem:

```bash
# Simply plug in the modem and check detection
lsusb | grep 0572:1329

# Device should appear as /dev/ttyACM0
ls -l /dev/ttyACM*

# Add your user to dialout group
sudo usermod -aG dialout $USER

# Test the modem
minicom -D /dev/ttyACM0
```

For detailed instructions, see [Linux Installation Guide](Documentation/INSTALLATION_LINUX.md)

## Repository Structure

```
├── Windows/                 # Windows drivers
│   ├── x86/                # 32-bit drivers
│   ├── x64/                # 64-bit drivers
│   ├── inf/                # Driver information files
│   │   └── fm56usb.inf    # Installation INF file
│   └── README.md           # Windows-specific documentation
│
├── Linux/                   # Linux support
│   ├── kernel-modules/     # Custom kernel module (optional)
│   │   ├── fm56usb.c      # Kernel driver source
│   │   ├── Makefile       # Build configuration
│   │   └── README.md      # Module documentation
│   └── README.md           # Linux-specific documentation
│
├── Documentation/           # Comprehensive documentation
│   ├── HARDWARE_SPECS.md   # Technical specifications
│   ├── INSTALLATION_WINDOWS.md  # Windows installation guide
│   ├── INSTALLATION_LINUX.md    # Linux installation guide
│   ├── AT_COMMANDS.md      # AT command reference
│   └── TROUBLESHOOTING.md  # Troubleshooting guide
│
├── Firmware/               # Firmware information
│   └── README.md           # Firmware documentation
│
├── CHANGELOG.md            # Version history
├── LICENSE                 # License information
└── README.md               # This file
```

## Documentation

### Installation Guides
- 📖 [Windows Installation Guide](Documentation/INSTALLATION_WINDOWS.md) - Step-by-step Windows installation
- 📖 [Linux Installation Guide](Documentation/INSTALLATION_LINUX.md) - Linux setup and PPP configuration

### Reference Documentation
- 📖 [Hardware Specifications](Documentation/HARDWARE_SPECS.md) - Detailed technical specifications
- 📖 [AT Command Reference](Documentation/AT_COMMANDS.md) - Complete AT command guide
- 📖 [Troubleshooting Guide](Documentation/TROUBLESHOOTING.md) - Common issues and solutions

### Platform-Specific
- 📖 [Windows Driver README](Windows/README.md) - Windows driver details
- 📖 [Linux Support README](Linux/README.md) - Linux support information
- 📖 [Firmware Information](Firmware/README.md) - Firmware details

## Usage Examples

### Windows Dial-Up Connection

1. Open **Control Panel** → **Network and Internet** → **Network Connections**
2. Create new connection → **Dial-up**
3. Select the FM56USB modem
4. Enter ISP phone number and credentials
5. Click **Connect**

### Linux PPP Connection

```bash
# Create PPP peer configuration
sudo nano /etc/ppp/peers/myisp

# Add configuration
/dev/ttyACM0
115200
crtscts
noauth
defaultroute
usepeerdns
user "your_username"

# Connect
sudo pon myisp

# Disconnect
sudo poff myisp
```

### AT Commands Test

```bash
# Linux
minicom -D /dev/ttyACM0

# Type these commands:
AT          # Should respond: OK
ATI3        # Display model name
ATZ         # Reset modem
ATDT1234567 # Dial a number
ATH         # Hang up
```

For more examples, see the [AT Commands Reference](Documentation/AT_COMMANDS.md).

## Troubleshooting

### Common Issues

#### Windows: Driver Installation Fails
- Ensure Administrator privileges
- Disable driver signature enforcement (Windows 8/10/11)
- Try different USB port
- See [Troubleshooting Guide](Documentation/TROUBLESHOOTING.md)

#### Linux: Device Not Detected
```bash
# Check USB detection
lsusb | grep 0572:1329

# Load CDC ACM module
sudo modprobe cdc_acm

# Check kernel messages
dmesg | tail -20
```

#### Slow Connection Speed
- Check phone line quality
- Reduce electrical interference
- Disable call waiting: dial `*70,` before number
- Ensure ISP supports V.90/V.92

For comprehensive troubleshooting, see the [Troubleshooting Guide](Documentation/TROUBLESHOOTING.md).

## Technical Support

### Resources
- 📖 [Complete Documentation](Documentation/)
- 🐛 [Troubleshooting Guide](Documentation/TROUBLESHOOTING.md)
- 💬 GitHub Issues (for bug reports)

### Before Requesting Support

Please provide:
1. Operating system and version
2. Modem model verification (ATI3 command)
3. Error messages or symptoms
4. Steps already attempted
5. Relevant log files

## Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Test thoroughly
4. Submit a pull request with clear description

Areas for contribution:
- Testing on different platforms
- Documentation improvements
- Bug fixes
- Driver enhancements

## Version History

See [CHANGELOG.md](CHANGELOG.md) for detailed version history.

**Current Version**: 1.0.0 (2024-03-15)

## License

This project contains components under different licenses:

- **Windows Drivers**: Proprietary/GPL compatible
- **Linux Kernel Module**: GPL v2
- **Documentation**: Creative Commons BY-SA 4.0

See [LICENSE](LICENSE) file for complete license information.

## Disclaimer

This driver package is provided "as is" without warranty of any kind. Use at your own risk. The authors and contributors are not responsible for any damage to hardware or software resulting from the use of these drivers.

**Note**: Modern broadband connections (DSL, cable, fiber) are significantly faster than dial-up. This modem is intended for:
- Areas without broadband access
- Backup/failover connections
- Legacy system support
- Industrial/embedded applications
- Fax transmission

## Acknowledgments

- **Gnet Communications** - Original hardware and driver development
- **LSI/Agere Systems** - AM5067 chipset
- **Linux Kernel Community** - CDC ACM driver support
- **Contributors** - Testing and feedback

---

**Keywords**: USB Modem, V.92, V.90, 56K, Dial-up, AM5067, LSI, Agere, Gnet, FM56USB, Windows Driver, Linux Driver, CDC ACM, Serial Modem
