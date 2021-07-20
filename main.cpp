
#include "main.h"

using namespace std;

/* ================================
    函数: Rand
    参数: seeds=种子数,最大值
    描述: 产生随机
================================ */
int Rand(const int seeds)
{
    if (seeds==0) return seeds;
    struct timeb timeSeed;
    ftime(&timeSeed);
    srand(timeSeed.time * 1000 + timeSeed.millitm); // milli time
    return rand()%seeds;
}
/* ================================
    函数: ToHexUpper
    参数: value=数值
    描述: 转成十六进制
================================ */
inline char ToHex(unsigned char value) 
{
	return "0123456789ABCDEF"[value & 0xF];
}

/* ================================
    函数: FrHex
    参数: value=数值
    描述: 将数16进（大写或小写）制转为数字
================================ */
inline int FrHex(unsigned char c) 
{
	return ((c >= '0') && (c <= '9')) ? int(c - '0') :
		((c >= 'A') && (c <= 'F')) ? int(c - 'A' + 10) :
		((c >= 'a') && (c <= 'f')) ? int(c - 'a' + 10) :
		/* otherwise */              -1;
}

inline short calcMod(short x,short y,int z)//积模分解
{
	if(y==1)
		return x%z;
	else
	    return (calcMod(x,y/2,z)*calcMod(x,y-y/2,z))%z;
}
//最小公倍数
inline int lcm(int one, int two)
{
    int i, iRet=0;
    for (i = one; i <= one * two; i++)
    {
        if (i%one == 0 && i%two == 0)
        {
            //printf("%d\n", i);
            iRet = i;
            break;
        }
    }
    return iRet;
    return one*two;
}
//互质
inline int gcd(int one, int two)
{
    if(one==1 || two==1) // 两个正整数中，只有其中一个数值为1，两个正整数为互质数
		return true;

	while(1)// 求出两个正整数的最大公约数
    {
		int t = one%two;
		if(t == 0) 
        {
            break;
        }
		else
        {
			one = two;
			two = t;
		}
	}
	if(two>1)
        return false; // 如果最大公约数大于1，表示两个正整数不互质
	else
        return true;  // 如果最大公约数等于1,表示两个正整数互质
}

void RSA_on(const char *str, char* out, bool outHex){
    RSA_on(str, strlen(str), out, outHex);
}
inline void RSA_on(const char *str, const int size, char* out, bool outHex)//RSA加密算法
{
    //int p=197, q=101, e=4779, d=4819; //P Q为相异质数，M与16*18=288互质
    int p=101, q=199, e=7499, d=9599;
    int i, k, ilen=size;
    short one=0;
	for(i=0;i<ilen;i++)
	{
        if (outHex){
	        one=calcMod(*(str+i),d,p*q);
	        //printf("加密数值为:%d = 0x%04X\n", one, one);
            for(k=0; k<4; k++){
                *(out+i*4+k) = ToHex(one & 0xF);
                one = one>>4;
            }
        } else {
	        one=calcMod((BYTE)*(str+i),d,p*q);
            *(out+i)=one;
        }
	}
    if (outHex){
        *(out+ilen*4) = 0;
    } else {
        *(out+ilen) = 0;
    }
}

void RSA_off(const char *str, char* out, bool inHex){
    RSA_off(str, strlen(str), out, inHex);
}
inline void RSA_off(const char *str, const int size, char* out, bool inHex)//RSA解密算法
{
    //int p=197, q=101, e=4779, d=4819; //(R*M)%288==1
    int p=101, q=199, e=7499, d=9599;
    int i, k, ilen=size;
    short one=0;
	for(i=0;i<ilen;i++)
	{
        if (inHex){
            one=0;
            for(k=0; k<4; k++){
                one += FrHex(*(str+i))*(0x1<<(k*4));
                i++;
            }
            i--;
	        //printf("解密数值为:%d = 0x%04X\n", one, one);
            *(out+i/4) = calcMod(one,e,p*q);
        } else {
            one = *(str+i);
            *(out+i) = calcMod((BYTE)one,e,p*q);
        }
	   //*(str+i)=(char)MOD((BYTE)*(str+i),R,p*q);
	}
    if (inHex){
        *(out+ilen/4) = 0;
    } else {
        *(out+ilen) = 0;
    }
}
//判断是否是素数
bool isPrime(const unsigned short number){
    if (number <= 1 || (number % 6 != 1 && number % 6 != 5)) return false;
	if (number == 2 || number == 3) return true;

	unsigned short i, halfNum = (int)sqrt((double)number);
	for (i = 5; i <= halfNum; i += 6)
		if (number % i == 0 || number % (i + 2) == 0)
			return false;
	return true;
}

