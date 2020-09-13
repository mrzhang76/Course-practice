#include "main.h"
using namespace std;
int main(int argc, char** argv) { 
	if (argc != 4) {cout << "Usage: port certfile privkeyfile" << endl;exit(1);}

	int sockfd = 0;
	int client_fd = 0;
	socklen_t len;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	u_int server_port;
	char buffer[MAXBUF + 1];
	SSL_CTX* ctx;
	//为SSL加载加密和哈希算法
	if (SSL_library_init() != 1)
		cout << "" << endl;
	OpenSSL_add_all_algorithms(); 
	//加载错误码的描述字符串
	SSL_load_error_strings();
	//创建SSL上下文接口
	if ((ctx = SSL_CTX_new(SSLv23_server_method())) == NULL) { ERR_print_errors_fp(stdout);exit(1);}
	//加载PEM证书文件
	if(SSL_CTX_use_certificate_file(ctx,argv[2],SSL_FILETYPE_PEM) <= 0){ ERR_print_errors_fp(stdout); exit(1); }
	//加载用户私钥
	if(SSL_CTX_use_PrivateKey_file(ctx, argv[3], SSL_FILETYPE_PEM) <= 0){ ERR_print_errors_fp(stdout); exit(1); }
	//验证私钥和证书是否相符
	if (SSL_CTX_check_private_key(ctx) != TRUE) { ERR_print_errors_fp(stdout); exit(1); }

#ifdef _WIN64
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
#endif

	//创建套接字
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) { perror("socket create failed"); exit(1); }
	else cout << " socket create success" << endl;

	server_port = atoi(argv[1]);
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(server_port);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	//绑定套接字
	if (bind(sockfd, (struct sockaddr*) & server_addr, sizeof(struct sockaddr)) == -1) { perror("bind  failed"); exit(1); }
	else cout << " bind success" << endl;

	//进行监听
	if (listen(sockfd, 2) == -1) { perror(" begin listen failed"); exit(1); }
	else cout << " begin listen success " << endl;

	//循环处理接收到的数据包
	while (1) {
		SSL* ssl;
		len = sizeof(struct sockaddr);
		//接收一个连接
		if ((client_fd = accept(sockfd, (struct sockaddr*) & client_addr, &len)) == -1) { perror("accept failed"); exit(errno); }
		else {
			cout << " SERVER GET CONNECTION FROM: " << inet_ntoa(client_addr.sin_addr)
				 << " PORT: " << ntohs(client_addr.sin_port)
				 << " SOCKET: " << client_fd
				 << endl;
		}
		//创建SSL套接字
		ssl = SSL_new(ctx);
		//申请SSL套接字
		SSL_set_fd(ssl, client_fd);
		//进行SSL握手
		if (SSL_accept(ssl) == -1) { perror(" ssl accept error "); closesocket(client_fd); break; }
		bzero(buffer, MAXBUF + 1);
		strcpy(buffer," SERVER LISTENING... ");
		//进行套接字读写
		if ((len = SSL_write(ssl, buffer, strlen(buffer))) <= 0)
			cout << " SEND INFORMATION: " << buffer 
				 << " FAILED, ERORR CODE: " << errno
				 << " ERROR INFORMATION: " << strerror(errno)
			<<endl;
		else
			cout << " SEND INFORMATION: " << buffer
			<< " SUCCESS, INFORMATION LEN: " << len
			<< endl;

		bzero(buffer, MAXBUF + 1);
		if(len = SSL_read(ssl, buffer, MAXBUF) > 0)
			cout << " RECEIVE INFORMATION SUCCESS: " << buffer
			<< " INFORMATION LEN: " << len
			<< endl;
		else
			cout << " RECEIVE INFORMATION FAILED , ERORR CODE: " << errno
			<< " ERROR INFORMATION: " << strerror(errno)
			<< endl;
		//释放SSL资源
		SSL_shutdown(ssl);
		//关闭SSL套接字
		SSL_free(ssl);
		//关闭套接字
		closesocket(client_fd);
	}
	//释放SSL套接字
	SSL_CTX_free(ctx);
	//关闭套接字
	closesocket(sockfd);

	return 0;

}