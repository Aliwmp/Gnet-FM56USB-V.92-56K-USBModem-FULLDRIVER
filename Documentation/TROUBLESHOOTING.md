# Troubleshooting Guide - FM56USB Gnet AM5067 Modem

## Common Issues and Solutions

### Windows Issues

#### Issue: Device Not Recognized

**Symptoms:**
- Yellow exclamation mark in Device Manager
- Device shows as "Unknown Device"
- Driver installation fails

**Solutions:**
1. Try a different USB port (preferably directly on motherboard, not hub)
2. Ensure USB port is functioning (test with other device)
3. Reinstall USB hub drivers
4. Update Windows USB drivers via Windows Update
5. Disable Fast Startup (Power Options → Choose what closing lid does)
6. Check BIOS for USB legacy support settings

#### Issue: Driver Signature Error (Windows 8/10/11)

**Symptoms:**
- "Windows cannot verify the digital signature"
- "Driver software publisher cannot be verified"

**Solutions:**
1. Disable Driver Signature Enforcement temporarily:
   - Restart PC
   - Press F8 during boot (or Shift+Restart → Troubleshoot → Advanced)
   - Select "Disable driver signature enforcement"
   - Install driver
   
2. Enable Test Mode (persistent):
   ```cmd
   bcdedit /set testsigning on
   ```
   Restart computer and install driver

#### Issue: COM Port Not Available

**Symptoms:**
- Software cannot find modem
- COM port shows but doesn't respond

**Solutions:**
1. Check COM port assignment in Device Manager
2. Change to a lower COM port number (COM1-COM4):
   - Device Manager → Modem → Properties
   - Port Settings → Advanced
   - Select new COM port
3. Disable other unused COM ports
4. Check for port conflicts

#### Issue: Modem Detected but Won't Dial

**Symptoms:**
- Device Manager shows working device
- AT commands fail or no response
- Dialing produces error

**Solutions:**
1. Test with HyperTerminal/PuTTY:
   - Connect to assigned COM port
   - Settings: 115200, 8, N, 1
   - Type `AT` and press Enter (should respond `OK`)
   
2. Check modem initialization string
3. Verify phone line is connected and working
4. Check dial tone with standard phone
5. Disable call waiting: `*70,` before number
6. Try pulse dialing instead of tone: `ATDP` instead of `ATDT`

#### Issue: Slow Connection Speed

**Symptoms:**
- Connects at low speed (14.4K instead of 56K)
- Frequent disconnections
- Poor line quality

**Solutions:**
1. Check phone line quality
2. Eliminate line noise (unplug other devices on same line)
3. Use shorter phone cable
4. Bypass line splitters/filters
5. Disable compression if line is poor: `AT%C0`
6. Lower maximum speed in modem properties
7. Check with ISP for line quality issues

#### Issue: Modem Disconnects Randomly

**Symptoms:**
- Connection drops after some time
- "NO CARRIER" messages

**Solutions:**
1. Disable power management:
   - Device Manager → USB Root Hub → Power Management
   - Uncheck "Allow computer to turn off this device"
2. Adjust inactivity timeout: `ATS30=0` (disable)
3. Check phone line for call waiting (disable with `*70`)
4. Update USB controller drivers
5. Check for electrical interference

### Linux Issues

#### Issue: Device Not Detected

**Symptoms:**
- `lsusb` doesn't show device (0572:1329)
- No `/dev/ttyACM*` created

**Solutions:**
1. Check USB connection:
   ```bash
   lsusb -v | grep -A 10 "0572:1329"
   dmesg | tail -50
   ```

2. Load cdc_acm module manually:
   ```bash
   sudo modprobe cdc_acm
   ```

3. Check if device is recognized but has wrong permissions:
   ```bash
   ls -l /dev/ttyACM*
   ```

4. Add udev rule:
   ```bash
   echo 'SUBSYSTEM=="tty", ATTRS{idVendor}=="0572", ATTRS{idProduct}=="1329", MODE="0666"' | sudo tee /etc/udev/rules.d/99-fm56usb.rules
   sudo udevadm control --reload-rules
   sudo udevadm trigger
   ```

#### Issue: Permission Denied

**Symptoms:**
- Cannot access `/dev/ttyACM0`
- "Permission denied" errors

**Solutions:**
1. Add user to dialout group:
   ```bash
   sudo usermod -aG dialout $USER
   ```
   Log out and back in

2. Temporary permission fix:
   ```bash
   sudo chmod 666 /dev/ttyACM0
   ```

3. Check current permissions:
   ```bash
   ls -l /dev/ttyACM0
   groups
   ```

#### Issue: PPP Connection Fails

**Symptoms:**
- pppd cannot connect
- "LCP timeout" errors
- No response from modem

**Solutions:**
1. Test modem directly:
   ```bash
   echo -e "ATZ\r" > /dev/ttyACM0
   cat /dev/ttyACM0
   ```

2. Check pppd logs:
   ```bash
   sudo tail -f /var/log/syslog | grep pppd
   ```

3. Verify ISP settings:
   - Phone number correct
   - Username/password correct
   - Authentication method (PAP/CHAP)

4. Test with simpler chat script:
   ```
   ABORT "NO CARRIER"
   "" ATZ
   OK ATDT<number>
   CONNECT ""
   ```

5. Check if pppd has correct permissions:
   ```bash
   ls -l /usr/sbin/pppd
   # Should be setuid root
   ```

#### Issue: Module Compilation Fails

**Symptoms:**
- `make` produces errors
- Module won't load

**Solutions:**
1. Install kernel headers:
   ```bash
   # Ubuntu/Debian
   sudo apt-get install linux-headers-$(uname -r)
   
   # Fedora
   sudo dnf install kernel-devel kernel-headers
   ```

