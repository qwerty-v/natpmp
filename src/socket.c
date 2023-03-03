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

    if (connect(sock, (const struct sockaddr *) &gw_addr, sizeof(gw_addr)) < 0) {
        return -1;
    }

    return sock;
}

ssize_t socket_send_and_recv(int sock, void* send_buf, size_t send_len, void* recv_buf, size_t recv_len) {
    ssize_t send_result = send(sock, send_buf, send_len, 0);
    if (send_result < 0) {
        return send_result;
    }

    return recv(sock, recv_buf, recv_len, 0);
}