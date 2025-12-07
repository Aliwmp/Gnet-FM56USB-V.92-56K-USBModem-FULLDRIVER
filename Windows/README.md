# Windows Drivers - FM56USB Gnet AM5067

## Directory Structure

```
Windows/
├── x86/              # 32-bit drivers (Windows 98/ME/2000/XP/Vista/7/8/10/11)
├── x64/              # 64-bit drivers (Windows XP/Vista/7/8/10/11 x64)
├── inf/              # Driver information files
│   └── fm56usb.inf   # Installation information file
└── README.md         # This file
```

## Supported Windows Versions

### 32-bit (x86)
- Windows 98 SE
- Windows ME
- Windows 2000
- Windows XP (32-bit)
- Windows Vista (32-bit)
- Windows 7 (32-bit)
- Windows 8/8.1 (32-bit)
- Windows 10 (32-bit)
- Windows 11 (32-bit) - limited availability

### 64-bit (x64)
- Windows XP Professional x64 Edition
- Windows Vista (64-bit)
- Windows 7 (64-bit)
- Windows 8/8.1 (64-bit)
- Windows 10 (64-bit)
- Windows 11 (64-bit)

## Files Required

### Essential Files
- **fm56usb.inf** - Driver installation information file (in inf/ directory)
- **fm56usb.sys** - Kernel-mode driver (would be in x86/ or x64/)
- **fm56usb.cat** - Catalog file for driver signing (for signed versions)

### Optional Files
- **setup.exe** - Automated installation wizard
- **readme.txt** - Installation notes
- **release_notes.txt** - Version-specific information

## Quick Installation

### Automatic Installation (Recommended)
1. Connect the FM56USB modem to a USB port
2. Run `setup.exe` as Administrator
3. Follow the installation wizard
4. Restart computer when prompted

### Manual Installation
1. Extract all files to a folder (e.g., C:\Drivers\FM56USB)
2. Connect the modem
3. Open Device Manager (Win + X → Device Manager)
4. Right-click on the unrecognized modem
5. Select "Update Driver Software"
6. Browse to the driver folder:
   - For 32-bit Windows: Select Windows/x86 folder
   - For 64-bit Windows: Select Windows/x64 folder
7. Complete installation

## Driver Signing

### Windows 98/ME/2000/XP
These operating systems do not enforce driver signature requirements. Unsigned drivers will install without issues.

### Windows Vista/7
Driver signing is enforced but can be bypassed:
- During installation, click "Install this driver software anyway" when warned
- Or disable enforcement temporarily (see Installation Guide)

### Windows 8/8.1/10/11
Strong driver signature enforcement:

**Option 1: Disable Driver Signature Enforcement (Temporary)**
1. Restart computer
2. Hold Shift and click Restart
3. Troubleshoot → Advanced Options → Startup Settings
4. Press F7 for "Disable driver signature enforcement"
5. Install driver

**Option 2: Test Mode (Persistent)**
```cmd
bcdedit /set testsigning on
```
Restart and install driver. Turn off test mode after installation:
```cmd
bcdedit /set testsigning off
```

## Hardware Detection

### Device Identification
- **Hardware ID**: `USB\VID_0572&PID_1329`
- **Compatible IDs**: `USB\Class_02&SubClass_02`, `USB\Class_02`
- **Device Class**: Modem (Class 02h)

### Expected Device Manager Location
- **Modems** category (normal installation)
- **Ports (COM & LPT)** category (may also appear here)
- **Other Devices** category (if driver not installed)

## COM Port Assignment

After installation, the modem is assigned a COM port number (e.g., COM3, COM4).

### Finding Your COM Port
1. Device Manager → Modems
2. Right-click modem → Properties
3. Modem tab shows COM port
4. Or: Device Manager → Ports (COM & LPT)

### Changing COM Port
1. Device Manager → Modem → Properties
2. Port Settings tab → Advanced
3. Select new COM port number
4. Click OK and restart computer

**Note**: Some applications require COM1-COM4. Modern Windows supports COM1-COM256.

## Configuration

### Modem Properties
Access through:
- Control Panel → Phone and Modem Options → Modems tab
- Device Manager → Modem → Properties

