# Linux Installation Guide - FM56USB Gnet AM5067 Modem

## System Requirements
- Linux kernel 2.6.x or later
- USB support enabled in kernel
- Root/sudo access
- gcc, make, and kernel headers installed

## Automatic Detection (Modern Linux)

Most modern Linux distributions will automatically recognize the FM56USB modem using the built-in `cdc_acm` driver:

1. **Connect the Modem**
   ```bash
   # Plug in the USB modem
   # Check if detected
   lsusb | grep 0572:1329
   ```

2. **Verify Device Node**
   ```bash
   # Should create /dev/ttyACM0 (or similar)
   ls -l /dev/ttyACM*
   
   # Check dmesg for detection messages
   dmesg | tail -20
   ```

3. **Check Permissions**
   ```bash
   # Add user to dialout group for modem access
   sudo usermod -aG dialout $USER
   
   # Log out and back in for changes to take effect
   ```

## Manual Driver Installation

If automatic detection fails, you can use the included kernel module:

### Compiling the Driver

1. **Install Prerequisites**
   
   Ubuntu/Debian:
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential linux-headers-$(uname -r)
   ```
   
   Fedora/RHEL/CentOS:
   ```bash
   sudo dnf install gcc make kernel-devel kernel-headers
   ```
   
   Arch Linux:
   ```bash
   sudo pacman -S base-devel linux-headers
   ```

2. **Navigate to Driver Directory**
   ```bash
   cd Linux/kernel-modules
   ```

3. **Compile the Module**
   ```bash
   make clean
   make
   ```

4. **Install the Module**
   ```bash
   sudo make install
   sudo depmod -a
   ```

5. **Load the Module**
   ```bash
   sudo modprobe fm56usb
   ```

6. **Verify Installation**
   ```bash
   lsmod | grep fm56usb
   dmesg | tail -10
   ```

### Make Driver Load at Boot

1. **Add to Module List**
   ```bash
   echo "fm56usb" | sudo tee -a /etc/modules
   ```

2. **Create udev Rule (Optional)**
   Create `/etc/udev/rules.d/99-fm56usb.rules`:
   ```
   SUBSYSTEM=="tty", ATTRS{idVendor}=="0572", ATTRS{idProduct}=="1329", SYMLINK+="modem", MODE="0666", GROUP="dialout"
   ```
   
   Reload udev:
   ```bash
   sudo udevadm control --reload-rules
   sudo udevadm trigger
   ```

## Configuration

### Testing the Modem

1. **Using minicom**
   ```bash
   # Install minicom
   sudo apt-get install minicom  # Debian/Ubuntu
   sudo dnf install minicom      # Fedora
   
   # Configure minicom
   sudo minicom -s
   # Set Serial Device to /dev/ttyACM0
   # Set Baud Rate to 115200
   # Set Hardware Flow Control to Yes
   # Save setup as dfl
   # Exit
   
   # Run minicom
   minicom
   
   # Test with AT commands
   # Type: AT
   # Should respond: OK
   ```

2. **Using screen**
   ```bash
   screen /dev/ttyACM0 115200
   
   # Type AT commands
   AT
   # Should respond: OK
   
   ATI
   # Should display modem information
   
   # Exit screen: Ctrl+A, then K
   ```

### Setting up PPP for Dial-up

1. **Install pppd**
   ```bash
   sudo apt-get install ppp  # Debian/Ubuntu
   sudo dnf install ppp      # Fedora
   ```

2. **Configure PPP**
   Create `/etc/ppp/peers/gnet-dialup`:
   ```
   /dev/ttyACM0
   115200
   crtscts
   noauth
   defaultroute
   usepeerdns
   persist
   user "your_isp_username"
   connect "/usr/sbin/chat -v -f /etc/chatscripts/gnet-dialup"
   ```

3. **Create Chat Script**
   Create `/etc/chatscripts/gnet-dialup`:
   ```
   TIMEOUT 30
   ABORT "NO CARRIER"
   ABORT "NO DIALTONE"
   ABORT "BUSY"
   "" ATZ
   OK ATDT1234567  # Replace with ISP phone number
   CONNECT ""
   ```

4. **Set Credentials**
   Add to `/etc/ppp/pap-secrets` or `/etc/ppp/chap-secrets`:
   ```
   your_isp_username * your_isp_password *
   ```

5. **Connect**
   ```bash
   sudo pon gnet-dialup
   
   # Check connection
   ifconfig ppp0
   
   # Disconnect
   sudo poff gnet-dialup
   ```

### NetworkManager Configuration (GUI)

For desktop environments with NetworkManager:

1. Open Network Settings
2. Click "Add Connection" → "DSL/PPPoE"
3. Select modem device (/dev/ttyACM0)
4. Enter ISP credentials and phone number
5. Save and connect

## Troubleshooting

### Modem Not Detected
```bash
# Check USB device is visible
lsusb -v | grep -A 10 "0572:1329"

# Check kernel messages
dmesg | grep -i usb
dmesg | grep -i modem

# Verify USB drivers loaded
lsmod | grep usb
```

### Permission Denied
```bash
# Check current user groups
groups

# Add to dialout group if not present
sudo usermod -aG dialout $USER

# Or temporarily change permissions
sudo chmod 666 /dev/ttyACM0
```

### Module Won't Load
```bash
# Check for errors
sudo modprobe fm56usb
dmesg | tail -20

# Verify kernel headers match
uname -r
ls /lib/modules/$(uname -r)/build

# Recompile if necessary
cd Linux/kernel-modules
make clean
make
sudo make install
```

### Connection Fails
```bash
# Test modem response
echo "AT" > /dev/ttyACM0
cat /dev/ttyACM0

# Check PPP logs
sudo tail -f /var/log/syslog | grep pppd

# Verify ISP settings
# - Phone number correct
# - Username/password correct
# - PPP authentication method (PAP/CHAP)
```

## Verification Commands

```bash
# List USB devices
lsusb | grep Gnet

# Check device nodes
ls -l /dev/ttyACM*

# View modem information
udevadm info -a -n /dev/ttyACM0 | grep -E 'idVendor|idProduct'

# Test AT commands
echo -e "ATI\r" > /dev/ttyACM0 && cat /dev/ttyACM0
```

## Uninstallation

```bash
# Remove kernel module
sudo modprobe -r fm56usb

# Remove installed files
cd Linux/kernel-modules
sudo make uninstall

# Remove from module list
sudo sed -i '/fm56usb/d' /etc/modules

# Remove udev rule
sudo rm /etc/udev/rules.d/99-fm56usb.rules
sudo udevadm control --reload-rules
```

## Additional Resources
- PPP Documentation: /usr/share/doc/ppp/
- Kernel USB Documentation: /usr/src/linux/Documentation/usb/
- AT Commands Reference: AT_COMMANDS.md