/* ===============================================
                     防破解类
=============================================== */
/* ================================
    函数: Anti
    参数: id=数组索引, next=下一组字符串
    描述: 字符串校验，明文增加字节。
================================ */
void CAntiBypass::Anti(const short id, const char *next) {
    if (id>0xFF || id<1) return;
    short byPass = 0x0F, ilen=strlen(strByPass[id]);
    //先验证原字符串
    if(strlen(hexByPass[id])>0){
        //解密
        char tmp[256]={0};
        this->sample(hexByPass[id], strlen(hexByPass[id]), id & 0xFF, tmp, false);
        byPass ^= (strcmp(strByPass[id], tmp));
    }
    //验证通过后
    if (byPass == 0x0F){
        //加密
        strcat(strByPass[id], next);
        this->sample(strByPass[id], strlen(strByPass[id]), id & 0xFF, hexByPass[id]);
    } else {
        //验证不通过，记录次数及随机时间
        if (byPass & 0x01)
            runQty += byPass & 0x01;
        else
            runQty++;

        runTime = runQty*0xFFFF;
    }
}

/* ================================
    函数: sample
    参数: id=数组索引, next=下一组字符串
    描述: 加密内容。
================================ */
void CAntiBypass::sample(const char * src, const int size, const short begin, char *dst, const bool encrypt)
{
    int i=0, iKey=begin, lenKey=strlen(this->strByPass[0]), lenSrc=0;
    if (begin>=lenKey) { iKey=lenKey/8+(begin % 7); }

    char *temp = (char*)malloc(sizeof(char)*size+1);
    memset(temp, 0, size+1);

    if (!encrypt){ //解密
        RSA_off(src, size, temp, true);
        lenSrc = size/4;
        //memcpy(&temp[0], &src[0], size);
        //lenSrc = size;
    } else { //加密
        memcpy(&temp[0], &src[0], size);
        lenSrc = size;
    }
	short ixOrKey = (lenSrc/2+begin) % 0x100;
    for(i=0; i<lenSrc; i++){
        temp[i] ^= this->strByPass[0][iKey++];
        temp[i] ^= ixOrKey;
        ixOrKey += 1;
		ixOrKey %= 0x100;

        if (iKey>=lenKey) {
            if (begin>=lenKey) {
                iKey=lenKey/8+(begin % 7);
            } else {
                iKey=begin;
            }
        }
    }
    if (!encrypt){ //解密
        memcpy(&dst[0], &temp[0], lenSrc+1);
    } else { //加密
        //memcpy(&dst[0], &temp[0], lenSrc+1);
        RSA_on(temp, lenSrc, dst, true);
    }
    free(temp);
};

