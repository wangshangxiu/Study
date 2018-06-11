#include <string>
#include <iostream>
#include <openssl/md5.h>
#include<string.h>
using namespace std;


/**
 * 
 */

string MD5(const string& src )
{
    MD5_CTX ctx;

    string md5_string;
    unsigned char md[16] = { 0 };
    char tmp[33] = { 0 };

    MD5_Init( &ctx );
    MD5_Update( &ctx, src.c_str(), src.size() );
    MD5_Final( md, &ctx );

    for( int i = 0; i < 16; ++i )
    {   
        memset( tmp, 0x00, sizeof( tmp ) );
        sprintf( tmp, "%02X", md[i] );
        md5_string += tmp;
    }   
    return md5_string;
}

string md5(const string& src) {
    string md5_string;
    unsigned char md[16] = {0};
    char tmp[33] = {0};	
    MD5((const unsigned char*)src.c_str(), src.size(), md);
    for(int i = 0; i < 16; ++i) {
        memset( tmp, 0x00, sizeof( tmp ) );
        sprintf( tmp, "%02X", md[i] );
        md5_string += tmp;
    }   
    return md5_string;
} 

int main()
{
    cout << MD5("fupeng") << endl;
    cout << MD5("123") << endl;
    cout << md5("fupeng") << endl;
    cout << md5("123") << endl;
     
    return 0;
}