### Common Settings
- **Maximum Port Speed**: 921600 bps (recommended)
- **Flow Control**: Hardware (RTS/CTS)
- **Error Control**: Enabled
- **Compression**: Enabled
- **Speaker Volume**: Medium
- **Wait for dial tone**: Enabled (may need to disable on PBX/VoIP)

## Testing the Installation

### Query Modem Test
1. Control Panel → Phone and Modem Options
2. Modems tab → Select modem
3. Properties → Diagnostics tab
4. Click "Query Modem"
5. Should see successful AT command responses

### HyperTerminal Test (Windows XP)
1. Start → Programs → Accessories → Communications → HyperTerminal
2. Create new connection
3. Connect using: COM port assigned to modem
4. Port Settings: 115200, 8, None, 1, Hardware
5. Type `AT` and press Enter (should respond `OK`)

### PuTTY/Terminal Test (All Windows)
1. Download PuTTY (free terminal software)
2. Select "Serial" connection type
3. Enter COM port (e.g., COM3)
4. Speed: 115200
5. Type `AT` and press Enter (should respond `OK`)

## Troubleshooting

### Driver Won't Install
- Ensure you have Administrator privileges
- Check if Windows Update has a compatible driver
- Try compatibility mode (right-click setup.exe → Properties → Compatibility)
- Disable antivirus temporarily

### Device Not Working
- Check Device Manager for yellow exclamation marks
- Ensure USB port is providing power
- Try different USB port (preferably USB 2.0 port)
- Reinstall driver

### Code 10 Error
- Update USB controller drivers
- Disable power management for USB Root Hub
- Check BIOS USB settings

### Code 28 Error
- Drivers are not installed
- Manually specify driver location during installation

### Code 31 Error
- Registry corruption - try: `regedit` and fix driver registry entries
- Or: Clean driver installation using DDU (Device Driver Uninstaller)

## Driver Updates

### Checking Current Version
1. Device Manager → Modem → Properties
2. Driver tab → Driver Version

### Updating Drivers
1. Download latest driver package
2. Uninstall current driver (keep "Delete driver software" unchecked initially)
3. Install new driver version
4. Restart computer

## Uninstallation

### Complete Removal
1. Device Manager → Modem → Right-click → Uninstall device
2. Check "Delete the driver software for this device"
3. Click Uninstall
4. Disconnect modem
5. Restart computer

### Clean Registry (Advanced)
If reinstallation fails, clean registry:
1. Run: `regedit`
2. Navigate to: `HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_0572&PID_1329`
3. Delete the key (backup first!)
4. Restart and reinstall

**Warning**: Editing registry can cause system instability. Backup first!

## INF File Details

The fm56usb.inf file contains:
- Device identification (VID/PID)
- Driver file associations
- Registry settings
- Modem initialization strings
- AT command defaults
- COM port configuration

**Do not modify** the INF file unless you understand device installation requirements.

## Driver Files Reference

### Kernel Driver (fm56usb.sys)
- **Type**: Windows Driver Model (WDM) / KMDF
- **Location**: C:\Windows\System32\drivers\
- **Function**: Low-level USB communication

### Installation Data
- **Location**: C:\Windows\INF\
- **Files**: fm56usb.inf, oem*.inf (copy)

## Support

For detailed installation instructions, see:
- **Documentation/INSTALLATION_WINDOWS.md** - Step-by-step guide
- **Documentation/TROUBLESHOOTING.md** - Problem solutions

## Notes

- This driver is unsigned and may trigger security warnings
- The modem is USB bus-powered (no external power needed)
- Driver works with standard Windows dial-up networking
- Compatible with PPP, RAS, and TAPI applications
- Supports legacy applications requiring COM port access

## Compatibility

### Working Applications
- Windows Dial-Up Networking
- HyperTerminal (XP and earlier)
- PuTTY, RealTerm, Tera Term
- Fax software (supporting Class 1 fax)
- Terminal emulators
- Legacy communication software

### Known Compatible Software
- Microsoft Dial-Up Networking
- Internet Explorer dial-up
- Outlook Express dial-up
- Third-party fax programs
- BBS terminal software
- Industrial control applications

## Legal

This driver package is provided for use with genuine Gnet FM56USB modems. Redistribution and modification may be subject to licensing terms. See LICENSE file for details.
