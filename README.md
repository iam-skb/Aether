# Aether

> AVERTISSEMENT : Usage exclusivement éducatif et défensif.
> Toute utilisation non autorisée est ILLÉGALE et engage votre responsabilité.

---

## Pourquoi Aether ?

Aether est un framework de sécurité sans fil écrit en C.
Il effectue le scan Wi-Fi, la capture de handshakes, l'audit WPS,
la simulation de Rogue AP et le scan Bluetooth pour des tests
d'intrusion autorisés.

Il est conçu pour les tests d'intrusion autorisés et les exercices Red Team.

---

## Modules (7)

| Catégorie | Modules |
|-----------|---------|
| Scan | Détection Wi-Fi (BSSID, SSID, canal, RSSI, chiffrement, WPS) |
| Capture | Capture de handshake WPA/WPA2 |
| Deauth | Envoi de paquets deauth ciblés |
| WPS | Audit WPS (attaque Pixie Dust) |
| Rogue AP | Point d'accès factice via hostapd |
| Bluetooth | Scan classique + BLE |
| Report | Rapport HTML ou JSON |

---

## Sécurité

Un token est obligatoire pour exécuter l'outil :

export AETHER_TOKEN="AETHER_AUTHORIZED"

---

## Installation

Prérequis : Linux (Kali, Parrot, Ubuntu), gcc, make,
libpcap-dev, aircrack-ng, reaver, hostapd, bluez.

git clone https://github.com/iam-skb/Aether.git
cd Aether
make

---

## Exemples d'utilisation

Vrai scan Wi-Fi (carte + root requis) :

sudo ./aether -i wlan0 --scan

Scan simulé (aucune carte requise) :

./aether --simulate --scan
./aether --simulate --scan -R rapport.html

Capture handshake :

sudo ./aether -i wlan0 --capture --bssid XX:XX:XX:XX:XX:XX

Deauth :

sudo ./aether -i wlan0 --deauth --bssid XX:XX:XX:XX:XX:XX

Audit WPS :

sudo ./aether -i wlan0 --wps --bssid XX:XX:XX:XX:XX:XX

Rogue AP :

sudo ./aether -i wlan0 --rogue MyFakeAP

Bluetooth :

sudo ./aether --bluetooth

Rapport :

sudo ./aether -i wlan0 --scan -R report.html

---

## Sortie

Rapport JSON ou HTML dans le dossier courant.

---

## Licence

Usage éducatif et défensif uniquement.

---

## Auteur

iam-skb
