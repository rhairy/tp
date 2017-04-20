/* tp.h */

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define TP_PORT 37

struct tp;

/* Initialize a tp socket. */
int tp_socket_open(int type);
/* Close a tp socket. */
int tp_socket_close(int socket_fd);
/* Connect to a tp server so it will send back the time value. */
int tp_socket_connect(int socket_fd, struct sockaddr* addr, socklen_t addr_len);
/* Receive a time value from a tp server. */
int tp_socket_receive(int socket_fd, void* buf, size_t len);
