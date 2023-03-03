#ifndef NAT_PMP_NAT_PMP_H
#define NAT_PMP_NAT_PMP_H

#include <stdint.h>
#include <sys/types.h>

struct nat_pmp_req {
    uint8_t ver;
    uint8_t opcode;
    uint16_t reserved;
    uint16_t internal_port;
    uint16_t external_port;
    uint32_t lifetime; // in seconds
};

struct nat_pmp_resp_hdr {
    uint8_t ver;
    uint8_t opcode;
    uint16_t result_code;
    uint32_t sssoe; // Seconds Since Start of Epoch
};

struct nat_pmp_resp_map {
    struct nat_pmp_resp_hdr hdr;
    uint16_t internal_port;
    uint16_t external_port;
    uint32_t lifetime; // in seconds
};

struct nat_pmp_resp_ext {
    struct nat_pmp_resp_hdr hdr;
    uint32_t ip;
};

ssize_t nat_pmp_add_port_mapping(int, uint16_t, uint16_t, uint32_t, struct nat_pmp_resp_map *);

ssize_t nat_pmp_delete_port_mapping(int, uint16_t, struct nat_pmp_resp_map *);

ssize_t nat_pmp_show_external_ip(int, struct nat_pmp_resp_ext *);

#endif //NAT_PMP_NAT_PMP_H
