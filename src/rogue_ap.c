#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "aether.h"
#include "config.h"

int aether_rogue_ap(const char *iface, const char *ssid, const char *channel) {
    char command[512];

    if (strlen(iface) == 0) {
        fprintf(stderr, "[!] Interface required for Rogue AP.\n");
        return -1;
    }

    if (ssid == NULL || strlen(ssid) == 0) {
        fprintf(stderr, "[!] SSID required for Rogue AP.\n");
        return -1;
    }

    printf("[*] Creating Rogue AP '%s' on interface %s...\n", ssid, iface);

    snprintf(command, sizeof(command), "ip link set %s down", iface);
    system(command);
    snprintf(command, sizeof(command), "iw dev %s set type managed", iface);
    system(command);
    snprintf(command, sizeof(command), "ip link set %s up", iface);
    system(command);

    snprintf(command, sizeof(command), "ip addr add 10.0.0.1/24 dev %s", iface);
    system(command);

    char conf_path[64];
    snprintf(conf_path, sizeof(conf_path), "/tmp/aether_hostapd_%d.conf", getpid());

    FILE *fp = fopen(conf_path, "w");
    if (fp == NULL) {
        fprintf(stderr, "[!] Failed to create hostapd config.\n");
        return -1;
    }

    fprintf(fp, "interface=%s\n", iface);
    fprintf(fp, "driver=nl80211\n");
    fprintf(fp, "ssid=%s\n", ssid);
    fprintf(fp, "hw_mode=g\n");
    fprintf(fp, "channel=%s\n", channel ? channel : "6");
    fprintf(fp, "auth_algs=1\n");
    fprintf(fp, "ignore_broadcast_ssid=0\n");
    fclose(fp);

    printf("[*] Starting hostapd...\n");
    snprintf(command, sizeof(command), "hostapd %s", conf_path);

    printf("[*] Rogue AP running. Press Ctrl+C to stop.\n");
    int ret = system(command);

    snprintf(command, sizeof(command), "ip addr del 10.0.0.1/24 dev %s", iface);
    system(command);
    remove(conf_path);

    if (ret == 0) {
        printf("[+] Rogue AP stopped.\n");
    } else {
        fprintf(stderr, "[!] Rogue AP failed.\n");
    }

    return ret;
}
