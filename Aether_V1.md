# Aether V1 - Documentation

Wireless security framework in C for authorized penetration testing.

---

## Warning

This tool is provided for educational and defensive purposes only.
Unauthorized use is illegal. The author assumes no responsibility
for misuse.

---

## Technical Sheet

| Field | Value |
|-------|-------|
| Name | Aether |
| Version | 1.0 (Public) |
| Type | Wireless security framework |
| Language | C |
| Platform | Linux |
| Interface | CLI |
| Modules | 7 (+ simulation mode) |
| License | MIT (educational use only) |
| Repository | github.com/iam-skb/Aether |

---

## Modules

### Scan
- Wi-Fi network detection
- BSSID, SSID, channel, RSSI
- Encryption detection (Open, WEP, WPA, WPA2, WPA3)
- WPS detection
- Hidden SSID detection

### Capture
- WPA/WPA2 handshake capture
- Automatic monitor mode
- Save as .cap file

### Deauth
- Targeted deauthentication packets
- Automatic monitor mode
- Compatible with aireplay-ng

### WPS
- WPS audit
- Pixie Dust attack
- WPS PIN recovery

### Rogue AP
- Fake access point creation
- Automatic hostapd configuration
- Custom SSID

### Bluetooth
- Classic Bluetooth scanning
- BLE (Bluetooth Low Energy) scanning
- Detailed device information

### Report
- HTML report generation
- JSON report generation

### Simulation Mode
- Simulated scan without Wi-Fi card
- Useful for testing the tool and generating reports
- Enabled with the --simulate flag

---

## Security

| Mechanism | Description |
|-----------|-------------|
| Token | AETHER_TOKEN environment variable required |
| Root | Requires administrator privileges |

---

## Installation

    git clone https://github.com/iam-skb/Aether.git
    cd Aether
    make

Dependencies:

    sudo apt install libpcap-dev aircrack-ng reaver hostapd bluez

---

## Usage

    export AETHER_TOKEN="AETHER_AUTHORIZED"

    # Real scan (Wi-Fi card required)
    sudo ./aether -i wlan0 --scan

    # Simulated scan (no Wi-Fi card required)
    ./aether --simulate --scan
    ./aether --simulate --scan -R rapport.html

    # Other modules
    sudo ./aether -i wlan0 --capture --bssid XX:XX:XX:XX:XX:XX
    sudo ./aether -i wlan0 --deauth --bssid XX:XX:XX:XX:XX:XX
    sudo ./aether -i wlan0 --wps --bssid XX:XX:XX:XX:XX:XX
    sudo ./aether -i wlan0 --rogue MyFakeAP
    sudo ./aether --bluetooth

---

## License

Educational and defensive use only.

---

## Author

iam-skb

---

Document generated on October 1, 2026.
