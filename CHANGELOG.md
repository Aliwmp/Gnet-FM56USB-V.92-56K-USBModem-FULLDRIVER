# Changelog - FM56USB Gnet AM5067 Driver Package

All notable changes to this driver package will be documented in this file.

## [1.0.0] - 2024-03-15

### Added
- Initial release of full driver package for Gnet FM56USB V.92 56K USB Modem
- Windows driver support for Windows 98/ME/2000/XP/Vista/7/8/8.1/10/11
- Linux kernel module for kernel 2.6.x and later
- Comprehensive hardware specifications documentation
- Complete AT command reference guide
- Windows installation guide with troubleshooting
- Linux installation guide with PPP configuration
- Troubleshooting guide covering common issues
- INF file for Windows driver installation (fm56usb.inf)
- Linux kernel module source code (fm56usb.c)
- Makefile for easy kernel module compilation

### Supported Platforms
- **Windows**: 98, ME, 2000, XP, Vista, 7, 8, 8.1, 10, 11 (32-bit and 64-bit)
- **Linux**: Kernel 2.6.x through 6.x
- **macOS**: Compatible via CDC ACM driver (built-in)

### Hardware Support
- **Device**: Gnet FM56USB V.92 56K USB Modem
- **Chipset**: LSI/Agere AM5067
- **USB VID:PID**: 0572:1329
- **Interface**: USB 1.1/2.0 compatible
- **Standards**: V.92, V.90, V.34, V.32bis, and legacy standards

### Features
- Full V.92 support with QuickConnect and Modem on Hold
- V.42 and MNP error correction
- V.42bis and MNP5 data compression
- Hardware and software flow control
- Full Hayes AT command set
- Caller ID support (where available)
- Fax Class 1 support
- Maximum 56K downstream, 48K upstream

### Documentation
- Hardware specifications and technical details
- Step-by-step installation guides for Windows and Linux
- Complete AT command reference with examples
- Comprehensive troubleshooting guide
- Linux PPP configuration guide
- Dial-up networking setup instructions

### Known Issues
- Windows 8/10/11 may require disabling driver signature enforcement
- Some USB 3.0 ports may require compatibility mode
- Line quality significantly affects maximum connection speed
- FCC regulations limit upload speed to 48 Kbps maximum

### Notes
- For Linux, the built-in cdc_acm driver works with most modern distributions
- Custom kernel module provided for special cases and development
- Windows driver is unsigned and may require test mode or signature override

---

## Future Releases

### Planned Features
- Signed Windows drivers for Windows 10/11
- Additional language support for documentation
- macOS-specific driver package (if needed)
- Firmware update utilities
- Connection diagnostic tools
- Performance tuning utilities

### Under Consideration
- GUI configuration utility for Windows
- Linux GUI connection manager
- Automatic optimal settings detection
- Remote management capabilities
- Enhanced logging and diagnostics

---

## Version History

### Version Numbering
This package follows Semantic Versioning (SemVer):
- **Major version**: Incompatible API changes
- **Minor version**: Backwards-compatible functionality additions
- **Patch version**: Backwards-compatible bug fixes

### Release Schedule
- **Major releases**: As needed for significant changes
- **Minor releases**: Quarterly feature additions
- **Patch releases**: As needed for critical bugs

---

## Support and Contact

For support, please refer to:
- Documentation/TROUBLESHOOTING.md
- Documentation/INSTALLATION_WINDOWS.md
- Documentation/INSTALLATION_LINUX.md

---

## License

This driver package is distributed under the terms specified in the LICENSE file.

- Windows drivers: Proprietary/GPL compatible
- Linux kernel module: GPL v2
- Documentation: Creative Commons BY-SA 4.0

---

## Contributors

- Gnet Communications - Original driver development
- Community contributors - Testing and feedback

---

## Changelog Format

This changelog follows the [Keep a Changelog](https://keepachangelog.com/) format.

Categories:
- **Added**: New features
- **Changed**: Changes in existing functionality
- **Deprecated**: Soon-to-be removed features
- **Removed**: Removed features
- **Fixed**: Bug fixes
- **Security**: Security vulnerability fixes
