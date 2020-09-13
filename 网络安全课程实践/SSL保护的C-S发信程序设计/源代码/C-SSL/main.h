#include <iostream>
#include <errno.h>
#include <string.h>

#ifdef _WIN64	
#include <winsock.h>
#define	socklen_t int
#define bzero(buf, len) memset(buf, 0, len)
#else			
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define closesocket close
#endif

#include <openssl/ssl.h>
#include <openssl/err.h>

#define MAXBUF 1024 

int inet_aton(char* str, struct in_addr* addr){
	u_long a;
	a = inet_addr(str);
	*(int*)addr = a;
	return a;
}