# FM56USB Gnet AM5067 Hardware Specifications

## Device Information
- **Model**: Gnet FM56USB V.92 56K USB Modem
- **Chipset**: LSI/Agere AM5067 (Lucent/Agere Systems)
- **Interface**: USB 1.1 / USB 2.0 Compatible
- **Maximum Speed**: 56 Kbps downstream, 48 Kbps upstream

## USB Device IDs
- **Vendor ID (VID)**: 0x0572
- **Product ID (PID)**: 0x1329
- **Device Class**: Communications Device Class (CDC)

## Technical Specifications

### Modem Standards
- ITU V.92 (56K download)
- ITU V.90 (56K download)
- V.34 (33.6 Kbps)
- V.32bis (14.4 Kbps)
- V.32 (9.6 Kbps)
- V.22bis (2.4 Kbps)
- V.22 (1.2 Kbps)
- V.23 (1.2 Kbps)
- V.21 (300 bps)
- Bell 212A
- Bell 103

### Fax Standards
- ITU T.31 (Class 1)
- ITU T.30 (Class 1 Fax)
- V.17 (14.4 Kbps fax)
- V.29 (9.6 Kbps fax)
- V.27ter (4.8 Kbps fax)
- V.21 channel 2

### Error Correction & Compression
- V.42 LAPM and MNP 2-4 error correction
- V.42bis and MNP5 data compression
- V.44 data compression

### V.92 Features
- QuickConnect (Reduces connection time)
- Modem on Hold (MOH)
- PCM Upstream (48 Kbps upload)

## Power Requirements
- **Power Source**: USB Bus-powered
- **Voltage**: 5V DC from USB
- **Current Draw**: < 500mA (USB 2.0 specification compliant)

## Physical Specifications
- **Connector Type**: USB Type-A
- **Dimensions**: Approximately 80mm x 40mm x 15mm
- **Weight**: ~50 grams
- **Operating Temperature**: 0°C to 50°C
- **Storage Temperature**: -20°C to 70°C
- **Humidity**: 5% to 95% non-condensing

## Supported Operating Systems
- Windows 98/ME
- Windows 2000/XP
- Windows Vista/7/8/8.1/10/11 (32-bit and 64-bit)
- Linux kernel 2.6.x and later
- macOS (with CDC ACM driver support)

## LED Indicators
- **Power LED**: Indicates device is powered
- **Data LED**: Flashes during data transmission
- **Connection LED**: Solid when connected to remote modem

## AT Command Set
Supports standard Hayes AT command set with extended commands for V.92 features.

## Chipset Features (LSI/Agere AM5067)
- Integrated Digital Signal Processor (DSP)
- Full hardware-based modem implementation
- Low CPU utilization
- Advanced echo cancellation
- Automatic rate adaptation
- Line quality monitoring and reporting
