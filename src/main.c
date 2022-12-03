#include "nat_pmp.h"
#include "options.h"
#include "socket.h"

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <assert.h>

void print_resp_result(struct nat_pmp_resp_hdr hdr) {
    char *status = "SUCCESS";
    if (hdr.result_code != 0) {
        status = "ERROR";
    }

    printf("Response result: %s (%d)\n", status, hdr.result_code);
}

void print_external_addr(uint32_t ip) {
    char addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ip, addr, INET_ADDRSTRLEN);

    printf("External address: %s\n", addr);
}

void print_external_port(uint16_t port) {
    printf("External port: %d\n", port);
}

void cleanup(int sock, void *resp) {
    close(sock);
    free(resp);
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
            cleanup(sock, resp);
            return -1;
        }

        print_resp_result(resp->hdr);
        print_external_addr(resp->ip);

        cleanup(sock, resp);
        return 0;
    } else if (opts.act == ACTION_ADD_MAPPING) {
        struct nat_pmp_resp_map *resp = calloc(1, sizeof(struct nat_pmp_resp_map));

        if (nat_pmp_add_port_mapping(sock, opts.internal_port, opts.external_port, opts.lifetime_in_secs, resp) < 0) {
            perror("nat_pmp_add_port_mapping");
            cleanup(sock, resp);
            return -1;
        }

        print_resp_result(resp->hdr);
        print_external_port(resp->external_port);

        cleanup(sock, resp);
        return 0;
    }

    assert(opts.act == ACTION_DELETE_MAPPING);

    struct nat_pmp_resp_map *resp = calloc(1, sizeof(struct nat_pmp_resp_map));

    if (nat_pmp_delete_port_mapping(sock, opts.internal_port, resp) < 0) {
        perror("nat_pmp_delete_port_mapping");
        cleanup(sock, resp);
        return -1;
    }

    print_resp_result(resp->hdr);

    cleanup(sock, resp);
    return 0;
}
