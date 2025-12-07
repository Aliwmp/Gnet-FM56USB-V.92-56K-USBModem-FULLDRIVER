# Linux Support - FM56USB Gnet AM5067

## Directory Structure

```
Linux/
├── kernel-modules/     # Custom kernel module source
│   ├── fm56usb.c      # Kernel driver source
│   ├── Makefile       # Build configuration
│   └── README.md      # Module documentation
├── documentation/      # Linux-specific docs
└── README.md          # This file
```

## Overview

The Gnet FM56USB V.92 56K USB Modem is supported on Linux through two methods:

1. **Built-in CDC ACM Driver** (Recommended)
2. **Custom Kernel Module** (Advanced/Development)

## Recommended: Using Built-in CDC ACM Driver

Modern Linux distributions (kernel 2.6.x and later) include the `cdc_acm` (Communications Device Class Abstract Control Model) driver, which automatically supports USB modems including the FM56USB.

### Automatic Detection

Simply plug in the modem:
```bash
# Check if device is detected
lsusb | grep 0572:1329

# Verify device node creation
ls -l /dev/ttyACM*

# Check kernel messages
dmesg | tail -20
```

### Expected Output
```
Bus 001 Device 003: ID 0572:1329 Conexant Systems (Rockwell), Inc.
```

Device node:
```
/dev/ttyACM0  (or /dev/ttyACM1, /dev/ttyACM2, etc.)
```

### Setting Permissions

Add your user to the `dialout` group:
```bash
sudo usermod -aG dialout $USER
```

Log out and back in for changes to take effect.

### Testing the Modem

#### Using minicom
```bash
# Install minicom
sudo apt-get install minicom  # Ubuntu/Debian
sudo dnf install minicom      # Fedora
sudo pacman -S minicom        # Arch

# Configure minicom
sudo minicom -s
# Set: Serial Device = /dev/ttyACM0
# Set: Baud Rate = 115200
# Set: Hardware Flow Control = Yes
# Save as dfl and Exit

# Run minicom
minicom

# Test commands
AT        # Should respond: OK
ATI3      # Should show: Gnet FM56USB V.92 56K USB Modem
ATZ       # Reset modem

# Exit: Ctrl+A, then Z, then X
```

#### Using screen
```bash
screen /dev/ttyACM0 115200

# Type AT commands
AT
ATI
ATZ

# Exit: Ctrl+A, then K, then Y
```

## Custom Kernel Module

For advanced users or development purposes, a custom kernel module is available in the `kernel-modules/` directory.

### When to Use Custom Module
- Standard cdc_acm driver doesn't work
- Need custom functionality
- Debugging or development
- Older kernel without proper CDC ACM support

### Building and Installing

See `kernel-modules/README.md` for detailed instructions.

Quick start:
```bash
cd kernel-modules
make
sudo make install
sudo modprobe fm56usb
```

## Dial-Up Networking with PPP

### Installing PPP
```bash
# Ubuntu/Debian
sudo apt-get install ppp

# Fedora/RHEL
sudo dnf install ppp

# Arch Linux
sudo pacman -S ppp
```

### Basic Configuration

1. **Create PPP peer file** (`/etc/ppp/peers/isp`):
```
/dev/ttyACM0
115200
crtscts
noauth
defaultroute
usepeerdns
persist
user "your_username"
connect "/usr/sbin/chat -v -f /etc/chatscripts/isp"
```

2. **Create chat script** (`/etc/chatscripts/isp`):
```
TIMEOUT 30
ABORT "NO CARRIER"
ABORT "NO DIALTONE"
ABORT "BUSY"
"" ATZ
OK ATDT1234567
CONNECT ""
```

3. **Set credentials** (`/etc/ppp/pap-secrets` or `/etc/ppp/chap-secrets`):
```
your_username * your_password *
```

4. **Connect**:
```bash
sudo pon isp
```

5. **Disconnect**:
```bash
sudo poff isp
```

6. **Check status**:
```bash
ifconfig ppp0
sudo pppd status
```

### NetworkManager GUI Setup

Most desktop Linux distributions include NetworkManager with dial-up support:

1. Open Network Settings
2. Click "+" to add connection
3. Select "DSL/PPPoE" or look for dial-up options
4. Configure:
   - Device: /dev/ttyACM0
   - Phone number: ISP's number
   - Username: Your ISP username
   - Password: Your ISP password
5. Save and connect

## Distribution-Specific Notes

### Ubuntu/Debian
```bash
# Install dependencies
sudo apt-get install build-essential linux-headers-$(uname -r)
sudo apt-get install ppp minicom

# Load cdc_acm driver
sudo modprobe cdc_acm

# Add to startup
echo "cdc_acm" | sudo tee -a /etc/modules
```

### Fedora/RHEL/CentOS
```bash
# Install dependencies
sudo dnf install gcc make kernel-devel kernel-headers
sudo dnf install ppp minicom

# Load cdc_acm driver
sudo modprobe cdc_acm

# Add to startup
echo "cdc_acm" | sudo tee -a /etc/modules-load.d/cdc_acm.conf
```

