#include <bits/stdc++.h>
#include<fstream>
using namespace std;

class encdec{

    int key;
    string file;
    char c;

public:
    void encrypt();
    void decrypt();

};

void encdec ::encrypt(string file){

     cout<<"Key : ";
     cin>>key;

     fstream fin,fout;

     fin.open(file, fstream::in);
     fout.open("encrypt.txt", fstream::out);

     while (fin >> noskipws >> c) {
        int temp = (c + key);

        // Write temp as char in
        // output file
        fout << (char)temp;
    }

    // Closing both files
    fin.close();
    fout.close();
}

void encdec::decrypt(string file)
{
    cout << "key: ";
    cin >> key;
    fstream fin;
    fstream fout;
    fin.open(file, fstream::in);
    fout.open("decrypt.txt", fstream::out);

    while (fin >> noskipws >> c) {

        // Remove the key from the
        // character
        int temp = (c - key);
        fout << (char)temp;
    }

    fin.close();
    fout.close();
}

int main()
{
    string filePath;
    getline(cin,filePath);

    cout<<"Type E if you want to encrypt the file, \n But to decrypt type D: \n";
    char ch;
    cin>>ch;

    switch(ch){
    case 'E':
    case 'e':
        encdec ::encrypt(filePath);
        if(encdec ::encrypt(filePath)){
            cout<<"file encrypted successfully";
        }
        break;
    case 'D':
    case 'd':
        encdec ::decrypt(filePath);
        if(encdec ::decrypt(filePath)){
            cout<<"file decrypted successfully";
        }
        break;

    }


    return 0;
}
