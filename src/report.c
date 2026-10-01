#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "aether.h"
#include "config.h"

int aether_report_html(const wifi_list_t *list, const char *filename) {
    FILE *fp;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    if (list == NULL || list->count == 0) {
        fprintf(stderr, "[!] No networks to report.\n");
        return -1;
    }

    fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "[!] Failed to create report file.\n");
        return -1;
    }

    fprintf(fp, "<!DOCTYPE html>\n");
    fprintf(fp, "<html lang=\"en\">\n<head>\n");
    fprintf(fp, "<meta charset=\"UTF-8\">\n");
    fprintf(fp, "<title>Aether Report</title>\n");
    fprintf(fp, "<style>\n");
    fprintf(fp, "body{background:#0a0a0f;color:#ccc;font-family:monospace;max-width:1000px;margin:40px auto;padding:20px;}\n");
    fprintf(fp, "h1{color:#9b59b6;}\n");
    fprintf(fp, "table{width:100%%;border-collapse:collapse;margin-top:20px;}\n");
    fprintf(fp, "th{text-align:left;color:#9b59b6;padding:10px;border-bottom:1px solid #2a1a3e;}\n");
    fprintf(fp, "td{padding:10px;border-bottom:1px solid #1a1a2e;}\n");
    fprintf(fp, ".footer{margin-top:40px;color:#444;text-align:center;font-size:.8em;}\n");
    fprintf(fp, "</style>\n</head>\n<body>\n");

    fprintf(fp, "<h1>Aether - Wireless Report</h1>\n");
    fprintf(fp, "<p>Generated: %04d-%02d-%02d %02d:%02d:%02d</p>\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);
    fprintf(fp, "<p>Total networks: %d</p>\n", list->count);

    fprintf(fp, "<table>\n");
    fprintf(fp, "<tr><th>BSSID</th><th>SSID</th><th>Channel</th><th>RSSI</th><th>Encryption</th><th>WPS</th></tr>\n");

    for (int i = 0; i < list->count; i++) {
        const wifi_network_t *n = &list->networks[i];
        const char *enc = "Open";
        if (n->encryption == 1) enc = "WEP";
        else if (n->encryption == 2) enc = "WPA";
        else if (n->encryption == 3) enc = "WPA2";
        else if (n->encryption == 4) enc = "WPA3";

        fprintf(fp, "<tr><td>%s</td><td>%s</td><td>%d</td><td>%d</td><td>%s</td><td>%s</td></tr>\n",
                n->bssid,
                n->ssid[0] ? n->ssid : "(hidden)",
                n->channel,
                n->rssi,
                enc,
                n->wps ? "Yes" : "No");
    }

    fprintf(fp, "</table>\n");
    fprintf(fp, "<div class=\"footer\">Aether - Educational Use Only</div>\n");
    fprintf(fp, "</body>\n</html>\n");

    fclose(fp);
    printf("[+] Report saved: %s\n", filename);
    return 0;
}

int aether_report_json(const wifi_list_t *list, const char *filename) {
    FILE *fp;

    if (list == NULL || list->count == 0) {
        fprintf(stderr, "[!] No networks to report.\n");
        return -1;
    }

    fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "[!] Failed to create report file.\n");
        return -1;
    }

    fprintf(fp, "{\n");
    fprintf(fp, "  \"total\": %d,\n", list->count);
    fprintf(fp, "  \"networks\": [\n");

    for (int i = 0; i < list->count; i++) {
        const wifi_network_t *n = &list->networks[i];
        fprintf(fp, "    {\n");
        fprintf(fp, "      \"bssid\": \"%s\",\n", n->bssid);
        fprintf(fp, "      \"ssid\": \"%s\",\n", n->ssid);
        fprintf(fp, "      \"channel\": %d,\n", n->channel);
        fprintf(fp, "      \"rssi\": %d,\n", n->rssi);
        fprintf(fp, "      \"encryption\": %d,\n", n->encryption);
        fprintf(fp, "      \"wps\": %s\n", n->wps ? "true" : "false");
        fprintf(fp, "    }%s\n", (i < list->count - 1) ? "," : "");
    }

    fprintf(fp, "  ]\n");
    fprintf(fp, "}\n");

    fclose(fp);
    printf("[+] JSON report saved: %s\n", filename);
    return 0;
}
