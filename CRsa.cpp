
#include <windows.h>
#include <stdio.h>
#include <string>
#include <sys/timeb.h>
#include "cRsa.h"

int 素数表[98] = {
    0x0002,0x0003,0x0005,0x0007,0x000B,0x000D,0x0011,0x0013,0x0017,0x001D,
    0x001F,0x0025,0x0029,0x002B,0x002F,0x0035,0x003B,0x003D,0x0043,0x0047,
    0x0049,0x004F,0x0053,0x0059,0x0061,0x0065,0x0067,0x006B,0x006D,0x0071,
    0x007F,0x0083,0x008B,0x0095,0x0097,0x009D,0x00A3,0x00A7,0x00AD,0x00B5,
    0x00C1,0x00C5,0x00C7,0x00D3,0x00DF,0x00E5,0x00E9,0x00F1,0x00FB, //49
    0x7FED,0x5551,0x332F,0x2485,0x1741,0x13AF,0x0F0D,0x0D79,0x0B1B,0x08CB,
    0x0841,0x06DF,0x063D,0x05F3,0x0565,0x04CF,0x0455,0x042D,0x03D1,0x0397,
    0x0377,0x033D,0x0313,0x02DD,0x02A1,0x0287,0x0277,0x025F,0x0259,0x0241,
    0x01FD,0x01F3,0x01D3,0x01B7,0x01B1,0x0199,0x0191,0x0185,0x0175,0x0167,
    0x0151,0x014B,0x013D,0x0133,0x0125,0x011B,0x0119,0x010F,0x0101, //98
};


类定义_加密::类定义_加密() {
    this->_公私积_总数 = 9;
    this->_乘积_索引 = (this->_公私积_总数-1) / 2;
    this->_公钥_乘积_xAx = this->_私钥_乘积_xAx = 0;
}
类定义_加密::~类定义_加密() {
    this->_释放内存();
}
unsigned long 类定义_加密::加密(const char *明文, unsigned long 明文长度, char *密文) {
    if (密文 == 0) { return 0; }
    if (明文长度 >= 0xFFFFFFL) { return 0; }

    int iK=0;
    unsigned long i = 0, j = 0, id = 0, iNum = 0, iN = 0;
    unsigned char _ucOne = 0;
    //先组织二进制的中英文字符对照表
    unsigned long _对照表长度 = (明文长度+7)/8;
    密文[0] = (_对照表长度 & 0xFF);
    密文[1] = (_对照表长度 & 0xFF00)/0x100;
    密文[2] = (_对照表长度 & 0xFF0000)/0x10000;
    
    //处理_对照表，只记录中文字符位置
    i=0;
    memset(&密文[3], 0, _对照表长度);
    while (i < 明文长度)
    {
        _ucOne = (unsigned char)明文[i];
        if (_ucOne & 0x80) { //中文
            id = i/8+3;
            密文[id] += 1<<(7-(i%8));
        }
        i++;
    }
    
    iK=0; i=0; id=_对照表长度+3;
    while (i < 明文长度)
    {
        _ucOne = (unsigned char)明文[i++];
        if ((_ucOne & 0x80)) {
            iNum = _ucOne;
        } else {
            iNum = _ucOne * 0x100;
            if (i < 明文长度){
                _ucOne = (unsigned char)明文[i++];
                iNum += _ucOne;
            }
        }
            iN = PowMod(iNum, this->_公钥_乘积_xAx[iK], this->_公钥_乘积_xAx[this->_乘积_索引]);
            密文[id++] = (unsigned char)( iN & 0xFF);
            密文[id++] = (unsigned char)((iN & 0xFF00) / 0x100);
        iK++;
        if(iK==this->_乘积_索引) {
            iK++;
        } else if(iK>=this->_公私积_总数) {
            iK=0;
        }
    }
    //FILE *hFiles = fopen("_密文.txt", "wb");
    //    fwrite(密文, sizeof(char), id, hFiles);
    //fclose(hFiles);
    return id;
}

