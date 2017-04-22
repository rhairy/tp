#include "tp.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[])
{
	uint32_t net_time;
	tp_client_gettime(argv[1], UDP, &net_time);
	printf("Network: %x\n", net_time);
	return 0;
}
