#ifndef AETHER_H
#define AETHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "config.h"

/* Structure représentant un réseau Wi-Fi détecté */
typedef struct {
    char bssid[MAX_BSSID_LEN];
    char ssid[MAX_SSID_LEN];
    int  channel;
    int  rssi;
    int  encryption;   /* 0=Open, 1=WEP, 2=WPA, 3=WPA2, 4=WPA3 */
    int  hidden;
    int  wps;
} wifi_network_t;

/* Structure pour stocker une liste de réseaux */
typedef struct {
    wifi_network_t networks[MAX_NETWORKS];
    int count;
} wifi_list_t;

/* Structure de configuration globale */
typedef struct {
    char interface[MAX_BSSID_LEN];
    int  channel;
    int  timeout;
    int  verbose;
    int  token_valid;
} aether_config_t;

/* Prototypes des fonctions principales */
void aether_banner(void);
int  aether_check_token(void);
int  aether_scan(wifi_list_t *list, const char *iface);
void aether_print_networks(const wifi_list_t *list);
int  aether_capture(const char *iface, const char *bssid, int channel);
int  aether_deauth(const char *iface, const char *bssid);
int  aether_wps_audit(const char *iface, const char *bssid);

#endif /* AETHER_H */
