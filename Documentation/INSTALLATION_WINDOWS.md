# Windows Installation Guide - FM56USB Gnet AM5067 Modem

## System Requirements
- Windows 98/ME/2000/XP/Vista/7/8/8.1/10/11
- Available USB port (USB 1.1 or USB 2.0)
- Administrator privileges for driver installation
- 10 MB free disk space

## Installation Steps

### Windows 10/11 (Automatic Installation)

1. **Connect the Modem**
   - Insert the FM56USB modem into an available USB port
   - Windows will automatically detect the device
   - Wait for Windows to attempt automatic driver installation

2. **Manual Driver Installation (if automatic fails)**
   - Open Device Manager (Win + X, then select Device Manager)
   - Locate the modem under "Other Devices" or "Modems"
   - Right-click on "Gnet FM56USB V.92 56K USB Modem" or unknown device
   - Select "Update Driver"
   - Choose "Browse my computer for driver software"
   - Navigate to the driver folder (Windows/x64 for 64-bit or Windows/x86 for 32-bit)
   - Click "Next" and follow the prompts

### Windows 7/8/8.1

1. **Download and Extract Drivers**
   - Extract the driver package to a known location (e.g., C:\Drivers\FM56USB)

2. **Connect the Modem**
   - Plug the modem into a USB port
   - Windows will detect new hardware

3. **Install Driver**
   - When prompted, select "Browse my computer for driver software"
   - Navigate to the extracted driver folder
   - Select the appropriate folder:
     - For 32-bit Windows: Windows/x86
     - For 64-bit Windows: Windows/x64
   - Click "Next" and complete installation

### Windows XP/2000

1. **Run Setup (Recommended)**
   - Navigate to the driver folder
   - Run setup.exe as Administrator
   - Follow the installation wizard
   - Restart computer when prompted

2. **Manual Installation**
   - Connect the modem
   - When "Found New Hardware Wizard" appears, click "Next"
   - Select "Install from a list or specific location"
   - Browse to the Windows/x86 folder
   - Complete the wizard

### Windows 98/ME

1. **Legacy Installation**
   - Run setup.exe from the driver package
   - Follow all prompts in the installation wizard
   - Connect the modem when prompted
   - Restart the computer after installation completes

## Verification

1. **Check Device Manager**
   - Open Device Manager (Win + X → Device Manager)
   - Expand "Modems" section
   - Verify "Gnet FM56USB V.92 56K USB Modem (AM5067)" appears
   - Check for yellow exclamation marks (indicates driver issue)

2. **Test the Modem**
   - Open Control Panel → Phone and Modem
   - Select the Modems tab
   - Select your modem and click "Properties"
   - On the Diagnostics tab, click "Query Modem"
   - Successful response confirms proper installation

3. **COM Port Assignment**
   - In Device Manager, expand "Ports (COM & LPT)"
   - Note the COM port number assigned to the modem
   - This port will be used by communication software

## Troubleshooting

### Driver Installation Fails
- Ensure you have administrator privileges
- Disable Driver Signature Enforcement (Windows 8/10/11):
  - Restart computer
  - Press F8 during boot
  - Select "Disable driver signature enforcement"
  - Install driver
  
### Device Not Recognized
- Try a different USB port
- Uninstall device from Device Manager and reconnect
- Check USB cable connection
- Test on another computer to rule out hardware failure

### COM Port Conflicts
- Change COM port number in Device Manager:
  - Right-click modem → Properties → Port Settings → Advanced
  - Select an available COM port (COM1-COM4 recommended)

### Driver Signature Warning (Windows 7+)
- The driver is unsigned; you may need to disable driver signature enforcement
- Or install in Test Mode:
  ```cmd
  bcdedit /set testsigning on
  ```
  (Restart required; turn off after installation with `bcdedit /set testsigning off`)

## Uninstallation

1. **Remove Driver**
   - Open Device Manager
   - Right-click on "Gnet FM56USB V.92 56K USB Modem"
   - Select "Uninstall device"
   - Check "Delete the driver software for this device"
   - Click "Uninstall"

2. **Physical Removal**
   - Safely disconnect the USB modem
   - Remove from USB port

3. **Clean Registry (Optional)**
   - Use the uninstaller from Control Panel → Programs and Features
   - Or manually remove registry entries (advanced users only)

## Additional Configuration

### Dial-Up Connection Setup
1. Open Control Panel → Network and Internet → Network Connections
2. Create new connection → Dial-up
3. Enter ISP phone number and credentials
4. Save and connect

### AT Command Terminal
- Use HyperTerminal (XP) or PuTTY/RealTerm
- Configure: COM port, 115200 baud, 8N1
- Test with: `AT` (should respond `OK`)
- Query model: `ATI` (displays modem information)

## Support
For additional support, refer to:
- TROUBLESHOOTING.md
- AT_COMMANDS.md
- Visit manufacturer website
