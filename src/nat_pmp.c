#include "nat_pmp.h"

#include <netinet/in.h>
#include <stdlib.h>

int nat_pmp_add_port_mapping(int sock, uint16_t internal_port, uint16_t external_port,
                             uint32_t lifetime_in_secs, struct nat_pmp_resp_map* resp) {
    struct nat_pmp_req req;
    req.ver = 0;
    req.opcode = 1;
    req.reserved = 0;
    req.internal_port = htons(internal_port);
    req.external_port = htons(external_port);
    req.lifetime = htonl(lifetime_in_secs);

    if (send(sock, &req, sizeof(req), 0) < 0) {
        return -1;
    }

    int n = (int) recv(sock, resp, sizeof(struct nat_pmp_resp_map), 0);
    if (n < 0) {
        return -1;
    }

    return n;
}

int nat_pmp_delete_port_mapping(int sock, uint16_t internal_port, struct nat_pmp_resp_map* resp) {
    struct nat_pmp_req req;
    req.ver = 0;
    req.opcode = 1;
    req.reserved = 0;
    req.internal_port = htons(internal_port);
    req.external_port = 0;
    req.lifetime = 0;

    if (send(sock, &req, sizeof(req), 0) < 0) {
        return -1;
    }

    int n = (int) recv(sock, resp, sizeof(struct nat_pmp_resp_map), 0);
    if (n < 0) {
        return -1;
    }

    return n;
}

int nat_pmp_show_external_ip(int sock, struct nat_pmp_resp_ext *resp) {
    struct nat_pmp_req req;
    req.ver = 0;
    req.opcode = 0;

    if (send(sock, &req, sizeof(req.ver) + sizeof(req.opcode), 0) < 0) {
        return -1;
    }

    int n = (int) recv(sock, resp, sizeof(struct nat_pmp_resp_ext), 0);
    if (n < 0) {
        return -1;
    }

    return n;
}