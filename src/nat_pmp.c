#include "nat_pmp.h"
#include "socket.h"

#include <stdlib.h>

ssize_t nat_pmp_add_port_mapping(int sock, uint16_t internal_port, uint16_t external_port,
                                 uint32_t lifetime_in_secs, struct nat_pmp_resp_map *resp) {
    struct nat_pmp_req req;
    req.ver = 0;
    req.opcode = 1;
    req.reserved = 0;
    req.internal_port = htons(internal_port);
    req.external_port = htons(external_port);
    req.lifetime = htonl(lifetime_in_secs);

    return socket_send_and_recv(sock,
                                &req, sizeof(req),
                                resp, sizeof(struct nat_pmp_resp_map)
    );
}

ssize_t nat_pmp_delete_port_mapping(int sock, uint16_t internal_port, struct nat_pmp_resp_map *resp) {
    struct nat_pmp_req req;
    req.ver = 0;
    req.opcode = 1;
    req.reserved = 0;
    req.internal_port = htons(internal_port);
    req.external_port = 0;
    req.lifetime = 0;

    return socket_send_and_recv(sock,
                                &req, sizeof(req),
                                resp, sizeof(struct nat_pmp_resp_map)
    );
}

ssize_t nat_pmp_show_external_ip(int sock, struct nat_pmp_resp_ext *resp) {
    struct nat_pmp_req req;
    req.ver = 0;
    req.opcode = 0;

    return socket_send_and_recv(sock,
                                &req, sizeof(req.ver) + sizeof(req.opcode), // send only two fields
                                resp, sizeof(struct nat_pmp_resp_ext)
    );
}