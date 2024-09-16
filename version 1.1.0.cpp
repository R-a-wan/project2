//Writing c++ program with capicom to encrypt and decrypt files
//The platform SDK redistributable ships a COM component called CAPICOM

//CAPI = Crypto API _when downloaded_ When we download this component, Capicom.dll, we must install it on our machine
// Capicom.dll ==> installs by default program files directory
//We must traverse the capicom folder on the command line until we find the capicom.dll in the directory listing
/*
Choose:
    ->visual Studio
    ->Win32 console application
    ->empty project
*/

#include <windows.h>
#include <fstream>
#include <string>
#include <iostream>
#import "capicom.dll"
using namespace std;
using namespace CAPICOM;

const char szErrParms[] = "Enter Capi [E|D] [file name] [secret key]";
const char szErrNoFile[] = "File not found";
const char szErrWrite[] = "Error writing to output file";

void Encrypt(char *pszFile, char *pszKey);
void Decrypt(char *pszFile, char *pszKey);
int main(int argc, char **argv)
{
    char c;
    CoInitialize(0);  //has to be called in every single thread that uses COM, regardless of what thread it is,
                      //or whether it has a parent thread or child threads
    if ( argc != 4 )
        cout << szErrParms << endl;
    else
    {
        c = argv[1][0]; // first character in this array of char szErrParms[] which will be E or D
        if ( (c == 'E') || (c == 'e') )
            Encrypt(argv[2], argv[3]);
        else if ( (c == 'D') || (c == 'd') )
            Decrypt(argv[2], argv[3]);
        else
            cout << szErrParms << std::endl; 
    }
    CoUninitialize();
    return 0;
}
void Encrypt(char *pszFile, char *pszSecret)
{
    int               size;
    char              *buf;
    _bstr_t           cipherText;
    string            name;
    ifstream          in(pszFile, ios::in | ios::binary | ios::ate);
    ofstream          out;
    IAlgorithmPtr     algo;
    IEncryptedDataPtr encryptor;

    if ( !in.is_open() )
        cout << szErrNoFile << std::endl;
    else
    {
        size = in.tellg();
        buf = new char[size + 1];
        buf[size] = 0;

        in.seekg(0, ios::beg);
        in.read(buf, size);
        in.close();
  
        encryptor.CreateInstance("CAPICOM.EncryptedData");
        encryptor->PutContent(_bstr_t(buf) );

        algo = encryptor->GetAlgorithm();
        algo->PutName(CAPICOM_ENCRYPTION_ALGORITHM_AES);
        algo->PutKeyLength(CAPICOM_ENCRYPTION_KEY_LENGTH_MAXIMUM);

        encryptor->SetSecret(_bstr_t(pszSecret), CAPICOM_SECRET_PASSWORD);

        cipherText = encryptor->Encrypt(CAPICOM_ENCODE_BASE64);

        name = pszFile;
        name.append(".encrypted");
        out.open(name.c_str(), ios::out | ios::binary);

        if ( !out.is_open() )
            cout << szErrWrite << endl;
        else
        {
            out << cipherText;
            out.close();
        }
    }
}

void Decrypt(char *pszFile, char *pszSecret)
{
    int               size;
    char              *buf;
    _bstr_t           plainText;
    string            name;
    ifstream          in(pszFile, ios::in | ios::binary | ios::ate);
    ofstream          out;
    IEncryptedDataPtr encryptor;

    if ( !in.is_open() )
        cout << szErrNoFile << std::endl;

    else
    {
        size = in.tellg();

        buf = new char[size + 1];
        buf[size] = 0;

        in.seekg(0, ios::beg);
        in.read(buf, size);
        in.close();

        encryptor.CreateInstance("CAPICOM.EncryptedData");

        encryptor->SetSecret(_bstr_t(pszSecret), CAPICOM_SECRET_PASSWORD);

        encryptor->Decrypt(_bstr_t(buf));
        plainText = encryptor->GetContent();

        name = pszFile;
        name.append(".decrypted");
        out.open(name.c_str(), ios::out | ios::binary);

        if ( !out.is_open() )
            cout << szErrWrite << endl;
        else
        {
            out << plainText;
            out.close();
        }
    }
}
