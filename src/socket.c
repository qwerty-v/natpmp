#include "socket.h"

#include <sys/socket.h>
#include <arpa/inet.h>

int create_socket(const char *gw, int port) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        return -1;
    }

    struct sockaddr_in gw_addr;
    gw_addr.sin_family = AF_INET;
    gw_addr.sin_port = htons(port);
    gw_addr.sin_addr.s_addr = inet_addr(gw);

    if (connect(sock, (const struct sockaddr *) &gw_addr, sizeof(gw)) < 0) {
        return -1;
    }

    return sock;
}