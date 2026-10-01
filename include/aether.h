#ifndef AETHER_H
#define AETHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

#include "config.h"

typedef struct {
    char bssid[MAX_BSSID_LEN];
    char ssid[MAX_SSID_LEN];
    int  channel;
    int  rssi;
    int  encryption;
    int  hidden;
    int  wps;
} wifi_network_t;

typedef struct {
    wifi_network_t networks[MAX_NETWORKS];
    int count;
} wifi_list_t;

typedef struct {
    char interface[MAX_BSSID_LEN];
    int  channel;
    int  timeout;
    int  verbose;
    int  token_valid;
} aether_config_t;

void aether_banner(void);
int  aether_check_token(void);
int  aether_scan(wifi_list_t *list, const char *iface);
int  aether_scan_simulated(wifi_list_t *list);
void aether_print_networks(const wifi_list_t *list);
int  aether_capture(const char *iface, const char *bssid, int channel);
int  aether_deauth(const char *iface, const char *bssid);
int  aether_wps_audit(const char *iface, const char *bssid);
int  aether_rogue_ap(const char *iface, const char *ssid, const char *channel);
int  aether_bluetooth_scan(int duration);
int  aether_bluetooth_info(const char *mac);
int  aether_report_html(const wifi_list_t *list, const char *filename);
int  aether_report_json(const wifi_list_t *list, const char *filename);

#endif
