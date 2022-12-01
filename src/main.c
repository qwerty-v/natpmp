#include "nat_pmp.h"
#include "options.h"
#include "socket.h"

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void print_result(struct nat_pmp_resp_hdr hdr) {
    char *status = "SUCCESS";
    if (hdr.result_code != 0) {
        status = "ERROR";
    }

    printf("Response result %s (%d)\n", status, hdr.result_code);
}

int main(int argc, char *argv[]) {
    struct options opts = parse_argv(argc, argv);

    int sock = create_socket(opts.gateway, opts.gw_port);
    if (sock < 0) {
        return -1;
    }

    if (opts.act == ACTION_SHOW_EXTERNAL_IP) {
        struct nat_pmp_resp_ext *resp = calloc(1, sizeof(struct nat_pmp_resp_ext));
        if (nat_pmp_show_external_ip(sock, resp) < 0) {
            perror("nat_pmp_show_external_ip");
            free(resp);
            return -1;
        }

        print_result(resp->hdr);

        char addr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &resp->ip, addr, INET_ADDRSTRLEN);

        printf("External address: %s\n", addr);
        free(resp);
        return 0;
    }

    struct nat_pmp_resp_map *resp = calloc(1, sizeof(struct nat_pmp_resp_map));
    if (opts.act == ACTION_ADD_MAPPING) {
        if (nat_pmp_add_port_mapping(sock, opts.internal_port, opts.external_port, opts.lifetime_in_secs, resp) < 0) {
            perror("nat_pmp_add_port_mapping");
            free(resp);
            return -1;
        }
    } else {
        if (nat_pmp_delete_port_mapping(sock, opts.internal_port, resp) < 0) {
            perror("nat_pmp_delete_port_mapping");
            free(resp);
            return -1;
        }
    }

    print_result(resp->hdr);
    free(resp);
    return 0;
}
