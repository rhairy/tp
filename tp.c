#include "tp.h"

typedef struct tp {
	int domain;
	int type;
	int socket_fd;
} tp;

int tp_init(tp* t, int domain, int type)
{
	t->domain = domain;
	t->type = type;
	t->socket_fd = socket(domain, type, 0);	
	if (t->socket_fd == -1) {
		return -1;
	} else {
		return 0;
	}
}
/*
int tp_socket_open(int type)
{
	int socket_fd;
	socket_fd = socket(AF_INET6, type, 0);
	return socket_fd;
}
*/
int tp_socket_close(int socket_fd)
{
	int res;
	res = close(socket_fd);
	return res;
}

int tp_socket_connect(int socket_fd, struct sockaddr* addr, socklen_t addr_len)
{
	int res;
	res = connect(socket_fd, addr, addr_len);
	return res;
}

int tp_socket_receive(int socket_fd, void* buf, size_t len)
{
	ssize_t res;
	char* cbuf = buf;
	while ( (res = recv(socket_fd, cbuf, len, 0)) > 0 ) {
		len -= res;
		cbuf += res;
	} 
	if (res == -1) {
		return -1;
	} else {
		return 0;
	} 
}
