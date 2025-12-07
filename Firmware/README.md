# Firmware Information - FM56USB Gnet AM5067

## Overview
This directory is reserved for firmware files and firmware update utilities for the Gnet FM56USB V.92 56K USB Modem with AM5067 chipset.

## Current Status
The FM56USB modem contains embedded firmware on the AM5067 chipset. Under normal circumstances, firmware updates are not required or supported by end users.

## Firmware Details

### Chipset Firmware
- **Chipset**: LSI/Agere AM5067
- **Firmware Location**: Embedded in chipset ROM
- **Update Method**: Not user-serviceable
- **Version Detection**: Use AT command `ATI7` to query firmware information

### Checking Firmware Version

#### Windows
1. Open Device Manager
2. Right-click on modem → Properties
3. Diagnostics tab → Query Modem
4. Check ATI responses

Or use terminal:
```
ATI          # Modem identification
ATI3         # Product ID
ATI7         # Product configuration/firmware info
ATI9         # Plug and Play ID
```

#### Linux
```bash
# Using minicom
minicom -D /dev/ttyACM0

# Using screen
screen /dev/ttyACM0 115200

# Using echo/cat
echo -e "ATI7\r" > /dev/ttyACM0
cat /dev/ttyACM0
```

## Firmware Update Information

### Standard Operation
The AM5067 chipset includes:
- DSP firmware in ROM
- Modem initialization parameters
- Country-specific settings
- AT command interpreter

These are permanent and do not require updates under normal circumstances.

### When Firmware Updates Are Needed
Firmware updates might be necessary if:
- Manufacturer releases critical bug fixes
- New regulatory requirements
- Performance improvements available
- Compatibility issues with specific systems

**Warning**: Firmware updates should only be performed by qualified personnel as improper updates can brick the device.

## Factory Settings

### Reset to Factory Defaults
```
AT&F        # Load factory profile
AT&W        # Write to NVRAM
ATZ         # Reset modem
```

### Factory Configuration
The modem ships with:
- V.92 enabled
- Hardware flow control enabled
- V.42/MNP error correction enabled
- V.42bis/MNP5 compression enabled
- Country setting: Auto-detect
- Speaker mode: On until carrier
- Speaker volume: Medium

## Regional/Country Settings

The modem supports country-specific settings for different telephone systems:

### Setting Country Code
```
AT+GCI=<country_code>    # Set country
AT+GCI?                   # Query current country
AT+GCI=?                  # List supported countries
```

Common country codes:
- `B4` - USA
- `B5` - Canada  
- `26` - United Kingdom
- `00` - Worldwide (auto)

### Country-Specific Features
Different regions may have:
- Different dial tone frequencies
- Varying maximum power levels
- Different regulatory requirements
- Specific impedance matching

## DSP Configuration

The Digital Signal Processor (DSP) in the AM5067 handles:
- Signal modulation/demodulation
- Echo cancellation
- Noise reduction
- Error correction protocols
- Data compression
- Line quality monitoring

DSP parameters are optimized at the factory and typically don't require modification.

## NVRAM Settings

The modem includes NVRAM (Non-Volatile RAM) to store:
- User configuration profiles
- Country settings
- Custom S-register values
- Dialing directories (if supported)

### Saving/Loading Profiles
```
AT&W        # Write current settings to NVRAM
ATZ         # Load settings from NVRAM
AT&F        # Load factory defaults
AT&V        # View stored profiles
```

## Calibration

The modem is factory-calibrated for:
- Transmit power levels
- Receive sensitivity
- Impedance matching
- Frequency response
- Echo cancellation

Recalibration is not normally needed or supported.

## Troubleshooting

### Modem Behavior Issues
If the modem is misbehaving:

1. **Reset to factory defaults**
   ```
   AT&F
   AT&W
   ATZ
   ```

2. **Check firmware version**
   ```
   ATI7
   ```

3. **Verify country setting**
   ```
   AT+GCI?
   ```

4. **Test basic functionality**
   ```
   AT
   ATI
   ATDT5551234
   ATH
   ```

### Cannot Connect
- Check if firmware supports your region
- Verify country code is correct
- Reset to factory defaults
- Check with known working configuration

## Important Notes

1. **No User-Serviceable Firmware**: The firmware cannot be updated by end users
2. **Factory Programmed**: All settings are optimized at the factory
3. **NVRAM Corruption**: If NVRAM is corrupted, use `AT&F` to restore
4. **RMA Required**: Hardware or firmware failures require return to manufacturer

## Advanced Information

### Chipset Capabilities
The AM5067 chipset provides:
- Integrated DSP for all modem functions
- Hardware-based protocol implementation
- Low CPU utilization on host
- Adaptive equalizer
- Advanced echo cancellation
- Automatic rate adaptation

### Protocol Stack
```
┌─────────────────────────────────┐
│    Application Software         │
├─────────────────────────────────┤
│    USB CDC ACM Driver          │
├─────────────────────────────────┤
│    USB Stack                   │
├─────────────────────────────────┤
│    AM5067 Chipset              │
│  ┌───────────────────────────┐ │
│  │   V.92/V.90/V.34 Engine   │ │
│  │   Error Correction (V.42) │ │
│  │   Compression (V.42bis)   │ │
│  │   DSP Processing          │ │
│  └───────────────────────────┘ │
├─────────────────────────────────┤
│    Telephone Line Interface    │
└─────────────────────────────────┘
```

## Future Firmware Updates

If firmware updates become available in the future, they will be:
- Digitally signed by manufacturer
- Accompanied by detailed update instructions
- Tested thoroughly before release
- Provided with rollback capability
- Documented with changelog

**Check manufacturer website for official firmware releases**

## Support

For firmware-related issues:
1. Refer to TROUBLESHOOTING.md
2. Contact manufacturer support
3. Verify device is not counterfeit
4. Check for known issues with specific firmware versions

## Disclaimer

**WARNING**: Attempting to modify firmware without proper authorization and equipment can permanently damage the device. Only use official firmware update tools from the manufacturer.
