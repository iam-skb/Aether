#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "aether.h"
#include "config.h"

void aether_banner(void) {
    printf("\n");
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|   AETHER - Wireless Framework                |\n");
    printf("|   Version %s                          |\n", AETHER_VERSION);
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");
    printf("\n");
}

int aether_check_token(void) {
    const char *env = getenv("AETHER_TOKEN");
    if (env == NULL) {
        fprintf(stderr, "[!] Token manquant. Definir AETHER_TOKEN.\n");
        return 0;
    }
    if (strcmp(env, AETHER_TOKEN) != 0) {
        fprintf(stderr, "[!] Token invalide.\n");
        return 0;
    }
    return 1;
}

void usage(const char *prog) {
    printf("Usage: %s [OPTIONS]\n", prog);
    printf("\nOptions:\n");
    printf("  -i, --interface <iface>   Interface Wi-Fi (ex: wlan0)\n");
    printf("  -s, --scan                Scanner les reseaux Wi-Fi\n");
    printf("  -c, --capture             Capturer un handshake\n");
    printf("  -b, --bssid <bssid>       BSSID cible\n");
    printf("  -d, --deauth              Envoyer des paquets deauth\n");
    printf("  -w, --wps                 Audit WPS (Pixie Dust)\n");
    printf("  -r, --rogue <ssid>        Creer un Rogue AP\n");
    printf("  -B, --bluetooth           Scanner les appareils Bluetooth\n");
    printf("  -R, --report <file>       Generer un rapport (HTML ou JSON)\n");
    printf("  -h, --help                Afficher cette aide\n");
    printf("  -v, --version             Afficher la version\n");
    printf("\n");
}

int main(int argc, char *argv[]) {
    aether_config_t config = {0};
    wifi_list_t network_list = {0};
    int opt;
    int do_scan = 0, do_capture = 0, do_deauth = 0, do_wps = 0, do_rogue = 0, do_bluetooth = 0, do_report = 0;
    char *bssid = NULL;
    char *rogue_ssid = NULL;
    char *report_file = NULL;

    static struct option long_options[] = {
        {"interface", required_argument, 0, 'i'},
        {"scan",      no_argument,       0, 's'},
        {"capture",   no_argument,       0, 'c'},
        {"bssid",     required_argument, 0, 'b'},
        {"deauth",    no_argument,       0, 'd'},
        {"wps",       no_argument,       0, 'w'},
        {"rogue",     required_argument, 0, 'r'},
        {"bluetooth", no_argument,       0, 'B'},
        {"report",    required_argument, 0, 'R'},
        {"help",      no_argument,       0, 'h'},
        {"version",   no_argument,       0, 'v'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "i:scb:dhwr:BR:v", long_options, NULL)) != -1) {
        switch (opt) {
            case 'i': strncpy(config.interface, optarg, sizeof(config.interface) - 1); break;
            case 's': do_scan = 1; break;
            case 'c': do_capture = 1; break;
            case 'b': bssid = optarg; break;
            case 'd': do_deauth = 1; break;
            case 'w': do_wps = 1; break;
            case 'r': do_rogue = 1; rogue_ssid = optarg; break;
            case 'B': do_bluetooth = 1; break;
            case 'R': do_report = 1; report_file = optarg; break;
            case 'h': usage(argv[0]); return 0;
            case 'v': printf("Aether %s\n", AETHER_VERSION); return 0;
            default:  usage(argv[0]); return 1;
        }
    }

    aether_banner();

    if (!aether_check_token()) {
        return 1;
    }

    if (do_scan) {
        if (strlen(config.interface) == 0) {
            fprintf(stderr, "[!] Interface requise pour le scan (-i).\n");
            return 1;
        }
        aether_scan(&network_list, config.interface);
        aether_print_networks(&network_list);
    }

    if (do_capture) {
        if (bssid == NULL) {
            fprintf(stderr, "[!] BSSID requis pour la capture (-b).\n");
            return 1;
        }
        aether_capture(config.interface, bssid, DEFAULT_CHANNEL);
    }

    if (do_deauth) {
        if (bssid == NULL) {
            fprintf(stderr, "[!] BSSID requis pour le deauth (-b).\n");
            return 1;
        }
        aether_deauth(config.interface, bssid);
    }

    if (do_wps) {
        if (bssid == NULL) {
            fprintf(stderr, "[!] BSSID requis pour l'audit WPS (-b).\n");
            return 1;
        }
        aether_wps_audit(config.interface, bssid);
    }

    if (do_rogue) {
        if (rogue_ssid == NULL) {
            fprintf(stderr, "[!] SSID requis pour le Rogue AP (-r).\n");
            return 1;
        }
        aether_rogue_ap(config.interface, rogue_ssid, "6");
    }

    if (do_bluetooth) {
        aether_bluetooth_scan(DEFAULT_TIMEOUT);
    }

    if (do_report) {
        if (report_file == NULL) {
            fprintf(stderr, "[!] Nom de fichier requis pour le rapport (-R).\n");
            return 1;
        }
        if (strstr(report_file, ".json") != NULL) {
            aether_report_json(&network_list, report_file);
        } else {
            aether_report_html(&network_list, report_file);
        }
    }

    if (!do_scan && !do_capture && !do_deauth && !do_wps && !do_rogue && !do_bluetooth && !do_report) {
        usage(argv[0]);
    }

    return 0;
}
