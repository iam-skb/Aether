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

# Modules

    Wi-Fi Scanner

    Handshake Capture

    WPS Auditor

    Deauth Module

    Rogue AP

# Author
@iam-skb


3. **Commit** : `Update README`

---

### Fichier : `Makefile`

1. **Add file** → **Create new file**
2. Nom : `Makefile`
3. Colle :

```makefile
CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
LDFLAGS = -lpcap -lpthread
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TARGET = aether

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

install:
	cp $(TARGET) /usr/local/bin/

.PHONY: all clean install

