/* tp.h */

#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define TP_PORT 37
#define UDP 1
#define TCP 0

ssize_t recvall(int sockfd, void* buf, size_t len, int flags);
int tp_client_gettime(const char* addr, const int proto, uint32_t* time);
