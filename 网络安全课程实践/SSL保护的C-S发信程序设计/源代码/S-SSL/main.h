#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#ifdef _WIN64	
#include <winsock.h>
#define	socklen_t int
#define bzero(buf, len) memset(buf, 0, len)
#else			
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#define closesocket close
#endif


#include <openssl/ssl.h>
#include <openssl/err.h>

#define MAXBUF 1024 
