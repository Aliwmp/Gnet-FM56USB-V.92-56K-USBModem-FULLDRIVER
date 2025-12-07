# AT Command Reference - FM56USB Gnet AM5067 Modem

## Introduction
This document provides a comprehensive reference for AT commands supported by the Gnet FM56USB V.92 modem with AM5067 chipset.

## Basic Commands

### Command Syntax
- Commands start with `AT` (Attention)
- Commands are case-insensitive
- Commands must end with carriage return `<CR>` (Enter key)
- Multiple commands can be combined on one line

### Standard Responses
- `OK` - Command executed successfully
- `ERROR` - Invalid command or syntax error
- `CONNECT` - Connection established
- `NO CARRIER` - Connection failed or lost
- `NO DIALTONE` - No dial tone detected
- `BUSY` - Remote modem busy
- `NO ANSWER` - No answer from remote modem

## Essential Commands

| Command | Description | Example |
|---------|-------------|---------|
| `AT` | Attention (test command) | `AT` returns `OK` |
| `ATZ` | Reset modem to default configuration | `ATZ` |
| `ATI` or `ATI0-I11` | Display modem information | `ATI3` (product ID) |
| `ATE0` | Echo off (commands not displayed) | `ATE0` |
| `ATE1` | Echo on (commands are displayed) | `ATE1` |
| `ATV0` | Numeric responses | `ATV0` |
| `ATV1` | Verbose responses (default) | `ATV1` |
| `ATQ0` | Enable result codes | `ATQ0` |
| `ATQ1` | Disable result codes (quiet mode) | `ATQ1` |
| `AT&F` | Factory reset | `AT&F` |
| `AT&W` | Save current configuration to NVRAM | `AT&W` |

## Dialing Commands

| Command | Description | Example |
|---------|-------------|---------|
| `ATDT<number>` | Dial using tone (DTMF) | `ATDT5551234` |
| `ATDP<number>` | Dial using pulse | `ATDP5551234` |
| `ATD` | Redial last number | `ATD` |
| `ATH` | Hang up (go on-hook) | `ATH` or `ATH0` |
| `ATA` | Answer incoming call | `ATA` |
| `AT,` | Pause 2 seconds during dial | `ATDT9,5551234` |
| `AT;` | Return to command mode after dial | `ATDT5551234;` |
| `ATX0-X4` | Select call progress monitoring | `ATX4` (full monitoring) |

## S-Registers

### Common S-Registers

| Register | Default | Range | Description |
|----------|---------|-------|-------------|
| `S0` | 0 | 0-255 | Auto-answer ring count (0=disabled) |
| `S1` | 0 | 0-255 | Ring counter (read-only) |
| `S2` | 43 | 0-255 | Escape character (default: +) |
| `S3` | 13 | 0-127 | Carriage return character |
| `S4` | 10 | 0-127 | Line feed character |
| `S5` | 8 | 0-127 | Backspace character |
| `S6` | 2 | 2-255 | Wait time before dialing (seconds) |
| `S7` | 50 | 1-255 | Wait time for carrier (seconds) |
| `S8` | 2 | 0-255 | Pause time for comma dial modifier |
| `S10` | 14 | 1-255 | Lost carrier disconnect time (0.1s) |
| `S11` | 95 | 50-255 | DTMF tone duration (milliseconds) |
| `S12` | 50 | 20-255 | Escape guard time (0.02s) |
| `S25` | 5 | 0-255 | Delay to DTR (seconds) |
| `S30` | 0 | 0-255 | Inactivity timer (10s units, 0=disabled) |

### S-Register Commands

| Command | Description | Example |
|---------|-------------|---------|
| `ATS<n>?` | Query register value | `ATS0?` returns `000` |
| `ATS<n>=<value>` | Set register value | `ATS0=2` (answer on 2 rings) |

## Flow Control

| Command | Description |
|---------|-------------|
| `AT&K0` | Disable flow control |
| `AT&K3` | Hardware flow control (RTS/CTS) |
| `AT&K4` | Software flow control (XON/XOFF) |

## Error Correction & Compression

| Command | Description |
|---------|-------------|
| `AT\N0` | Disable error correction (buffered mode) |
| `AT\N1` | Enable error correction (auto select) |
| `AT\N2` | Enable MNP reliable mode |
| `AT\N3` | Enable V.42/MNP auto reliable mode |
| `AT%C0` | Disable data compression |
| `AT%C1` | Enable MNP5 compression |
| `AT%C2` | Enable V.42bis compression |
| `AT%C3` | Enable V.42bis and MNP5 compression |

## V.92 Specific Commands

| Command | Description |
|---------|-------------|
| `AT+PCW=1` | Enable Modem on Hold (MOH) |
| `AT+PCW=0` | Disable Modem on Hold |
| `AT+PQC=1` | Enable QuickConnect |
| `AT+PQC=0` | Disable QuickConnect |
| `AT+PMH` | Initiate Modem on Hold |
| `AT+PMHR` | Resume from Modem on Hold |
| `AT+PMHT=<n>` | Set MOH timer (seconds) |

## Speaker & Volume Control

| Command | Description |
|---------|-------------|
| `ATL0` | Low speaker volume |
| `ATL1` | Low speaker volume |
| `ATL2` | Medium speaker volume (default) |
| `ATL3` | High speaker volume |
| `ATM0` | Speaker always off |
| `ATM1` | Speaker on until carrier detected |
| `ATM2` | Speaker always on |
| `ATM3` | Speaker on after dialing until carrier |

