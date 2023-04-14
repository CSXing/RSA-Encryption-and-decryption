
#include <windows.h>
#include <stdio.h>
#include <iostream> 
#include <string>
#include <string.h>

#include "cRsa.h"

using std::cout;
using std::endl;
using std::cin;
using std::hex;


int main()
{
    DWORD start = 0;

    FILE *h原内容 = fopen("_源文本.txt", "rb");
    //FILE *h原内容 = fopen("_源文件.exe", "rb");
    if (h原内容) {
        fseek(h原内容, 0, SEEK_END);
        unsigned int _原内容大小 = ftell(h原内容); //文件大小
        char *_原内容 = (char*)malloc(sizeof(char)*_原内容大小+1);
        rewind(h原内容);
        _原内容大小 = fread(_原内容, sizeof(char), _原内容大小, h原内容);
        fclose(h原内容);

        cout << "原内容大小..."<< _原内容大小 << endl;
    
        类定义_加密 _服务端_加密;
        _服务端_加密.生成密钥(16);
    
        cout <<"__加密.密钥长度: "<< _服务端_加密.密钥长度() << endl;

        char *_加密后的数据 = (char*)malloc(sizeof(char)*_原内容大小*3);
        memset(_加密后的数据, 0, _原内容大小*3);
        start = GetTickCount();
        unsigned long _加密后的大小 = _服务端_加密.加密(_原内容, _原内容大小, _加密后的数据);
        std::cout << "加密耗时：[" << GetTickCount()-start << "ms, 大小:" << _加密后的大小 << "]" << std::endl;
    
        char *_解密后的数据 = (char*)malloc(sizeof(char)*_原内容大小*3);
        memset(_解密后的数据, 0, _原内容大小*3);
        start = GetTickCount();
        unsigned long _解密后的大小 = _服务端_加密.解密(_加密后的数据, _加密后的大小, _解密后的数据);
        std::cout << "解密耗时：[" << GetTickCount()-start << "ms, 大小:" << _解密后的大小 << "]" << std::endl;
        cout <<  _解密后的数据 << endl;
            
        free(_原内容);
        free(_加密后的数据);
        free(_解密后的数据);
    }

    system("pause");
}