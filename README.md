# Aether

> **Wireless security framework in C for authorized penetration testing.**
> For Red Team operations and Wi-Fi audits.

---

## Description

Aether is a wireless security framework written in C. It performs Wi-Fi scanning, handshake capture, WPS auditing, rogue access point simulation, and Bluetooth scanning for authorized security testing.

---

## Warning

**Authorized use only.** Always obtain written permission before scanning any wireless network.

---

## Build

```bash
git clone https://github.com/iam-skb/Aether.git
cd Aether
make

# Set authorization token
export AETHER_TOKEN="AETHER_AUTHORIZED"

# Scan Wi-Fi networks
sudo ./aether -i wlan0 --scan

# Simulation mode (no Wi-Fi card required)
./aether --simulate --scan
./aether --simulate --scan -R rapport.html

# Capture a handshake
sudo ./aether -i wlan0 --capture --bssid XX:XX:XX:XX:XX:XX

# Send deauth packets
sudo ./aether -i wlan0 --deauth --bssid XX:XX:XX:XX:XX:XX

# WPS audit (Pixie Dust)
sudo ./aether -i wlan0 --wps --bssid XX:XX:XX:XX:XX:XX

# Create a Rogue AP
sudo ./aether -i wlan0 --rogue MyFakeAP

# Bluetooth scan
sudo ./aether --bluetooth

# Generate a report
sudo ./aether -i wlan0 --scan --report report.html

Modules
Module	Description
Scan	Wi-Fi network scanning (BSSID, SSID, channel, RSSI, encryption, WPS)
Capture	WPA/WPA2 handshake capture
Deauth	Targeted deauthentication packets
WPS	WPS audit (Pixie Dust attack)
Rogue AP	Fake access point creation
Bluetooth	Classic and BLE device scanning
Report	HTML and JSON report generation
Simulation Mode

If you don't have a compatible Wi-Fi card (monitor mode), you can still test Aether using the --simulate flag. It returns fake networks so you can try the tool, generate reports, and understand how it works.
bash

./aether --simulate --scan
./aether --simulate --scan -R rapport.html

Requirements

    Linux (Kali, Parrot, Ubuntu)

    gcc, make

    libpcap-dev

    aircrack-ng, reaver, hostapd, bluez

Author

@iam-skb
text


3. **Commit** : `Update README with simulation mode`

---

## PDF : `Aether_V1.md`

1. Ouvre `Aether_V1.md` (crayon ✏️)
2. **Remplace tout** par :

```markdown
# AETHER V1 — DOCUMENTATION OFFICIELLE

> **Framework de sécurité sans fil en C pour tests d'intrusion autorisés.**
> Version publique — Open Source — Usage éducatif

---

## FICHE TECHNIQUE

| Élément | Détail |
|---------|--------|
| **Nom** | Aether |
| **Version** | 1.0 (Publique) |
| **Type** | Framework de sécurité sans fil |
| **Licence** | MIT (usage éducatif uniquement) |
| **Langage** | C |
| **Plateforme** | Linux |
| **Interface** | CLI |
| **Modules** | 7 + mode simulation |
| **Dépôt** | github.com/iam-skb/Aether |

---

## MODULES

### Scan
- Détection des réseaux Wi-Fi
- BSSID, SSID, canal, RSSI
- Détection du chiffrement (Open, WEP, WPA, WPA2, WPA3)
- Détection du WPS
- Détection des réseaux cachés

### Capture
- Capture de handshakes WPA/WPA2
- Mode monitor automatique
- Sauvegarde au format .cap

### Deauth
- Envoi de paquets deauth ciblés
- Mode monitor automatique
- Compatible avec aireplay-ng

### WPS
- Audit WPS
- Attaque Pixie Dust
- Récupération du PIN WPS

### Rogue AP
- Création d'un point d'accès factice
- Configuration hostapd automatique
- SSID personnalisable

### Bluetooth
- Scan des appareils Bluetooth classiques
- Scan BLE (Bluetooth Low Energy)
- Informations détaillées sur un appareil

### Report
- Génération de rapports HTML
- Génération de rapports JSON

### Mode Simulation
- Scan simulé sans carte Wi-Fi
- Parfait pour tester l'outil et générer des rapports
- Activé avec l'option `--simulate`

---

## SÉCURITÉ

| Mécanisme | Description |
|-----------|-------------|
| **Token** | Variable d'environnement AETHER_TOKEN obligatoire |
| **Root** | Nécessite les privilèges administrateur |

---

## INSTALLATION

```bash
git clone https://github.com/iam-skb/Aether.git
cd Aether
make

Dépendances :
bash

sudo apt install libpcap-dev aircrack-ng reaver hostapd bluez

UTILISATION
bash

export AETHER_TOKEN="AETHER_AUTHORIZED"

# Vrai scan (carte Wi-Fi requise)
sudo ./aether -i wlan0 --scan

# Scan simulé (aucune carte Wi-Fi requise)
./aether --simulate --scan
./aether --simulate --scan -R rapport.html

# Capture, deauth, WPS, rogue AP, bluetooth...
sudo ./aether -i wlan0 --capture --bssid XX:XX:XX:XX:XX:XX
sudo ./aether -i wlan0 --deauth --bssid XX:XX:XX:XX:XX:XX
sudo ./aether -i wlan0 --wps --bssid XX:XX:XX:XX:XX:XX
sudo ./aether -i wlan0 --rogue MyFakeAP
sudo ./aether --bluetooth

AVERTISSEMENT

Cet outil est fourni à des fins exclusivement éducatives et défensives.
Toute utilisation sur un réseau sans autorisation écrite est ILLÉGALE.
AUTEUR

@iam-skb — 
