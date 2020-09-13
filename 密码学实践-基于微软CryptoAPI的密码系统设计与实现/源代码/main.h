#include "windows.h"
#include "wincrypt.h"
#include "iostream"
#include "fstream"
#define MY_ENCODING_TYPE (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
#define KEYLENGTH 0x00800000
#define ENCRYPT_ALGORITHM CALG_RC4
#define ENCRYPT_BLOCK_SIZE 8
#define MAX_FILE_SIZE 4000000
#define SIGNATURE_SIZE 500
#define BLOCK_SIZE 50

BYTE* pbKeyBlob;
DWORD dwBlobLen;