unsigned long 类定义_加密::解密(const char *密文, unsigned long 密文长度, char *明文) {
    if (明文 == 0) { return 0; }

    int iK=0;
    unsigned long i = 0, j = 0, id = 0, iNum = 0, iN = 0;
    unsigned char _ucOne = 0;
    id = 3 + (unsigned char)密文[0] + (unsigned char)密文[1]*0x100L + (unsigned char)密文[2]*0x10000L;
    
    while (id < 密文长度)
    {
        iN = (unsigned char)密文[id++];
        iN+= (unsigned char)密文[id++] * 0x100;
            iNum = PowMod(iN, this->_私钥_乘积_xAx[iK], this->_私钥_乘积_xAx[this->_乘积_索引]);
            if ((iNum & 0x80)) {
                _ucOne = (unsigned char)((iNum&0x7F00)/0x100);
                if (_ucOne==0) {
                    int _id=密文[i/8+3]; j=1<<(7-(i%8));
                    if ((_id & j)==0) {
                        明文[i++] = 0;
                    }
                } else {
                    明文[i++] = _ucOne;
                }
                明文[i++] = (unsigned char)(iNum&0xFF);
            } else {
                明文[i++] = (unsigned char)((iNum&0x7F00)/0x100);
                明文[i++] = (unsigned char)(iNum&0xFF);
            }
        iK++;
        if(iK==this->_乘积_索引) {
            iK++;
        } else if(iK>=this->_公私积_总数) {
            iK=0;
        }
    }
    //FILE *hFiles = fopen("_明文.txt", "wb");
    //    fwrite(明文, sizeof(char), i-1, hFiles);
    //fclose(hFiles);
    return i-1;
}

bool 类定义_加密::_密钥已存在(unsigned short _公钥, unsigned short _私钥) {
    int seqId=0, revId = this->_公私积_总数-1, halfCount = this->_公私积_总数/2+1;
    for (int seqId=0; seqId<halfCount; seqId++)
    {
        if (this->_公钥_乘积_xAx[seqId] == _公钥 || this->_私钥_乘积_xAx[seqId] == _私钥) {
            return true;
        }
        if (this->_公钥_乘积_xAx[revId-seqId] == _公钥 || this->_私钥_乘积_xAx[revId-seqId] == _私钥) {
            return true;
        }
    }
    return false;
}

/**
    方法：生成密钥
    参数：密钥版本，范围0-0xFF
    描述：产生私钥和公钥
*/
void 类定义_加密::生成密钥(const unsigned char 密钥版本)
{
    const unsigned char _pqMax=98;
    const unsigned char _pqHalf=_pqMax/2;
    unsigned char pid = this->Rand(_pqHalf) & 0xFF;
    if (1<=密钥版本) pid = ((int)(_pqHalf * 密钥版本*0.75f) % (_pqHalf)) & 0xFF;
    unsigned char qid = (this->Rand(_pqHalf)+_pqHalf) & 0xFF;
    unsigned short p = 素数表[pid], q = 素数表[qid];
    unsigned long i=0, id = 0, _公钥 = 0, _私钥 = 0, _乘积 = p * q;
    while(_乘积>0xFFFF || _乘积<0x8000 || p==q) { qid = this->Rand(_pqHalf)+_pqHalf; q = 素数表[qid]; _乘积 = p * q; }
    //释放内存
    this->_释放内存();
    //根据版本生成密钥对
    this->_公私积_总数 = 256;
    this->_乘积_索引 = (this->_公私积_总数-1+(this->_公私积_总数%2))*0.334f;
    unsigned short _总数 = sizeof(unsigned short)*this->_公私积_总数+1;
    this->_公钥_乘积_xAx = (unsigned short*)malloc(_总数);
    this->_私钥_乘积_xAx = (unsigned short*)malloc(_总数);
    memset(this->_公钥_乘积_xAx, 0, _总数);
    memset(this->_私钥_乘积_xAx, 0, _总数);
    //生产密钥
    for (i=0; i<this->_公私积_总数; i++)
    {
        _公钥 = this->素数(this->Rand(0xEFFE) + 0x1001);
        _私钥 = reverseMod(_公钥, (p - 1)*(q - 1));
        while (this->_密钥已存在(_公钥,_私钥)) {
	        _公钥 = this->素数(this->Rand(0xEFFE) + 0x1001);
	        _私钥 = reverseMod(_公钥, (p - 1)*(q - 1));
        }
        this->_公钥_乘积_xAx[id] = _公钥;
        this->_私钥_乘积_xAx[id] = _私钥;
        id++;
    }
    this->_公钥_乘积_xAx[this->_乘积_索引] = this->_私钥_乘积_xAx[this->_乘积_索引] = _乘积;
}
    
