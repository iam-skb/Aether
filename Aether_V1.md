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
| **Modules** | 7 |
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
sudo ./aether -i wlan0 --scan
sudo ./aether -i wlan0 --capture --bssid XX:XX:XX:XX:XX:XX
sudo ./aether -i wlan0 --deauth --bssid XX:XX:XX:XX:XX:XX
sudo ./aether -i wlan0 --wps --bssid XX:XX:XX:XX:XX:XX
sudo ./aether -i wlan0 --rogue MyFakeAP
sudo ./aether --bluetooth
sudo ./aether -i wlan0 --scan --report report.html

AVERTISSEMENT

Cet outil est fourni à des fins exclusivement éducatives et défensives.
Toute utilisation sur un réseau sans autorisation écrite est ILLÉGALE.
AUTEUR

@iam-skb
