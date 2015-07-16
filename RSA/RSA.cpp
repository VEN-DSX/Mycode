#include "RSA.h"

using namespace std;

int main()
{
    // Initialize();


    RSA_Initialize();

    string Plain;
    cout<<"encrypt every 8bit\nInput your Plaintext:"<<endl;
    while(cin>>Plain){
        string Cipher;
        Cipher = RSA_Encrypt(Plain);
        RSA_Decrypt(Cipher);
        cout<<"encrypt every 8bit\nInput your Plaintext:"<<endl;
    }
    
    system("pause");
    return 0;
}