/**
    方法：密钥
    参数：
    描述：获取公钥数据
        公钥:(7BEF 70B7 2C41 B9AD 6F1F 7193 FCEF 8605 8DD9 70B7 6DCD 6FFB 19B5)
        私钥:(0B0F AF27 56D1 1CA5 73FF 6C9B FCEF 3C0D 2479 AF27 2525 1B83 E5CD)
*/
unsigned long 类定义_加密::密钥长度()
{
    return sizeof(unsigned short)*this->_公私积_总数;
}
unsigned short* 类定义_加密::私钥()
{
    return this->_私钥_乘积_xAx;
}

void 类定义_加密::同步私钥()
{
    unsigned short _总数 = sizeof(unsigned short)*this->_公私积_总数+1;
    memset(&this->_私钥_乘积_xAx[0], 0, _总数);
    memcpy(&this->_私钥_乘积_xAx[0], &this->_公钥_乘积_xAx[0], _总数);
}

unsigned short 类定义_加密::素数(const unsigned short _in起始值, const unsigned char _in个数)
{
    for (int i=0; i<_in个数; i++)
    {
        if (this->是否素数(_in起始值+i)) return _in起始值+i;
    }
    return 0;
}
//判断是否是素数
bool 类定义_加密::是否素数(const unsigned short _in值)
{
	if (_in值 == 2 || _in值 == 3) return true;
    if (_in值 <= 1 || (_in值 % 6 != 1 && _in值 % 6 != 5)) return false;

	unsigned short i, halfNum = (int)sqrt((double)_in值);
	for (i = 5; i <= halfNum; i += 6)
		if (_in值 % i == 0 || _in值 % (i + 2) == 0)
			return false;
	return true;
}


//返回d=gcd(a,b);和对应于等式ax+by=d中的x,y
int 类定义_加密::extend_gcd(int one, int two, int &x, int &y) {
    if (one == 0 && two == 0) return -1;//无最大公约数
    if (two == 0) {
        x = 1; y = 0; return one;
    }
    int d = extend_gcd(two, one%two, y, x);
    y -= one / two * x;
    return d;
}
//ax = 1(mod n) 求X
int 类定义_加密::reverseMod(int one, int two) {
    int x, y;
    int d = extend_gcd(one, two, x, y);
    if (d == 1)
        return (x%two + two) % two;
    else return -1;
}

/* ================================
    函数: Rand
    参数: [in]seeds=种子数,最大值
    描述: 随机产生整型数字
    ================================ */
unsigned int 类定义_加密::Rand(const unsigned int seeds)
{
    if (seeds == 0) return seeds;
    struct timeb timeSeed;
    ftime(&timeSeed);
    unsigned int _timestamp = ((timeSeed.time & 0xFFFFFFFFUL) * 0x10000UL + timeSeed.millitm) & 0xFFFFFFFFUL;
    if (_timestamp - time_stamp > 100) {
        time_stamp = _timestamp;
        srand(time_stamp); // milli time
    }
    unsigned int _randVal = rand();
    return _randVal % seeds;
}

/**
    方法：设置密钥
    参数：[uint]密钥 {xxxx,y,xxxx}
            [uint]大小，必须是奇数
    描述：初始化密钥对
*/
void 类定义_加密::密钥(unsigned short *_in密钥, unsigned int _in大小)
{
    this->_释放内存();
    this->_公私积_总数 = _in大小;
    this->_乘积_索引 = (this->_公私积_总数-1+(this->_公私积_总数%2))*0.334f;

    unsigned short _总数 = sizeof(unsigned short)*this->_公私积_总数+1;
    this->_公钥_乘积_xAx = (unsigned short*)malloc(_总数);
    this->_私钥_乘积_xAx = (unsigned short*)malloc(_总数);
    memcpy(&this->_公钥_乘积_xAx[0], &_in密钥[0], _总数);
    memcpy(&this->_私钥_乘积_xAx[0], &_in密钥[0], _总数);
}

void 类定义_加密::_释放内存() {
    if (this->_公钥_乘积_xAx) { free(this->_公钥_乘积_xAx); this->_公钥_乘积_xAx=0; }
    if (this->_私钥_乘积_xAx) { free(this->_私钥_乘积_xAx); this->_私钥_乘积_xAx=0; }
}

//模乘运算，返回值 x=a*b mod n
//模幂运算，返回值 x=base^pow mod n
unsigned int 类定义_加密::PowMod(unsigned int _in值, unsigned int _in密钥, unsigned int _in乘积)
{
    if (_in值 == 0)
        return 0;
    else if (_in密钥 == 1)
        return _in值 % _in乘积;
    else
        return (PowMod(_in值, _in密钥 / 2, _in乘积)*PowMod(_in值, _in密钥 - _in密钥 / 2, _in乘积)) % _in乘积;
}