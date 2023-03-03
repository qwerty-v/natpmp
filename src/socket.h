#ifndef NAT_PMP_SOCKET_H
#define NAT_PMP_SOCKET_H

#include <sys/types.h>

int create_socket(const char *gw, int port);

ssize_t socket_send_and_recv(int sock, void* send_buf, size_t send_len, void* recv_buf, size_t recv_len);

#endif //NAT_PMP_SOCKET_H
