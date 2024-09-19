
#include <iostream>
#include <filesystem>
#include <conio.h>
using namespace std;

int main()
{
    int ans;
    cout<<"press 1 to encrypt , 2 to decrypt\n";
    cin>>ans;

    cout<<"Enter file name: \n";
    string fname;
    getline(cin,fname);

    cout<<"Enter key: \n";
    int key;
    cin>>key;

    if( ans == 1 ){

        char c;
        ifstream in;
        ofstream ou;
        in.open(fname.c_str(),ios::binary);
        in = "output";

        ou.open(fname.c_str(),ios::binary);

        while(!in.eof()){
            in>>noskipws>>c;
            int temp = (c + key);
            ou<<(char)temp;

        }
        in.close();
        ou.close();
    }
    else if( ans == 2 ){
        char c;
        ifstream in;
        ofstream ou;
        in.open(fname.c_str(),ios::binary);
        in = "output";

        ou.open(fname.c_str(),ios::binary);

        while(!in.eof()){
            in>>noskipws>>c;
            int temp = (c - key);
            ou<<(char)temp;

        }
        in.close();
        ou.close();

    }


    return 0;
}
