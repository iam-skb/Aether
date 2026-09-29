#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "aether.h"
#include "config.h"

/* Scan des réseaux Wi-Fi via iwlist (fallback) */
int aether_scan(wifi_list_t *list, const char *iface) {
    char command[256];
    char buffer[512];
    FILE *fp;

    list->count = 0;

    printf("[*] Scanning networks on interface %s...\n", iface);

    snprintf(command, sizeof(command), "iwlist %s scan 2>/dev/null", iface);
    fp = popen(command, "r");

    if (fp == NULL) {
        fprintf(stderr, "[!] Failed to run scan command.\n");
        return -1;
    }

    wifi_network_t current = {0};
    int in_cell = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, "Cell ") != NULL) {
            if (in_cell && list->count < MAX_NETWORKS) {
                list->networks[list->count++] = current;
            }
            memset(&current, 0, sizeof(current));
            in_cell = 1;

            char *addr = strstr(buffer, "Address: ");
            if (addr) {
                strncpy(current.bssid, addr + 9, MAX_BSSID_LEN - 1);
                current.bssid[MAX_BSSID_LEN - 1] = '\0';
            }
        }

        if (strstr(buffer, "ESSID:") != NULL) {
            char *start = strchr(buffer, '"');
            char *end = strrchr(buffer, '"');
            if (start && end && end > start) {
                size_t len = end - start - 1;
                if (len >= MAX_SSID_LEN) len = MAX_SSID_LEN - 1;
                strncpy(current.ssid, start + 1, len);
                current.ssid[len] = '\0';
            }
        }

        if (strstr(buffer, "Channel:") != NULL) {
            char *ch = strstr(buffer, "Channel:") + 8;
            current.channel = atoi(ch);
        }

        if (strstr(buffer, "Signal level=") != NULL) {
            char *sig = strstr(buffer, "Signal level=") + 13;
            current.rssi = atoi(sig);
        }

        if (strstr(buffer, "Encryption key:on") != NULL) {
            current.encryption = 2;
        }

        if (strstr(buffer, "WPA2") != NULL) {
            current.encryption = 3;
        } else if (strstr(buffer, "WPA3") != NULL) {
            current.encryption = 4;
        } else if (strstr(buffer, "WPA") != NULL) {
            current.encryption = 2;
        }

        if (strstr(buffer, "WPS") != NULL) {
            current.wps = 1;
        }
    }

    if (in_cell && list->count < MAX_NETWORKS) {
        list->networks[list->count++] = current;
    }

    pclose(fp);
    printf("[+] Found %d network(s).\n", list->count);
    return 0;
}

/* Affichage des réseaux */
void aether_print_networks(const wifi_list_t *list) {
    if (list->count == 0) {
        printf("[!] No networks found.\n");
        return;
    }

    printf("\n");
    printf("+-------------------+----------------------------------+---------+--------+------+------+\n");
    printf("| BSSID             | SSID                             | Channel | RSSI   | Enc  | WPS  |\n");
    printf("+-------------------+----------------------------------+---------+--------+------+------+\n");

    for (int i = 0; i < list->count; i++) {
        const wifi_network_t *n = &list->networks[i];
        const char *enc_str = "Open";
        if (n->encryption == 1) enc_str = "WEP";
        else if (n->encryption == 2) enc_str = "WPA";
        else if (n->encryption == 3) enc_str = "WPA2";
        else if (n->encryption == 4) enc_str = "WPA3";

        printf("| %-17s | %-32s | %-7d | %-6d | %-4s | %-4s |\n",
               n->bssid,
               n->ssid[0] ? n->ssid : "(hidden)",
               n->channel,
               n->rssi,
               enc_str,
               n->wps ? "Yes" : "No");
    }

    printf("+-------------------+----------------------------------+---------+--------+------+------+\n");
    printf("\n");
}
