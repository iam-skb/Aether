#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "aether.h"
#include "config.h"

/* Capture d'un handshake WPA/WPA2 */
int aether_capture(const char *iface, const char *bssid, int channel) {
    char command[512];
    char output_file[128];
    time_t now = time(NULL);

    if (strlen(iface) == 0) {
        fprintf(stderr, "[!] Interface required for capture.\n");
        return -1;
    }

    snprintf(output_file, sizeof(output_file),
             "capture_%s_%ld.cap", bssid, (long)now);
    for (char *p = output_file; *p; p++) {
        if (*p == ':') *p = '-';
    }

    printf("[*] Preparing capture on %s (channel %d)...\n", iface, channel);

    /* Mettre l'interface en mode monitor */
    snprintf(command, sizeof(command), "ip link set %s down", iface);
    if (system(command) != 0) {
        fprintf(stderr, "[!] Failed to bring interface down.\n");
        return -1;
    }

    snprintf(command, sizeof(command), "iw dev %s set type monitor", iface);
    if (system(command) != 0) {
        fprintf(stderr, "[!] Failed to set monitor mode.\n");
        return -1;
    }

    snprintf(command, sizeof(command), "ip link set %s up", iface);
    system(command);

    /* Fixer le canal */
    snprintf(command, sizeof(command), "iw dev %s set channel %d", iface, channel);
    system(command);

    printf("[*] Capturing handshake to %s...\n", output_file);
    printf("[*] Press Ctrl+C to stop.\n");

    /* Lancer airodump-ng ou tcpdump */
    snprintf(command, sizeof(command),
             "airodump-ng --bssid %s --channel %d --write %s %s",
             bssid, channel, output_file, iface);

    int ret = system(command);

    /* Restaurer le mode managed */
    snprintf(command, sizeof(command), "ip link set %s down", iface);
    system(command);
    snprintf(command, sizeof(command), "iw dev %s set type managed", iface);
    system(command);
    snprintf(command, sizeof(command), "ip link set %s up", iface);
    system(command);

    printf("[+] Capture finished. File: %s-01.cap\n", output_file);
    return ret;
}
