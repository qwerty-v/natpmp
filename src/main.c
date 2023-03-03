#include "nat_pmp.h"
#include "options.h"
#include "socket.h"
#include "mem_area.h"

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>

void print_resp_header(struct nat_pmp_resp_hdr hdr) {
    char *status = "SUCCESS";
    if (hdr.result_code != 0) {
        status = "ERROR";
    }

    printf("Response result: %s (%d)\n", status, hdr.result_code);
}

void print_external_ip(uint32_t ip) {
    char addr[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ip, addr, INET_ADDRSTRLEN);

    printf("External address: %s\n", addr);
}

void print_external_port(uint16_t port) {
    printf("External port: %d\n", port);
}

int show_external_ip(struct mem_area *area, int sock) {
    struct nat_pmp_resp_ext *resp = mem_area_calloc(area, 1, sizeof(struct nat_pmp_resp_ext));

    if (nat_pmp_show_external_ip(sock, resp) < 0) {
        perror("nat_pmp_show_external_ip");
        return -1;
    }

    print_resp_header(resp->hdr);
    print_external_ip(resp->ip);

    return 0;
}

int add_mapping(struct mem_area *area, int sock, struct options opts) {
    struct nat_pmp_resp_map *resp = mem_area_calloc(area, 1, sizeof(struct nat_pmp_resp_map));

    if (nat_pmp_add_port_mapping(sock, opts.internal_port, opts.external_port, opts.lifetime_in_secs, resp) < 0) {
        perror("nat_pmp_add_port_mapping");
        return -1;
    }

    print_resp_header(resp->hdr);
    print_external_port(resp->external_port);

    return 0;
}

int delete_mapping(struct mem_area *area, int sock, struct options opts) {
    struct nat_pmp_resp_map *resp = mem_area_calloc(area, 1, sizeof(struct nat_pmp_resp_map));

    if (nat_pmp_delete_port_mapping(sock, opts.internal_port, resp) < 0) {
        perror("nat_pmp_delete_port_mapping");
        return -1;
    }

    print_resp_header(resp->hdr);

    return 0;
}

int main_mem_area(struct mem_area *area, int argc, char *argv[]) {
    struct options opts = parse_argv(argc, argv);

    int sock = create_socket(opts.gateway, opts.gw_port);
    if (sock < 0) {
        return -1;
    }

    if (opts.act == ACTION_SHOW_EXTERNAL_IP) {
        return show_external_ip(area, sock);
    } else if (opts.act == ACTION_ADD_MAPPING) {
        return add_mapping(area, sock, opts);
    }

    assert(opts.act == ACTION_DELETE_MAPPING);
    return delete_mapping(area, sock, opts);
}

int main(int argc, char *argv[]) {
    struct mem_area *area = mem_area_create();

    int ret = main_mem_area(area, argc, argv);

    mem_area_free(area);
    return ret;
}
