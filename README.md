# Aether

> **Wireless security framework in C for authorized penetration testing.**
> For Red Team operations and Wi-Fi audits.

---

## Description

Aether is a wireless security framework written in C. It performs Wi-Fi scanning, handshake capture, WPS auditing, and rogue access point simulation for authorized security testing.

---

## Warning

**Authorized use only.** Always obtain written permission before scanning any wireless network.

---

## Build

```bash
git clone https://github.com/theanonspider/Aether.git
cd Aether
make
sudo ./aether --scan
sudo ./aether --capture --bssid XX:XX:XX:XX:XX:XX --channel 6

