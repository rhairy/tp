#include "tp.h"

ssize_t recvall(int sockfd, void* buf, size_t len, int flags)
{
	ssize_t res;
	while ( (res = recv(sockfd, buf, len, flags)) > 0 && len > 0 ) {
		buf += res;
		len -= res;
	}
	return res;
}

int tp_client_gettime(const char* addr, const int proto, uint32_t* time)
{
	int res, sock_fd, type;
	ssize_t rec;
	struct addrinfo* a, *b;
	
	if (proto == TCP) {
		type = SOCK_STREAM;
	} else if (proto == UDP) {
		type = SOCK_DGRAM;
	} else {
		return -1;
	}

	res = getaddrinfo(addr, "time", NULL, &a);
	if (res) {
		return -1;
	}

	for (b = a; b != NULL; b = b->ai_next) {
		sock_fd = socket(b->ai_addr->sa_family, type, 0);	
		if (sock_fd == -1) {
			continue;
		}
		break;
	}

	res = connect(sock_fd, b->ai_addr, b->ai_addrlen);
	if (res == -1) {
		freeaddrinfo(a);
		close(sock_fd);
		return -1;
	}
	if (type == SOCK_STREAM) {
		rec = recvall(sock_fd, time, sizeof(uint32_t), 0);	
	} else {
		//rec = send(sock_fd, time, sizeof(uint32_t), 0);
		rec = recv(sock_fd, time, sizeof(uint32_t), 0);
	}
	if (rec == -1) {
		freeaddrinfo(a);
		close(sock_fd);
		return -1;
	}
	freeaddrinfo(a);
	close(sock_fd);
	*time = ntohl(*time);
	return 0;
}