2. Verify headers match running kernel:
   ```bash
   uname -r
   ls /lib/modules/$(uname -r)/build
   ```

3. Clean and rebuild:
   ```bash
   make clean
   make
   sudo make install
   sudo depmod -a
   ```

4. Check for compilation errors and missing dependencies

### Hardware Issues

#### Issue: Modem Not Powering On

**Symptoms:**
- No LEDs light up
- Not detected by any computer
- No power draw from USB

**Solutions:**
1. Test different USB ports
2. Try different USB cable
3. Test on different computer
4. Check for physical damage
5. Verify USB port provides power (test with other device)
6. Device may be faulty - consider replacement

#### Issue: Physical Damage

**Symptoms:**
- Cracked case
- Bent USB connector
- Exposed circuits

**Solutions:**
1. Do not use if internal components are exposed
2. If connector is bent, carefully straighten (power off first)
3. If case is cracked but device works, secure with electrical tape
4. Consider professional repair or replacement

### Line Quality Issues

#### Issue: Poor Line Quality

**Symptoms:**
- Frequent disconnections
- Slow speeds
- Static or noise on line
- CRC errors

**Solutions:**
1. Test phone line with regular telephone
2. Check for:
   - Loose connections
   - Damaged cables
   - Long cable runs (>25 feet)
   - Improper grounding
3. Eliminate sources of interference:
   - Fluorescent lights
   - Electric motors
   - Other electronic devices
4. Contact phone company for line test
5. Request line conditioning from ISP

#### Issue: No Dial Tone

**Symptoms:**
- "NO DIALTONE" error
- ATX3 or ATX4 won't dial

**Solutions:**
1. Verify phone line is connected
2. Test line with regular phone
3. Check if phone service is active
4. Try different phone jack
5. Bypass X4 dial tone detection: `ATX3` or `ATX0`
6. Check if modem expects different region settings

### Connection Speed Issues

#### Issue: Cannot Connect Above 33.6K

**Symptoms:**
- Maximum speed is 33.6 Kbps
- Never achieves V.90/V.92 speeds

**Solutions:**
1. Verify ISP supports V.90/V.92
2. Check line quality (must be very good for 56K)
3. Ensure ISP modem is V.90/V.92 compatible
4. Distance from central office (CO) affects maximum speed
5. FCC regulations limit upload to 48K (V.92) or 33.6K (V.90)
6. Disable compression: `AT%C0`
7. Try connecting at different times (line quality varies)

## Diagnostic Tools

### Windows Diagnostic Tools

1. **Device Manager**
   - Win + X → Device Manager
   - Check modem status
   - View COM port assignment
   - Update drivers

2. **Phone and Modem Options**
   - Control Panel → Phone and Modem
   - Query modem test
   - View modem logs

3. **Event Viewer**
   - Win + X → Event Viewer
   - Windows Logs → System
   - Look for USB/Modem errors

4. **PuTTY/RealTerm**
   - Test AT commands directly
   - Verify modem responses

### Linux Diagnostic Tools

1. **lsusb / dmesg**
   ```bash
   lsusb -v | grep -A 10 "0572:1329"
   dmesg | tail -50
   ```

2. **minicom / screen**
   ```bash
   minicom -D /dev/ttyACM0
   screen /dev/ttyACM0 115200
   ```

3. **pppd debug**
   ```bash
   sudo pppd debug dump logfd 2 nodetach
   ```

4. **System logs**
   ```bash
   sudo tail -f /var/log/syslog
   journalctl -f
   ```

## AT Command Diagnostics

### Test Basic Functionality
```
AT          -> Should return OK
ATZ         -> Reset modem
ATI3        -> Display model name
ATI4        -> Display current configuration
ATI6        -> Display link diagnostics
AT&V        -> View active and stored profiles
```

### Test Connection
```
ATDT5551234 -> Dial test number
ATH         -> Hang up
ATA         -> Answer incoming call
```

### Check Configuration
```
AT&V        -> View current settings
ATS0?       -> Check auto-answer rings
ATS7?       -> Check carrier wait time
AT&K?       -> Check flow control
AT\N?       -> Check error correction mode
```

## Getting More Help

### Log Collection

**Windows:**
1. Device Manager → Modem → Properties → Advanced
2. Enable modem logging
3. Reproduce issue
4. Collect logs from: `%SystemRoot%\ModemLog_*.txt`

**Linux:**
1. Enable debug logging:
   ```bash
   echo 'options usbserial debug=1' | sudo tee /etc/modprobe.d/usbserial.conf
   ```
2. Reproduce issue
3. Collect logs:
   ```bash
   dmesg > dmesg.log
   sudo journalctl -b > journal.log
   ```

### Contact Information

When seeking support, provide:
- Operating system and version
- Modem model and firmware version (ATI3, ATI7)
- Error messages (exact text)
- Log files
- Steps to reproduce issue
- What troubleshooting steps were already tried

## Known Limitations

1. **FCC Regulations**: Upload speed limited to 48 Kbps in V.92 mode
2. **Line Distance**: Quality degrades beyond 18,000 feet from CO
3. **USB Power**: Some older USB ports may not provide adequate power
4. **Driver Signing**: Windows 10/11 require driver signature or test mode
5. **Linux Kernel**: Requires kernel 2.6.x or later for full support
6. **56K Speed**: Requires perfect line conditions and ISP support

## Additional Resources

- See AT_COMMANDS.md for complete command reference
- See INSTALLATION_WINDOWS.md for installation help
- See INSTALLATION_LINUX.md for Linux setup
- See HARDWARE_SPECS.md for technical specifications