## DTE-DCE Interface Commands

| Command | Description |
|---------|-------------|
| `AT&C0` | DCD always on |
| `AT&C1` | DCD follows carrier (default) |
| `AT&D0` | Ignore DTR |
| `AT&D1` | Enter command mode on DTR drop |
| `AT&D2` | Hang up and enter command mode on DTR drop |
| `AT&D3` | Reset on DTR drop |

## Information Commands

| Command | Description | Response |
|---------|-------------|----------|
| `ATI0` | Product code | Numeric code |
| `ATI1` | ROM checksum | Checksum value |
| `ATI2` | ROM checksum test | OK/ERROR |
| `ATI3` | Product ID string | Model name |
| `ATI4` | Current settings | Configuration |
| `ATI5` | NVRAM settings | Saved configuration |
| `ATI6` | Link diagnostics | Connection stats |
| `ATI7` | Product configuration | Hardware info |
| `ATI9` | Plug and Play ID | PnP string |
| `ATI11` | Link diagnostics (last) | Last connection info |

## Extended Commands (V.25ter)

| Command | Description |
|---------|-------------|
| `AT+FCLASS=?` | Query fax class support |
| `AT+FCLASS=0` | Data mode (default) |
| `AT+FCLASS=1` | Fax Class 1 mode |
| `AT+GMI` | Request manufacturer ID |
| `AT+GMM` | Request model ID |
| `AT+GMR` | Request revision |
| `AT+GCAP` | Request capabilities list |
| `AT+GCI=<country>` | Select country code |
| `AT+GCI?` | Query current country |

## Fax Commands (Class 1)

| Command | Description |
|---------|-------------|
| `AT+FCLASS=1` | Enter Class 1 fax mode |
| `AT+FTS=<n>` | Transmit silence (10ms units) |
| `AT+FRS=<n>` | Receive silence (10ms units) |
| `AT+FTM=<n>` | Transmit data with modulation |
| `AT+FRM=<n>` | Receive data with modulation |
| `AT+FTH=<n>` | Transmit HDLC data |
| `AT+FRH=<n>` | Receive HDLC data |

## Caller ID Commands

| Command | Description |
|---------|-------------|
| `AT#CID=1` | Enable Caller ID detection |
| `AT#CID=0` | Disable Caller ID detection |
| `AT#CID?` | Query Caller ID status |

## Diagnostics Commands

| Command | Description |
|---------|-------------|
| `AT&T` | Local analog loopback test |
| `AT&T0` | Terminate test |
| `ATI11` | View last call diagnostics |
| `AT%Q` | Query line signal quality |

## Online Commands

These commands can be issued while connected:

| Command | Description |
|---------|-------------|
| `+++` | Escape to command mode (pause 1s before and after) |
| `ATO` | Return to online mode from command mode |
| `ATH` | Hang up connection |

## Extended Result Codes

| Code | Meaning |
|------|---------|
| `CONNECT` | Connected at default speed |
| `CONNECT 1200` | Connected at 1200 bps |
| `CONNECT 2400` | Connected at 2400 bps |
| `CONNECT 4800` | Connected at 4800 bps |
| `CONNECT 9600` | Connected at 9600 bps |
| `CONNECT 14400` | Connected at 14.4 Kbps |
| `CONNECT 19200` | Connected at 19.2 Kbps |
| `CONNECT 28800` | Connected at 28.8 Kbps |
| `CONNECT 31200` | Connected at 31.2 Kbps |
| `CONNECT 33600` | Connected at 33.6 Kbps |
| `CONNECT 48000` | Connected at 48 Kbps (V.92 upload) |
| `CONNECT 50000` | Connected at 50 Kbps |
| `CONNECT 52000` | Connected at 52 Kbps |
| `CONNECT 54000` | Connected at 54 Kbps |
| `CONNECT 56000` | Connected at 56 Kbps |

## Example Command Sequences

### Basic Connection Test
```
AT          -> OK
ATI3        -> Gnet FM56USB V.92 56K USB Modem
ATZ         -> OK
ATDT5551234 -> CONNECT 48000
+++         (wait 1 second before and after)
ATH         -> OK (disconnect)
```

### Configure Auto-Answer
```
ATS0=2      -> OK (answer on 2nd ring)
AT&W        -> OK (save to memory)
```

### Enable V.92 Features
```
AT+PQC=1    -> OK (enable QuickConnect)
AT+PCW=1    -> OK (enable Modem on Hold)
AT&W        -> OK (save settings)
```

### Maximum Performance Setup
```
AT&F        -> OK (factory reset)
ATE1        -> OK (echo on)
ATQ0        -> OK (result codes on)
ATV1        -> OK (verbose mode)
ATX4        -> OK (full call progress)
AT&K3       -> OK (hardware flow control)
AT\N3       -> OK (V.42/MNP auto)
AT%C3       -> OK (V.42bis/MNP5 compression)
AT&W        -> OK (save configuration)
```

## Notes
- Not all commands may be supported depending on firmware version
- Some commands are hardware-dependent
- Country-specific settings may affect available features
- Consult modem documentation for additional proprietary commands
