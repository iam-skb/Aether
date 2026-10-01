#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "aether.h"
#include "config.h"

int aether_bluetooth_scan(int duration) {
    char command[256];

    printf("[*] Starting Bluetooth scan (duration: %d seconds)...\n", duration);

    printf("[*] Checking Bluetooth adapter...\n");
    if (system("hciconfig hci0 > /dev/null 2>&1") != 0) {
        fprintf(stderr, "[!] No Bluetooth adapter detected (hci0).\n");
        return -1;
    }

    printf("[*] Enabling Bluetooth adapter...\n");
    system("hciconfig hci0 up");
    system("hciconfig hci0 piscan");

    printf("[*] Scanning classic Bluetooth devices...\n");
    snprintf(command, sizeof(command),
             "timeout %d hcitool scan", duration);
    system(command);

    printf("[*] Scanning BLE devices...\n");
    snprintf(command, sizeof(command),
             "timeout %d hcitool lescan", duration);
    system(command);

    printf("\n[*] Known Bluetooth devices:\n");
    system("hcitool con");

    printf("\n[+] Bluetooth scan completed.\n");
    return 0;
}

int aether_bluetooth_info(const char *mac) {
    char command[256];

    if (mac == NULL || strlen(mac) == 0) {
        fprintf(stderr, "[!] MAC address required.\n");
        return -1;
    }

    printf("[*] Getting info for device %s...\n", mac);

    snprintf(command, sizeof(command), "hcitool info %s", mac);
    system(command);

    snprintf(command, sizeof(command), "sdptool browse %s", mac);
    system(command);

    printf("[+] Device info retrieved.\n");
    return 0;
}
