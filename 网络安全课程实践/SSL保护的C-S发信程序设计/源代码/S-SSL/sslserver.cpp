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
	//ΪSSL���ؼ��ܺ͹�ϣ�㷨
	if (SSL_library_init() != 1)
		cout << "" << endl;
	OpenSSL_add_all_algorithms(); 
	//���ش�����������ַ���
	SSL_load_error_strings();
	//����SSL�����Ľӿ�
	if ((ctx = SSL_CTX_new(SSLv23_server_method())) == NULL) { ERR_print_errors_fp(stdout);exit(1);}
	//����PEM֤���ļ�
	if(SSL_CTX_use_certificate_file(ctx,argv[2],SSL_FILETYPE_PEM) <= 0){ ERR_print_errors_fp(stdout); exit(1); }
	//�����û�˽Կ
	if(SSL_CTX_use_PrivateKey_file(ctx, argv[3], SSL_FILETYPE_PEM) <= 0){ ERR_print_errors_fp(stdout); exit(1); }
	//��֤˽Կ��֤���Ƿ����
	if (SSL_CTX_check_private_key(ctx) != TRUE) { ERR_print_errors_fp(stdout); exit(1); }

#ifdef _WIN64
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
#endif

	//�����׽���
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) { perror("socket create failed"); exit(1); }
	else cout << " socket create success" << endl;

	server_port = atoi(argv[1]);
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(server_port);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	//���׽���
	if (bind(sockfd, (struct sockaddr*) & server_addr, sizeof(struct sockaddr)) == -1) { perror("bind  failed"); exit(1); }
	else cout << " bind success" << endl;

	//���м���
	if (listen(sockfd, 2) == -1) { perror(" begin listen failed"); exit(1); }
	else cout << " begin listen success " << endl;

	//ѭ��������յ������ݰ�
	while (1) {
		SSL* ssl;
		len = sizeof(struct sockaddr);
		//����һ������
		if ((client_fd = accept(sockfd, (struct sockaddr*) & client_addr, &len)) == -1) { perror("accept failed"); exit(errno); }
		else {
			cout << " SERVER GET CONNECTION FROM: " << inet_ntoa(client_addr.sin_addr)
				 << " PORT: " << ntohs(client_addr.sin_port)
				 << " SOCKET: " << client_fd
				 << endl;
		}
		//����SSL�׽���
		ssl = SSL_new(ctx);
		//����SSL�׽���
		SSL_set_fd(ssl, client_fd);
		//����SSL����
		if (SSL_accept(ssl) == -1) { perror(" ssl accept error "); closesocket(client_fd); break; }
		bzero(buffer, MAXBUF + 1);
		strcpy(buffer," SERVER LISTENING... ");
		//�����׽��ֶ�д
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
		//�ͷ�SSL��Դ
		SSL_shutdown(ssl);
		//�ر�SSL�׽���
		SSL_free(ssl);
		//�ر��׽���
		closesocket(client_fd);
	}
	//�ͷ�SSL�׽���
	SSL_CTX_free(ctx);
	//�ر��׽���
	closesocket(sockfd);

	return 0;

}