/* ================================
    函数: Anti
    参数: id=数组索引, next=下一个累计数值
    描述: 字符串校验，明文增加字节。
================================ */
void CAntiBypass::Anti(const short id, const long next) {
    if (id>0xFF || id<1) return;
    short byPass = Rand(0xFF);
    //先验证原字符串
    if(intByPass[id]!=0){
        //解密
        long tmp=0;
        this->sample(this->lngByPass[id], id, &tmp);
        if (tmp == this->intByPass[id]){
            this->intByPass[id] += next;
            this->sample(this->intByPass[id], id, &this->lngByPass[id]);
        } else {
            //验证不通过，记录次数及随机时间
            if (byPass & 0x01)
                runQty += byPass & 0x01;
            else
                runQty++;

            runTime = runQty*0xFFFF;
        }
    } else {
        this->intByPass[id] += next;
        this->sample(this->intByPass[id], id, &this->lngByPass[id]);
    }
}
void CAntiBypass::sample(const long src, const short begin, long *dst)
{
    long long byPass = 0;
    int i=0, iKey=begin, lenKey=strlen(this->strByPass[0])-10;
    if (iKey>lenKey) { iKey=lenKey/10+(begin % 4); }

    byPass += this->strByPass[0][iKey+0] * 0x1000000UL;
    byPass += this->strByPass[0][iKey+1] * 0x10000UL;
    byPass += this->strByPass[0][iKey+2] * 0x100UL;
    byPass += this->strByPass[0][iKey+3] * 0x1UL;
    
    dst[0] = src ^ byPass;
}
//================================================================================

//================================================================================
int main(int argc, char**argv)
{

    //(1)选择两个不同的大素数p和q；
    //(2)计算乘积n=pq和Φ(n)=(p-1)(q-1)；
    //(3)选择大于1小于Φ(n)的随机整数e，使得gcd(e,Φ(n))=1；注：gcd即最大公约数。
    //(4)计算d使得de=1mod Φ(n)；注：即de mod Φ(n) =1。
    //(5)对每一个密钥k=(n,p,q,d,e)，定义加密变换为Ek(x)=xe mod n，解密变换为Dk(x)=yd mod n，这里x,y∈Zn；
    //(6)p,q销毁，以{e,n}为公开密钥，{d,n}为私有密钥。

    int p=19,q=37; //素数
    int e, d;
    p=13; q=19;

    p=101; q=199;

    int n=p*q;
    int Φn=lcm((p-1),(q-1)); //最小公倍数

    for(e=2; e<n*10; e++){
        if (gcd(e,Φn) && e<Φn){
            for(d=e+1; d<Φn; d++){
                if ((e * d)%Φn==1 && d<Φn && (e * d)<=0x7fffffff){
	                printf("Φn:%d, n=%d\nint p=%d, q=%d, e=%d, d=%d;\n", Φn, n, p, q, e, d);
                }
            }
        }
    }
    //for(e=2; e<9999; e++){
    //    if (isPrime(e)){
    //        printf("素数:%d,", e);
    //    }
    //}
    
    CAntiBypass bypass;
	char strHex[2048],str[1024]="2014年7月5日 获取网站访客QQ号码DIY轻松三步搞定,网站访客QQ获取系统能抓取网站访问客户的QQ,并向访客进行邮件推送,统计客户归类、关键词来路、来路IP、到期提醒、访问页面、强制对话等。还可建立...";
    //char strHex[2048],str[1024]="0123456789_abcdefghijklnmopqrstuvwxyz_ABCDEFGHIJKLNMOPQRSTUVWXYZ";
    
    int ilen= strlen(str);

	//printf("原数据:%s\n\n",str);

 //   RSA_on(str, strHex,true);
	//printf("加密后数据:%s\n",strHex);
	//RSA_off(strHex,str,true);
	//printf("解密后数据:%s\n\n",str);

    bypass.Anti(1, str);
    //bypass.sample(str, ilen, 1, bypass.hexByPass[1], true);
    printf("加密后数据:%s\n", bypass.hexByPass[1]);
    ilen = strlen(bypass.hexByPass[1]);
    bypass.sample(bypass.hexByPass[1], ilen, 1, str, false);
	printf("解密后数据:%s\n\n",str);

 //   long tmp=0;
 //   bypass.Anti(1, 0x1314520);
 //   printf("数值加密:0x%08X\n", bypass.lngByPass[1]);
 //   bypass.sample(bypass.lngByPass[1], 1, &tmp);
 //   printf("数值解密:0x%08X\n", tmp);

    
        RSA_on("0xB4DC41F", strHex,true);
	printf("0xB4DC41F 加密后数据:%s\n",strHex);
	RSA_off(strHex,str,true);
	printf("0xB4DC41F 解密后数据:%s\n\n",str);

    Sleep(12800);
    return 1;
}
