#include <iostream>

using namespace std;

#define P_LENGTH 22
#define KEY_LENGTH 12
typedef unsigned char uc;


struct HexCharStruct
{
  unsigned char c;
  HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
  return (o << std::hex << (int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
  return HexCharStruct(_c);
}

// Permutate by Key scheduling algorithm
void IV(uc* S, uc* Key, int *keyLength){

    int i,j,tmp;

    for(i=0;i<256;i++){
        S[i]=i;
    }

    for(i=0;i<256;i++){
        j = (j + S[i] + Key[i % *keyLength])%256;
        
        tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;

    }
    
    
}

//Permutate by Psuedo random generation algorithm
void rc4(uc* key,uc* plainText,uc*cipherText, int* plainTextLength,uc* streamArray){

    int i=0,j=0,t,KeyStream,tmp;

    for(int k=0 ;k < *plainTextLength;k++){
        i = (i+1)%256;
        j = (j + key[i]) % 256;

         tmp = key[i];
        key[i] = key[j];
        key[j] = tmp;

        t = (key[i] + key[j]) % 256;
        KeyStream = key[t];
        streamArray[k]=KeyStream;

        cipherText[k] = plainText[k] ^ KeyStream;

    }
}

void rc4Decrypt(uc* keyStream,uc* plainText,uc*cipherText, int* plainTextLength){

    int i=0,KeyStream;

    for(int i= 0 ;i<*plainTextLength;i++){
        
        KeyStream = keyStream[i];

        plainText[i] = cipherText[i] ^ KeyStream;

    }
}



int main(){

    unsigned char plaintText[P_LENGTH]="This is a sample text";
    unsigned char key[KEY_LENGTH]="this is key";
    unsigned char S[256];
    unsigned char cipherText[P_LENGTH];
    unsigned char streamArray[P_LENGTH];
    unsigned char decryptText[P_LENGTH];

    int p = KEY_LENGTH;
    int* x = &p;
    IV(S,key,x);

    p=P_LENGTH;
    rc4(S,plaintText,cipherText,x,streamArray);
rc4Decrypt(streamArray,decryptText,cipherText,x);
    
    cout<<endl;
    
    for(uc c:cipherText){
        cout<<hex(c)<<" ";
    }

    
    cout<<endl;
    for(uc c:decryptText){
        cout<<c;
    }

    return 0;
}