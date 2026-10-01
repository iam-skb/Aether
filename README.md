# Aether

Wireless security framework written in C, for authorized penetration testing
and Red Team engagements.

---

## Disclaimer

This tool is provided for educational and defensive purposes only.
Unauthorized use against networks you do not own or do not have
written permission to test is illegal and may result in criminal
prosecution. The author assumes no responsibility for misuse.

---

## Overview

Aether is a modular wireless security framework. It performs Wi-Fi
reconnaissance, handshake capture, WPS auditing, rogue access point
simulation, and Bluetooth scanning. It is built with a low-level
approach (raw sockets, libpcap, hostapd) for accuracy and speed.

Designed for:
- Red Team operations
- Wi-Fi security audits
- Wireless lab testing

---

## Features

| Category | Feature | Status |
|----------|---------|--------|
| Recon | Wi-Fi scan (BSSID, SSID, channel, RSSI, encryption, WPS) | Yes |
| Recon | Hidden SSID detection | Yes |
| Recon | Simulation mode (no Wi-Fi card required) | Yes |
| Attack | WPA/WPA2 handshake capture | Yes |
| Attack | Targeted deauth | Yes |
| Attack | WPS audit (Pixie Dust) | Yes |
| Attack | Rogue AP (hostapd) | Yes |
| Recon | Bluetooth classic + BLE scan | Yes |
| Report | HTML report | Yes |
| Report | JSON report | Yes |

---

## Requirements

- Linux (Kali, Parrot, Ubuntu 22.04+)
- GCC, make
- libpcap-dev
- aircrack-ng
- reaver
- hostapd
- bluez

Install on Debian/Ubuntu/Kali:

    sudo apt update
    sudo apt install -y build-essential libpcap-dev aircrack-ng reaver hostapd bluez

---

## Build

    git clone https://github.com/iam-skb/Aether.git
    cd Aether
    make

The binary aether is produced in the project root.

---

## Usage

Set the authorization token:

    export AETHER_TOKEN="AETHER_AUTHORIZED"

### Real Wi-Fi scan (requires root + compatible adapter)

    sudo ./aether -i wlan0 --scan

### Simulation mode (no Wi-Fi card needed)

    ./aether --simulate --scan
    ./aether --simulate --scan -R rapport.html

### Capture a WPA/WPA2 handshake

    sudo ./aether -i wlan0 --capture --bssid XX:XX:XX:XX:XX:XX

### Send targeted deauth packets

    sudo ./aether -i wlan0 --deauth --bssid XX:XX:XX:XX:XX:XX

### WPS audit (Pixie Dust)

    sudo ./aether -i wlan0 --wps --bssid XX:XX:XX:XX:XX:XX

### Create a Rogue AP

    sudo ./aether -i wlan0 --rogue MyFakeAP

### Bluetooth scan (classic + BLE)

    sudo ./aether --bluetooth

### Generate a report

    sudo ./aether -i wlan0 --scan -R report.html
    sudo ./aether -i wlan0 --scan -R report.json

---

## Output

HTML report: a dark-themed, self-contained page listing every detected
network with BSSID, SSID, channel, RSSI, encryption and WPS status.

JSON report: structured output suitable for scripting or SIEM ingestion.

---

## Architecture

    Aether/
    ├── Makefile
    ├── README.md
    ├── Aether_V1.md
    ├── LICENSE
    ├── .gitignore
    ├── include/
    │   ├── aether.h
    │   └── config.h
    └── src/
        ├── main.c
        ├── scan.c
        ├── capture.c
        ├── deauth.c
        ├── wps.c
        ├── rogue_ap.c
        ├── bluetooth.c
        └── report.c

---

## License

Educational and defensive use only.
MIT License - see LICENSE file.

---

## Author

iam-skb
