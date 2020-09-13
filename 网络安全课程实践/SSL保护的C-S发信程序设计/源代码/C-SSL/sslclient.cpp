#include "main.h"
void ShowCerts(SSL* ssl);
using namespace std;
int main(int argc, char **argv){
	if (argc != 4) {cout << "Usage: sslclient ip port filename" << endl;exit(0);}
	
	int sockfd;
	int len;
	struct sockaddr_in dest;
	char buffer[MAXBUF + 1];
	SSL_CTX *ctx;
	SSL *ssl;

#ifdef _WIN64
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
#endif
	HANDLE File = NULL; 
	DWORD FILESIZE = NULL;	
	DWORD File_Len = NULL;
	PBYTE temp = NULL;	

	//��ȡ��Ҫ���͵��ļ�
	if ((File = CreateFileA(argv[3], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
		perror("OPEN File error"); exit(errno);
	}
	FILESIZE = GetFileSize(File, NULL);
	temp = (PBYTE)malloc(FILESIZE);
	if (!ReadFile(File, temp, FILESIZE, &File_Len, NULL)) {
		perror("READ File error"); exit(errno);
	}
		
	//�����׽���
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { perror("Socket create failed"); exit(errno); }
	else cout << "socket creat success" << endl;

	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(atoi(argv[2]));
	//��ַת��
	if (inet_aton(argv[1], (struct in_addr *) &dest.sin_addr.s_addr) == 0) {perror(argv[1]);exit(errno);}
	else cout << "address creat success" << endl;
	//���ӷ�����
	if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {perror("Connect ");exit(errno);}
	else cout << "server connect success" << endl;

	////ΪSSL���ؼ��ܺ͹�ϣ�㷨
	SSL_library_init();
	OpenSSL_add_all_algorithms();
	//���ش�����������ַ���
	SSL_load_error_strings();
	//����SSL�����Ľӿ�
	if((ctx = SSL_CTX_new(SSLv23_client_method())) == NULL){ERR_print_errors_fp(stdout);exit(1);}
	//����SSL�׽���
	ssl = SSL_new(ctx);
	//����SSL�׽���
	SSL_set_fd(ssl, sockfd);
	//����SSL����
	if (SSL_connect(ssl) == -1) { ERR_print_errors_fp(stderr); }
	else {
		cout << "Connected with "<< SSL_get_cipher(ssl) << " encryption " <<endl;
		ShowCerts(ssl);
	}

	bzero(buffer, MAXBUF + 1);

	if((len = SSL_read(ssl, buffer, MAXBUF)) > 0)
		cout << "Message received successfully: " << buffer << " The length of data: " << len << endl;
	else {
		cout << "Message received failed! The error code is " << errno << " and the error message is " << strerror(errno) << endl;
		exit(errno);
	}

	if((len = SSL_write(ssl, temp, File_Len)) > 0 )
		cout << "Message received successfully: " << temp << " The length of data: " << File_Len << endl;
	else
		cout << "Message received failed! The error code is" << errno << " and the error message is " << strerror(errno) << endl;

	closesocket(sockfd);
	SSL_shutdown(ssl);
	SSL_free(ssl);
	SSL_CTX_free(ctx);
	return 0;

}

void ShowCerts(SSL* ssl){
	X509* cert;
	char line[MAXBUF + 1];
	cert = SSL_get_peer_certificate(ssl);
	if (cert != NULL) {
		cout << "Digital certificate information:" << endl;
		X509_NAME_oneline(X509_get_subject_name(cert), line, MAXBUF);
		cout << "certificate: " << line << endl;
		X509_NAME_oneline(X509_get_issuer_name(cert), line, MAXBUF);
		cout << "lusser: " << line << endl;
		X509_free(cert);
	}
	else
		cout << "No certificate information��" << endl;
}