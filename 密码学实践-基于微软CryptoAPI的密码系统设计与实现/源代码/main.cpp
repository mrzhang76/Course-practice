#include "main.h"
using namespace std;
void HandleError(const char *s);
void Encrpyted_file();
void Decrpyted_file();
void Generate_keys();
int main(void) {
	while (1) {
		int flag = -1;
		cout << "------------------------------------------------------" << endl;
		cout << "--------------Please choose function------------------" << endl;
		cout << "------------------------------------------------------" << endl;
		cout << "1.Create Key" << endl;
		cout << "2.Encrypted file" << endl;
		cout << "3.Decrupted file" << endl;
		cout << "0.Exit" << endl;
		cout << "------------------------------------------------------" << endl;
		cout << "------------------------------------------------------" << endl;
		cout << "------------------------------------------------------" << endl;
		cin >> flag;
		switch (flag) {
			case 1:
				Generate_keys();
				break;
			case 2:
				Encrpyted_file();
				break;
			case 3:
				Decrpyted_file();
				break;
			case 0:
				exit(0);
		}

	}
}
void HandleError(const char *s) {
	cout <<"Error occurred"<< endl;
	cout <<  s << endl;
	printf("Error Code :%x", GetLastError());
	exit(1);
}

void Encrpyted_file() {
	HCRYPTPROV hProv = NULL;		//CSP句柄指针
	HCRYPTHASH hHash = NULL;		//Hash对象
	HCRYPTKEY hKey = NULL;		//会话密钥句柄
	PBYTE hKey_out = NULL;		//会话密钥
	HANDLE hKeyFile = NULL;		//会话密钥文件
	DWORD hKeyLen = NULL;		//会话密钥长度
	PBYTE pbBuffer = NULL;		//数据缓存
	DWORD r_file_len = NULL;		//文件长度
	HCRYPTKEY hXchgKey = NULL;	//公钥句柄
	HANDLE PublicKeyFile = NULL; //公钥文件
	PBYTE hPublicKey = NULL;		//公钥指针
	DWORD hPublicKeyLen = NULL; //公钥长度
	HANDLE m_File = NULL;		//加密文件
	DWORD FILESIZE = NULL;	//文件长度
	DWORD lpNumberOfBytesWritten = 0;

	cout << "------------------------------------------------------" << endl;
	cout << "--------------------Encrpyted_file--------------------" << endl;
	cout << "------------------------------------------------------" << endl;

	//连接CSP,获得指定CSP密钥容器的句柄
	if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0)) 
		cout << "CryptAcquireContext success..." << endl;
	else
		HandleError("CryptAcquireContext error");


	//读取公钥文件
	if ((PublicKeyFile = CreateFile(L"key\\PublicKey", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
		HandleError("OPEN PublicKey error");
	}
	FILESIZE = GetFileSize(PublicKeyFile, NULL);
	hPublicKey = (PBYTE)malloc(FILESIZE);
	if(!ReadFile(PublicKeyFile, hPublicKey,FILESIZE,&hPublicKeyLen,NULL))
		HandleError("READ PublicKey error");
	//公钥装载
	if(CryptImportKey(hProv,hPublicKey,hPublicKeyLen,0,NULL, &hXchgKey))
		cout << "PublicKey loaded success..." << endl;

	char file_name[50];
	char out_file_name[50];
	cout << "Please enter file name you want to encrypt:" << endl;
	cin >> file_name;
	cout << "Please enter the name of the output file:" << endl;
	cin >> out_file_name;
	cout << "------------------------------------------------------" << endl;
	cout << "----------------Your information is-------------------" << endl;
	cout << "Crypted file name: " << file_name << endl;
	cout << "Out file name:     " << out_file_name << endl;
	cout << "------------------------------------------------------" << endl;

	//打开待加密文件
	ifstream r_file;
	r_file.open(file_name, ios::in);
	if(!r_file.is_open())
		HandleError("Cannot find your file");
	streampos pos = r_file.tellg();
	r_file.seekg(0, ios::end);
	r_file_len = r_file.tellg();
	r_file.seekg(pos);
	cout << "File len is " << r_file_len << endl;

	//创建会话密钥
	if (CryptGenKey(hProv, ENCRYPT_ALGORITHM, KEYLENGTH | CRYPT_EXPORTABLE, &hKey)) {
		cout << "CryptGenKey success......" << endl;
		cout << "Your session key: " << hKey << endl;
	}

	CHAR* temp = NULL;
	pbBuffer = (PBYTE)malloc(r_file_len);
	temp = (PCHAR)malloc(r_file_len);
	r_file.read(temp, r_file_len);
	memcpy(pbBuffer,temp,r_file_len);
	r_file.close();

	//加密数据文件	
	if (CryptEncrypt(hKey,NULL,TRUE,	0,pbBuffer,&r_file_len,r_file_len))
		cout << "Encrypt success" << endl;
	else 
		HandleError("Encrypt faild");
	
	//存储加密数据	
	if ((m_File = CreateFileA(out_file_name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
		HandleError("Create m_File error");
	if (!(WriteFile(m_File, (LPCVOID)pbBuffer, r_file_len, &lpNumberOfBytesWritten, NULL)))
		HandleError("Write m_File error");
	FlushFileBuffers(m_File);
	CloseHandle(m_File);
	cout << "Your encrpyted file is: " <<out_file_name<< endl;
	
	//导出会话密钥
	if (CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, NULL, &hKeyLen))
		cout << "Get hKeyLen success...hKeyLen: " << hKeyLen << endl;
	else
		HandleError("Get hKeyLen error");
	//获取内存空间
	if (!(hKey_out = (PBYTE)malloc(hKeyLen)))
		HandleError("malloc error");
	//导出会话密钥到内存空间
	if (CryptExportKey(hKey, hXchgKey, SIMPLEBLOB, 0, hKey_out, &hKeyLen)) 
		cout << "CryptExporthKey success..." << endl;
	else
		HandleError("CryptExporthKey error");
	//导出会话密钥到文件	
	CHAR key_name[50] = { "key\\key-" };
	strcat_s(key_name, out_file_name);
	if ((hKeyFile = CreateFileA(key_name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
		HandleError("CreatehKeyFile error");
	if (!(WriteFile(hKeyFile, (LPCVOID)hKey_out, hKeyLen, &lpNumberOfBytesWritten, NULL)))
		HandleError("WritehKeyFile error");
	FlushFileBuffers(hKeyFile);
	CloseHandle(hKeyFile);
	cout << "Your hKey is created in " << key_name <<endl;

	CryptReleaseContext(hProv, 0);
	cout << "------------------------------------------------------\n" << endl;
}	

void Decrpyted_file() {
	HCRYPTPROV hProv = NULL;	//CSP句柄指针
	HCRYPTKEY hXchgKey = NULL; //私钥句柄
	HANDLE PrivateKeyFile = NULL;//私钥文件
	PBYTE hPrivateKey = NULL;//私钥
	DWORD hPrivateKeyLen = NULL; //私钥长度
	HANDLE hKeyFile = NULL; //会话密钥文件
	HCRYPTKEY hKey = NULL;		//会话密钥句柄
	PBYTE hKey_in = NULL;	//会话密钥
	DWORD hKeyLen = NULL;	//会话密钥长度
	HANDLE mFile = NULL;		//待解密文件
	PBYTE mfile_in = NULL;  //待解密文件指针
	DWORD mfileLen = NULL;	//待解密文件长度
	DWORD FILESIZE = NULL;	//文件长度
	DWORD lpNumberOfBytesWritten = 0;
	HANDLE OutFile = NULL; //导出文件

	
	
	cout << "------------------------------------------------------" << endl;
	cout << "--------------------Decrpyted_file--------------------" << endl;
	cout << "------------------------------------------------------" << endl;

	//连接CSP,获得指定CSP密钥容器的句柄
	if (CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 0))
		cout << "CryptAcquireContext success..." << endl;
	else
		HandleError("CryptAcquireContext error");

	//读取私钥文件
	if ((PrivateKeyFile = CreateFile(L"key\\PrivateKey", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
		HandleError("OPEN PrivateKey error");
	}
	FILESIZE = GetFileSize(PrivateKeyFile, NULL);
	hPrivateKey = (PBYTE)malloc(FILESIZE);
	if (!ReadFile(PrivateKeyFile, hPrivateKey, FILESIZE, &hPrivateKeyLen, NULL))
		HandleError("READ PrivateKey error");
	//私钥装载
	if (CryptImportKey(hProv, hPrivateKey, hPrivateKeyLen, 0, 0, &hXchgKey)) {
		cout << "PrivateKey loaded success..." << endl;
		cout << "Your PrivateKey: " << hXchgKey << endl;
	}

	char file_name[50];
	char key_name[50];
	char out_file_name[50];
	cout << "Please enter file name you want to decrypt:" << endl;
	cin >> file_name;
	cout << "Please enter the name of the key file:" << endl;
	cin >> key_name;
	cout << "Please enter the name of the out file:" << endl;
	cin >> out_file_name;
	cout << "------------------------------------------------------" << endl;
	cout << "Your information is:" << endl;
	cout << "Crypted file name:" << file_name << endl;
	cout << "Key file name:" << key_name << endl;
	cout << "out file name:" << out_file_name << endl;

	CHAR key_file_name[50] = { "key\\" };
	strcat_s(key_file_name, key_name);
	cout << "Open key file :" << key_file_name << endl;

	//读取会话密钥文件
	if ((hKeyFile = CreateFileA(key_file_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
		HandleError("OPEN hKeyfile error");
	}
	FILESIZE = GetFileSize(hKeyFile, NULL);
	hKey_in = (PBYTE)malloc(FILESIZE);
	if (!ReadFile(hKeyFile, hKey_in, FILESIZE, &hKeyLen, NULL))
		HandleError("READ PrivateKey error");

	//会话密钥装载
	if (CryptImportKey(hProv, hKey_in, hKeyLen, hXchgKey, NULL, &hKey)) {
		cout << "hKey loaded success..." << endl;
		cout << "Your session key :" << hKey << endl;
	}
	//读取以加密文件
	if ((mFile = CreateFileA(file_name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) {
		HandleError("OPEN mfile error");
	}
	FILESIZE = GetFileSize(mFile, NULL);
	mfile_in = (PBYTE)malloc(FILESIZE);
	if (!ReadFile(mFile, mfile_in, FILESIZE, &mfileLen, NULL))
		HandleError("READ mfile error");
	cout << "File len is: " << mfileLen << endl;
	
	

	//解密文件
	if (CryptDecrypt(hKey,NULL,TRUE,	0,mfile_in,&mfileLen)) {
		cout << "Decrypt success" << endl;
	}

	//存储已解密文件
	if ((OutFile = CreateFileA(out_file_name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
		HandleError("CreatehKeyFile error");
	if (!(WriteFile(OutFile, (LPCVOID)mfile_in, mfileLen, &lpNumberOfBytesWritten, NULL)))
		HandleError("WritehKeyFile error");
	FlushFileBuffers(OutFile);
	CloseHandle(OutFile);
	cout << "Out file is created in " << out_file_name << endl;
	cout << "------------------------------------------------------\n" << endl;
	CryptReleaseContext(hProv, 0);
}

void Generate_keys() { 
	HCRYPTPROV hProv = NULL;	//CSP句柄指针
	HCRYPTKEY hKey = NULL;	//会话密钥
	DWORD PublicKeyLen = 0; //公钥长度
	DWORD PrivateKeyLen = 0;//私钥长度
	PBYTE PublicKey = NULL; //公钥
	PBYTE PrivateKey = NULL;//私钥
	HANDLE hPublicKeyFile = NULL; //公钥文件
	HANDLE hPrivateKeyFile = NULL;//私钥文件
	DWORD lpNumberOfBytesWritten = 0;
	CHAR strPublicKeyFile;
	CHAR* strPrivateKeyFile;
	//连接CSP,获得指定CSP密钥容器的句柄
	cout << "------------------------------------------------------" << endl;
	cout << "-------------------Create Your Key--------------------" << endl;
	cout << "------------------------------------------------------" << endl;
	if (CryptAcquireContext(&hProv, NULL,NULL, PROV_RSA_FULL, 0)) 
		cout << "CryptAcquireContext success..." << endl;
	else
		HandleError("CryptAcquireContext error");

	//创建随机的公钥私钥对
	if(CryptGenKey(hProv, AT_KEYEXCHANGE, CRYPT_ARCHIVABLE, &hKey))
		cout << "CryptGenKey success..." << endl;
	else
		HandleError("CryptGenKey error");

	//导出公钥
	//获取公钥长度
	if(CryptExportKey(hKey,NULL,PUBLICKEYBLOB,0,NULL,&PublicKeyLen))
		cout << "Get PublicKeyLen success...PublicKeyLen:" << PublicKeyLen <<endl;
	else
		HandleError("Get PublicKeyLen error");
	//获取内存空间
	if (!(PublicKey = (PBYTE)malloc(PublicKeyLen)))
		HandleError("malloc error");
	//导出公钥到内存空间
	if (CryptExportKey(hKey, NULL, PUBLICKEYBLOB, 0, PublicKey, &PublicKeyLen)) {
		cout << "CryptExportPublicKey success..." << endl;
	}
	else
		HandleError("CryptExportPublicKey error");
	//导出私钥
	//获取私钥长度
	if (CryptExportKey(hKey, NULL, PRIVATEKEYBLOB, 0, NULL, &PrivateKeyLen))
		cout << "Get PrivateKeyLen success...PrivateKeyLen:" << PrivateKeyLen <<endl;
	else
		HandleError("Get PrivateKeyLen error");
	//获取内存空间
	if (!(PrivateKey = (PBYTE)malloc(PrivateKeyLen)))
		HandleError("malloc error");
	//导出私钥到内存空间
	if (CryptExportKey(hKey, NULL, PRIVATEKEYBLOB, 0, PrivateKey, &PrivateKeyLen)) {
		cout << "CryptExportPrivateKey success..." << endl;
	}
	else
		HandleError("CryptExportPrivateKey error");
	
	//存放公钥至文件
	if((hPublicKeyFile=CreateFile(L"key\\PublicKey", GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE)
		HandleError("CreatePublicKeyFile error");
	if(!(WriteFile(hPublicKeyFile,(LPCVOID)PublicKey, PublicKeyLen,&lpNumberOfBytesWritten,NULL)))
		HandleError("WritePublicKeyFile error");
	FlushFileBuffers(hPublicKeyFile);
	CloseHandle(hPublicKeyFile);
	cout << "Your PublicKey is created"<< endl;

	//存放私钥至文件
	if((hPrivateKeyFile = CreateFile(L"key\\PrivateKey", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
		HandleError("CreatePrivateKeyFile error");
	if(!WriteFile(hPrivateKeyFile, (LPCVOID)PrivateKey, PrivateKeyLen, &lpNumberOfBytesWritten, NULL))
		HandleError("WritePrivateKeyFile error");
	FlushFileBuffers(hPrivateKeyFile);
	CloseHandle(hPrivateKeyFile);
	
	cout << "Your PrivateKey is created" << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "You can find your key in \"./key\"" << endl;
	cout << "------------------------------------------------------\n" << endl;
	free(PublicKey);
	free(PrivateKey);
	CryptDestroyKey(hKey);
	CryptReleaseContext(hProv, 0);


}