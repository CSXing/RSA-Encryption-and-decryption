#pragma once

#include <windows.h>
#include <queue>
#include <fstream>
#include <time.h>
#include <sys/timeb.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

// RSA加密算法 ========================================
void RSA_on (const char *str, char* out, bool isHex=false);
inline void RSA_on (const char *str, const int size, char* out, bool outHex);
void RSA_off(const char *str, char* out, bool isHex=false);
inline void RSA_off(const char *str, const int size, char* out, bool outHex);

/* ===============================================
    文字加密模块
=============================================== */
template <int xorKeys, int srcLen, long xRefKiller>
class XorStr
{
private: 
    XorStr();
public: 
	char s[srcLen];
    XorStr(const char* xSource);
#ifndef DEBUG_OPTION
    ~XorStr(){ for(int i=0;i<srcLen;i++) s[i]=0;} // clear string from stack
#endif
};
template <int xorKeys, int srcLen, long xRefKiller>
XorStr<xorKeys, srcLen, xRefKiller>::XorStr(const char* xSource)
{
	int xvalue = xorKeys;
	int i = 0;
	for(;i<(srcLen-1);i++) {
		s[i] = xSource[i-xRefKiller] ^ xvalue;
		xvalue += 1;
		xvalue %= 256;
	}
	s[srcLen-1] = 0;
}

/* ===============================================
                    防破解类
=============================================== */
class CAntiBypass;
class CAntiBypass
{
public:
	//初始化
    CAntiBypass(){
        memset(&this->strByPass[0], 0, 255*256*sizeof(char));
        memset(&this->hexByPass[0], 0, 255*512*sizeof(char));
        memset(&this->intByPass[0], 0, 255*sizeof(int));
        
        sprintf(this->strByPass[0], "『宅』专用加密信息，创建日期：２０２１．０３．１５，企鹅号：９１０９５５９５１，邮箱：１３５８０４８３２３２＠１６３．ｃｏｍ ");
        RSA_on(this->strByPass[0], hexByPass[0], true);
        intByPass[0] = strlen(this->strByPass[0]);

        runQty = runTime = 0;
    }
    //释放
    ~CAntiBypass(){

    }
	//字符串校验
	void Anti(const short id, const char *next);
     int Check(const short id, const char *next);
	//数值校验
	void Anti(const short id, const long next);
     int Check(const short id, const long *next);
//private:
    //加密处理
    void sample(const char * src, const int size, const short begin, char *dst, const bool encrypt=true);
    void sample(const long src, const short begin, long *dst);
    char strByPass[255][256]; //存放字符串 待验证
    char hexByPass[255][512]; //存放字符串 待验证
    long intByPass[255]; //存放数值   待验证
    long lngByPass[255]; //存放数值   待验证

    //验证不通过后的变量
     int runQty;
    long runTime; //时间间隔
};