### Arch Linux
```bash
# Install dependencies
sudo pacman -S base-devel linux-headers
sudo pacman -S ppp minicom

# Load cdc_acm driver
sudo modprobe cdc_acm

# Add to startup
echo "cdc_acm" | sudo tee -a /etc/modules-load.d/cdc_acm.conf
```

### Raspberry Pi (Raspbian)
```bash
# Usually works out of the box
lsusb | grep 0572:1329
ls -l /dev/ttyACM0

# If not, load module
sudo modprobe cdc_acm
```

## udev Rules

Create persistent device naming:

File: `/etc/udev/rules.d/99-fm56usb.rules`
```
# Gnet FM56USB Modem
SUBSYSTEM=="tty", ATTRS{idVendor}=="0572", ATTRS{idProduct}=="1329", SYMLINK+="modem", MODE="0666", GROUP="dialout"
```

Reload udev:
```bash
sudo udevadm control --reload-rules
sudo udevadm trigger
```

Now the modem will also be available as `/dev/modem`.

## Fax Support

### Installing efax
```bash
# Ubuntu/Debian
sudo apt-get install efax

# Fedora
sudo dnf install efax
```

### Sending a Fax
```bash
efax -d /dev/ttyACM0 -t "1234567" file.ps
```

### Receiving a Fax
```bash
efax -d /dev/ttyACM0 -r -o received
```

## Serial Console Applications

The modem can be used with various serial communication tools:

### cu
```bash
cu -l /dev/ttyACM0 -s 115200
```

### picocom
```bash
picocom -b 115200 /dev/ttyACM0
```

### Python Serial
```python
import serial

ser = serial.Serial('/dev/ttyACM0', 115200)
ser.write(b'ATI\r')
response = ser.readline()
print(response)
ser.close()
```

## Troubleshooting

### Device Not Detected
```bash
# Check USB
lsusb -v | grep -A 10 "0572:1329"

# Check kernel messages
dmesg | grep -i usb
dmesg | grep -i modem
dmesg | grep cdc_acm

# Verify module loaded
lsmod | grep cdc_acm
```

### Permission Issues
```bash
# Check permissions
ls -l /dev/ttyACM0

# Check groups
groups

# Add to dialout group
sudo usermod -aG dialout $USER

# Temporary fix
sudo chmod 666 /dev/ttyACM0
```

### Module Won't Load
```bash
# Check kernel logs
dmesg | tail -20

# Load manually with debug
sudo modprobe cdc_acm

# Check dependencies
modinfo cdc_acm
```

### PPP Connection Fails
```bash
# Check logs
sudo tail -f /var/log/syslog | grep pppd

# Test modem directly
echo -e "ATZ\r" > /dev/ttyACM0
cat /dev/ttyACM0

# Verify ISP settings
# - Correct phone number
# - Correct username/password
# - Correct authentication (PAP/CHAP)
```

## Verification

### Check USB Device
```bash
lsusb -v -d 0572:1329
```

### Check Device Node
```bash
ls -l /dev/ttyACM*
```

### Test Modem Communication
```bash
# Simple test
echo -e "AT\r" > /dev/ttyACM0 && timeout 1 cat /dev/ttyACM0

# Should output: OK
```

### View Modem Information
```bash
# Using screen
screen /dev/ttyACM0 115200

# Commands to try:
AT       # Basic test
ATI3     # Model name
ATI7     # Configuration
AT&V     # View settings
```

## Performance Tips

### Optimal Settings
- Use hardware flow control (crtscts)
- Maximum baud rate: 115200 or higher
- Enable error correction: `AT\N3`
- Enable compression: `AT%C3`
- Use persistent connection in PPP

### Line Quality
- Shorter phone cables are better
- Avoid line splitters
- Remove unnecessary devices from line
- Check for line noise

## Advanced Usage

### Custom Initialization
Add to PPP peer file:
```
init "/usr/sbin/chat -v '' ATZ OK 'AT&F' OK 'AT\N3%C3' OK"
```

### Logging
Enable PPP logging:
```
debug
logfile /var/log/ppp-isp.log
```

### Multiple Modems
Each modem gets a unique /dev/ttyACMx number. Create separate PPP peer files for each.

## Resources

- **Installation Guide**: Documentation/INSTALLATION_LINUX.md
- **Troubleshooting**: Documentation/TROUBLESHOOTING.md
- **AT Commands**: Documentation/AT_COMMANDS.md
- **PPP Documentation**: /usr/share/doc/ppp/

## Support

For Linux-specific issues:
1. Check kernel messages: `dmesg`
2. Verify USB detection: `lsusb`
3. Check permissions: `ls -l /dev/ttyACM0`
4. Review PPP logs: `/var/log/syslog`
5. Consult distribution documentation

## Notes

- Most users should use the built-in cdc_acm driver
- Custom kernel module is for special cases only
- The modem appears as a serial device (/dev/ttyACM0)
- PPP daemon provides dial-up networking
- Modem is USB bus-powered (no external power needed)

## License

- Kernel module: GPL v2
- Documentation: Creative Commons BY-SA 4.0
