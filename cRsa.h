#ifndef xRSA_H
#define xRSA_H


class 类定义_加密
{
public:
    类定义_加密();
    ~类定义_加密();
    unsigned long 加密(const char *明文, unsigned long 明文长度, char *密文);
    unsigned long 解密(const char *密文, unsigned long 密文长度, char *明文);

    /**
        方法：生成密钥
        参数：密钥版本，范围0-0xFF
        描述：产生私钥和公钥
    */
    void 生成密钥(const unsigned char 密钥版本);
    /**
        方法：密钥
        参数：
        描述：获取公钥数据
            公钥:(7BEF 70B7 2C41 B9AD 6F1F 7193 FCEF 8605 8DD9 70B7 6DCD 6FFB 19B5)
            私钥:(0B0F AF27 56D1 1CA5 73FF 6C9B FCEF 3C0D 2479 AF27 2525 1B83 E5CD)
    */
    unsigned short* 私钥();
    unsigned long 密钥长度();
    void 同步私钥();
    
    unsigned short 素数(const unsigned short _in起始值, const unsigned char _in个数=10);
    //判断是否是素数
    bool 是否素数(const unsigned short _in值);
    /**
        方法：设置密钥
        参数：[uint]密钥 {xxxx,y,xxxx}
             [uint]大小，必须是奇数
        描述：初始化密钥对
    */
    void 密钥(unsigned short *_in密钥, unsigned int _in大小);
private:
    unsigned short *_公钥_乘积_xAx, *_私钥_乘积_xAx, _公私积_总数, _乘积_索引;

    //unsigned int _乘积; //n=p*q
    //unsigned int _私钥; //a对于φ(n)的模反元素
    //unsigned int _公钥;

    void _释放内存();

    bool _密钥已存在(unsigned short _公钥, unsigned short _私钥);
    
    //模乘运算，返回值 x=a*b mod n
    //模幂运算，返回值 x=base^pow mod n
    unsigned int PowMod(unsigned int _in值, unsigned int _in密钥, unsigned int _in乘积);
    
    //返回d=gcd(a,b);和对应于等式ax+by=d中的x,y
    int extend_gcd(int one, int two, int &x, int &y);
    //ax = 1(mod n) 求X
    int reverseMod(int one, int two);

    /* ================================
        函数: Rand
        参数: [in]seeds=种子数,最大值
        描述: 随机产生整型数字
       ================================ */
    unsigned int time_stamp;
    unsigned int Rand(const unsigned int seeds);
};
#endif