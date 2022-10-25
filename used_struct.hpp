// neeede headers
#include <arpa/inet.h>



struct sockaddr {
	unsigned short sa_family; // address family, AF_xxx
	char sa_data[14]; // 14 bytes of protocol address
};

// sa_family => stores AF_INET for IPv4 addresses : => 127.25.12.11
// sa_data => stores destination address and port numbet for the socket

struct sockaddr_in {
	short int sin_family; // Address family
	unsigned short int sin_port; // Port number
	struct in_addr sin_addr; // Internet addressunsigned char sin_zero[8]; // Same size as struct sockaddr
	unsigned char sin_zero[8]; // same size as struct sockaddr
};


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(int argc, char *argv[])
{
	struct hostent *h;
	if (argc != 2) { // error check the command line
		fprintf(stderr,"usage: getip address\n");
		exit(1);
	}
	if ((h=gethostbyname(argv[1])) == NULL)
	{ // get the host info
		herror("gethostbyname");
		exit(1);
	}
	printf("Host name : %s\n", h->h_name);
	printf("IP Address : %s\n", inet_ntoa(*((struct in_addr *)h->h_addr)));
	return 0;
}