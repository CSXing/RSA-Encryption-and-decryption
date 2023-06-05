#ifndef __类定义_标识值_文件头
#define __类定义_标识值_文件头


#include <typeinfo>

//#include <iostream>
//using std::cout;
//using std::endl;
//using std::cin;
//using std::hex;

enum 枚举_值类型
{
    枚举_值类型_字符串 = 0,
    枚举_值类型_字面值_布尔型 = 1, //字面值
    枚举_值类型_字面值_null  = 2, //字面值
    枚举_值类型_数组   = 4,
    枚举_值类型_对象   = 8,
    枚举_值类型_数字   = 0x80,
    枚举_值类型_小数   = 0x10,
    枚举_值类型_正数   = 0x20,
    枚举_值类型_整数1  = 枚举_值类型_数字 | 0x1,
    枚举_值类型_整数2  = 枚举_值类型_数字 | 0x2,
    枚举_值类型_整数4  = 枚举_值类型_数字 | 0x4,
    枚举_值类型_整数8  = 枚举_值类型_数字 | 0x8,
    枚举_值类型_正整数1  = 枚举_值类型_数字 | 枚举_值类型_正数 | 0x1,
    枚举_值类型_正整数2  = 枚举_值类型_数字 | 枚举_值类型_正数 | 0x2,
    枚举_值类型_正整数4  = 枚举_值类型_数字 | 枚举_值类型_正数 | 0x4,
    枚举_值类型_正整数8  = 枚举_值类型_数字 | 枚举_值类型_正数 | 0x8,
    枚举_值类型_小数4 = 枚举_值类型_数字 | 枚举_值类型_小数 | 0x4,
    枚举_值类型_小数8 = 枚举_值类型_数字 | 枚举_值类型_小数 | 0x8,
};

#define __是布尔型(v) (typeid(v)==typeid(bool))
#define __是Null(v) (typeid(v)==typeid(void*))
#define __是小数类型(v) (typeid(v)==typeid(double) || typeid(v)==typeid(float))
#define __是整数类型(v) (typeid(v)==typeid(char) || typeid(v)==typeid(short) || typeid(v)==typeid(int) || typeid(v)==typeid(long) || typeid(v)==typeid(__int64))
#define __是整数类型_正数(v) (typeid(v)==typeid(unsigned char) || typeid(v)==typeid(unsigned short) || typeid(v)==typeid(unsigned int) || typeid(v)==typeid(unsigned long) || typeid(v)==typeid(unsigned __int64))
#define __是字符串类型(v) (typeid(v)==typeid(char*) || typeid(v)==typeid(char const *))

#define __是数组_布尔型(v) (typeid(v)==typeid(bool*) || typeid(v)==typeid(bool const*))
#define __是数组_Null(v) (typeid(v)==typeid(void**) || typeid(v)==typeid(void const**))
#define __是数组_小数类型(v) (typeid(v)==typeid(double*) || typeid(v)==typeid(float*) || typeid(v)==typeid(double const*) || typeid(v)==typeid(float const*))
#define __是数组_整数类型(v) (typeid(v)==typeid(short*) || typeid(v)==typeid(int*) || typeid(v)==typeid(long*) || typeid(v)==typeid(__int64*) || typeid(v)==typeid(short const*) || typeid(v)==typeid(int const*) || typeid(v)==typeid(long const*) || typeid(v)==typeid(__int64 const*))
#define __是数组_整数类型_正数(v) (typeid(v)==typeid(unsigned short*) || typeid(v)==typeid(unsigned int*) || typeid(v)==typeid(unsigned long*) || typeid(v)==typeid(unsigned __int64*) || typeid(v)==typeid(unsigned short const*) || typeid(v)==typeid(unsigned int const*) || typeid(v)==typeid(unsigned long const*) || typeid(v)==typeid(unsigned __int64 const*))
#define __是数组_字符串类型(v) (typeid(v)==typeid(char**) || typeid(v)==typeid(char const**))

class 类定义_标识值;

#pragma pack(1)
typedef struct 树定义_列表指针 {
    void *当前, *下一个;
} *树定义_p列表指针;

typedef struct 树定义_标识值
{
    char 标识[32], *值;
    unsigned int 长度;
    unsigned char 类型; // 0x00=字符串
                      // 0x01=字面值 0/1(false/true)
                      // 0x02=枚举_值类型_字面值_null null
                      // 0x04=数组, 0x08=对象
                      // 0x80=数字 0x80=小数
                      // 1000 0001 char         1100 0001 unsigned 1char
                      // 1000 0010 short        1100 0010 unsigned 2short
                      // 1000 0100 int          1100 0100 unsigned 4int
                      // 1000 1000 longlong     1100 1000 unsigned 8longlong
                      // 1001 0100 float
                      // 1001 1000 double
    树定义_标识值 *下一个;
    bool _bool() {
        if (类型 == 枚举_值类型_字面值_布尔型)
            return *(bool*)值;
        return false;
    }
    char _char() {
        if (类型 == 枚举_值类型_整数1)
            return 值[0];
        return 0;
    }
    float _float() {
        if (类型 == 枚举_值类型_小数4)
            return *(float*)值;
        return 0;
    }
    double _double() {
        if (类型 == 枚举_值类型_小数8)
            return *(double*)值;
        return 0;
    }
    short _short() {
        if (类型 == 枚举_值类型_整数2)
            return *(short*)值;
        return 0;
    }
    int _int() {
        if (类型 == 枚举_值类型_整数4)
            return *(int*)值;
        return 0;
    }
    __int64 _int_64() {
        if (类型 == 枚举_值类型_整数8)
            return *(__int64*)值;
        return 0;
    }
    unsigned char _uchar() {
        if (类型 == 枚举_值类型_正整数1)
            return ((char*)值)[0];
        return 0;
    }
    unsigned short _ushort() {
        if (类型 == 枚举_值类型_正整数2)
            return ((short*)值)[0];
        return 0;
    }
    unsigned int _uint() {
        if (类型 == 枚举_值类型_正整数4)
            return ((unsigned int*)值)[0];
        return 0;
    }
    unsigned __int64 _uint_64() {
        if (类型 == 枚举_值类型_正整数8)
            return ((__int64*)值)[0];
        return 0;
    }
    char *_string() {
        if (类型 == 枚举_值类型_字符串)
            return 值;
        return 0;
    }
    char *_null() {
        if (类型 == 枚举_值类型_字面值_null)
            return "null";
        return 0;
    }
    树定义_标识值 *_array() {
        if (类型 == 枚举_值类型_数组)
            return (树定义_标识值 *)值;
        return 0;
    }
    类定义_标识值 *_object() {
        if (类型 == 枚举_值类型_对象)
            return (类定义_标识值 *)值;
        return 0;
    }
} *树定义_p标识值;
#pragma pack()


class 类定义_标识值
{
private:
    树定义_标识值 _主, *_上一项, *_当前项;
    char _上次查找标识[256], *_结果串;

    树定义_p标识值 查找(const char *标识)
    {
        return 查找(标识, &this->_主);
    }
    树定义_p标识值 查找(const char *标识, 树定义_p标识值 _主项)
    {
        if (_主项)
        {
            if (strcmpi(this->_上次查找标识, 标识)==0) return this->_当前项;
            int icount=0;
            this->_上一项 = 0;
                this->_当前项 = _主项;
            while (this->_当前项) {
                if (strcmpi(this->_当前项->标识, 标识)==0) {
                    sprintf_s(this->_上次查找标识, 标识);
                    return this->_当前项;
                }
                this->_上一项 = this->_当前项;
                this->_当前项 = this->_当前项->下一个;
            }
        } else {
            memset(this->_上次查找标识, 0, 256);
            this->_上一项 = 0;
            this->_当前项 = _主项;
        }
        return this->_当前项;
    }
    
    树定义_p标识值 __处理(const char *标识, void *标识值, unsigned char 值类型, unsigned int 值长度)
    {
        return this->__处理(标识, 标识值, 值类型, 值长度, &this->_主);
    }
    树定义_p标识值 __处理(unsigned int 序号, void *标识值, unsigned char 值类型, unsigned int 值长度, 树定义_p标识值 _主项)
    {
        char _Id[16]={0};
        sprintf_s(_Id, "%u", 序号);
        return this->__处理(_Id, 标识值, 值类型, 值长度, _主项);
    }
    树定义_p标识值 __处理(int 序号, void *标识值, unsigned char 值类型, unsigned int 值长度, 树定义_p标识值 _主项)
    {
        char _Id[16]={0};
        sprintf_s(_Id, "%d", 序号);
        return this->__处理(_Id, 标识值, 值类型, 值长度, _主项);
    }
    树定义_p标识值 __处理(const char *标识, void *标识值, unsigned char 值类型, unsigned int 值长度, 树定义_p标识值 _主项)
    {
        if (_主项)
        {
            树定义_p标识值 _项 = this->查找(标识, _主项);

            if (_项!=0){
                _项->类型 = 值类型;
                this->改(_项, 标识值, 值长度);
                return _项;
            }

            if (this->_上一项!=0) {
                if (this->_上一项->标识[0]==0 && this->_上一项->值==0 && this->_上一项->下一个==0) {
                    this->_当前项 = this->_上一项;
                } else {
                    this->_当前项 = (树定义_p标识值)malloc(sizeof(树定义_标识值));
                    this->_上一项->下一个 = this->_当前项;
                }
            } else 
                this->_当前项=0;
        } else 
            this->_当前项=0;

        if (!this->_当前项){
            this->_当前项 = (树定义_p标识值)malloc(sizeof(树定义_标识值));
        }
        memset(this->_当前项, 0, sizeof(树定义_标识值));
        sprintf_s(this->_当前项->标识, 标识);
        this->_当前项->类型 = 值类型;
        this->改(this->_当前项, 标识值, 值长度);

        return this->_当前项;
    }
    //template <class 数据类型>
    //unsigned char 获取类型(数据类型 标识值)
    //{
    //    if __是小数类型(标识值) return 枚举_值类型_数字 | 枚举_值类型_小数 | sizeof(标识值);
    //    
    //    if __是整数类型(标识值) return 枚举_值类型_数字 | sizeof(标识值);
    //    if __是整数类型_正数(标识值) return 枚举_值类型_数字 | 枚举_值类型_正数 | sizeof(标识值);
    //    
    //    if __是字符串类型(标识值) return 枚举_值类型_字符串;

    //    if __是布尔型(标识值) return 枚举_值类型_字面值;
    //    if __是Null(标识值) return 枚举_值类型_字面值_null;

    //    if (__是数组_布尔型(数据类型) || __是数组_Null(数据类型) || __是数组_小数类型(数据类型) || __是数组_整数类型(数据类型) || __是数组_整数类型_正数(数据类型) || __是数组_字符串类型(数据类型))
    //            return 枚举_值类型_数组;

    //     return 枚举_值类型_字符串;
    //}
    void __分析_项值(树定义_p标识值 _项, char *值_分隔符=":", char *项_分隔符=",")
    {
        if (值_分隔符) {
            strcat(this->_结果串, "\"");
            strcat(this->_结果串, _项->标识);
            strcat(this->_结果串, "\"");
            strcat(this->_结果串, 值_分隔符);
        }
        //std::cout << "_结果串:" << this->_结果串 << std::endl;

        unsigned char _值类型 = _项->类型;
        if (_值类型 == 枚举_值类型_对象) {
            strcat(this->_结果串, "{");
            树定义_p标识值 _子项 = _项->_object()->operator 树定义_p标识值();
            while (_子项)
            {
                this->__分析_项值(_子项);
                _子项 = _子项->下一个;
            }
            unsigned int _last= strlen(this->_结果串);
            if (this->_结果串[_last-1] == ',') this->_结果串[_last-1]=0;
            strcat(this->_结果串, "}");

        } else if (_值类型 == 枚举_值类型_数组) {
            strcat(this->_结果串, "[");
            树定义_p标识值 _子项 = _项->_array();
            while (_子项)
            {
                this->__分析_项值(_子项, 0);
                _子项 = _子项->下一个;
            }
            unsigned int _last= strlen(this->_结果串);
            if (this->_结果串[_last-1] == ',') this->_结果串[_last-1]=0;
            strcat(this->_结果串, "]");

        } else if (_值类型 == 枚举_值类型_字面值_null) {
            strcat(this->_结果串, "null");

        } else if (_值类型 == 枚举_值类型_字面值_布尔型) {
            if (_项->_bool()) {
                strcat(this->_结果串, "true");
            } else {
                strcat(this->_结果串, "false");
            }
        } else if ((_值类型 & 枚举_值类型_数字)== 枚举_值类型_数字) {
            char _临时数值[256] = {0};
            if (_值类型== 枚举_值类型_小数4) {
                sprintf_s(_临时数值, "%f", _项->_float());
            } else if (_值类型 == 枚举_值类型_小数8) {
                sprintf_s(_临时数值, "%f", _项->_double());

            } else if (_值类型 == 枚举_值类型_整数1) {
                sprintf_s(_临时数值, "%d", _项->_char());
            } else if (_值类型 == 枚举_值类型_整数2) {
                sprintf_s(_临时数值, "%d", _项->_short());
            } else if ( _值类型 == 枚举_值类型_整数4) {
                sprintf_s(_临时数值, "%d", _项->_int());
            } else if ( _值类型 == 枚举_值类型_整数8) {
                sprintf_s(_临时数值, "%I64d", _项->_int());

            } else if (_值类型 == 枚举_值类型_正整数1) {
                sprintf_s(_临时数值, "%u", _项->_uchar());
            } else if (_值类型 == 枚举_值类型_正整数2) {
                sprintf_s(_临时数值, "%u", _项->_ushort());
            } else if ( _值类型 == 枚举_值类型_正整数4) {
                sprintf_s(_临时数值, "%u", _项->_uint());
            } else if ( _值类型 == 枚举_值类型_正整数8) {
                sprintf_s(_临时数值, "%I64u", _项->_uint_64());
            }
            strcat(this->_结果串, _临时数值);
        } else {
            strcat(this->_结果串, "\"");
            strcat(this->_结果串, _项->_string());
            strcat(this->_结果串, "\"");
        }
        if (项_分隔符) strcat(this->_结果串, 项_分隔符);
    }

    void __清除(树定义_p标识值 _项)
    {
        while (_项)
        {
            if (_项->类型 == 枚举_值类型_数组 || _项->类型 == 枚举_值类型_对象)
            {
                this->__清除((树定义_p标识值)_项->值);
            }
            if(_项->值) free(_项->值);
            树定义_p标识值 _下一个 = _项->下一个;
            free(_项);
            _项 = _下一个;
        }
    }
public:

    类定义_标识值()
    {
        memset(&this->_主, 0, sizeof(树定义_标识值));
        this->_上一项 = 0;
        this->_结果串 = (char*)malloc(sizeof(char)*2049);
    }
    ~类定义_标识值()
    {
        if (this->_主.类型 == 枚举_值类型_数组 || this->_主.类型 == 枚举_值类型_对象)
        {
            this->__清除((树定义_p标识值)this->_主.值);
        }
        this->__清除(this->_主.下一个);

        if(this->_主.值) free(this->_主.值);
        if(this->_结果串) free(this->_结果串);
        memset(&this->_主, 0, sizeof(树定义_标识值));
    }

    operator 树定义_p标识值()
    {
        return &this->_主;
    }

    树定义_p标识值 operator [](const char *标识)
    {
        return this->查找(标识);
    }
/* ======================================= 字符串相关功能 ======================================= */
/* 字符串 */
#define __建方法_字符串(参数类型) \
    树定义_p标识值 建(const char *标识, 参数类型 标识值) { return this->__处理(标识, (void*)&标识值[0], 枚举_值类型_字符串, strlen(标识值)); }

#define __建数组_方法_字符串(参数类型) \
    树定义_p标识值 建(const char *标识, 参数类型* 标识列表值, unsigned int 个数) { \
        if (!个数) return 0; \
        树定义_p标识值 _主项 = this->__处理(标识, 0, 枚举_值类型_数组, 个数); \
        参数类型* _指针 = &标识列表值[0]; \
        树定义_p标识值 _项 = this->__处理(0, (void*)&_指针[0][0], 枚举_值类型_字符串, strlen(_指针[0]), 0); \
        _主项->值 = (char*)_项; \
        for(unsigned int i=1; i<个数; i++) { this->__处理(i, (void*)&_指针[i][0], 枚举_值类型_字符串, strlen(_指针[i]), _项); } \
        return _主项; \
    }

    __建方法_字符串(const char*)
    __建方法_字符串(char*)

    __建数组_方法_字符串(const char*)
    __建数组_方法_字符串(char*)
/* ======================================= 数值相关功能 ======================================= */
/* 数值 */
#define __建方法_数值(参数类型, 值类型) \
    树定义_p标识值 建(const char *标识, 参数类型 标识值) { return this->__处理(标识, (void*)&标识值, (枚举_值类型_数字 | 值类型 | sizeof(标识值)), sizeof(标识值)); }

#define __建数组_方法_数值(参数类型, 值类型) \
    树定义_p标识值 建(const char *标识, 参数类型* 标识列表值, unsigned int 个数) { \
        if (!个数) return 0; \
        树定义_p标识值 _主项 = this->__处理(标识, 0, 枚举_值类型_数组, 个数); \
        参数类型 *_指针 = &标识列表值[0]; \
        _主项->值 = (char*)this->__处理(0, (void*)&_指针[0], (枚举_值类型_数字 | 值类型 | sizeof(_指针[0])), sizeof(_指针[0]), 0); \
        for(unsigned int i=1; i<个数; i++) { this->__处理(i, (void*)&_指针[i], (枚举_值类型_数字 | 值类型 | sizeof(_指针[i])), sizeof(_指针[i]), (树定义_p标识值)_主项->值); } \
        return _主项; \
    }

    /* 数值 带符号 小数 */
    __建方法_数值(float, 枚举_值类型_小数)
    __建方法_数值(double, 枚举_值类型_小数)

    __建数组_方法_数值(float, 枚举_值类型_小数)
    __建数组_方法_数值(double, 枚举_值类型_小数)
    __建数组_方法_数值(const float, 枚举_值类型_小数)
    __建数组_方法_数值(const double, 枚举_值类型_小数)
    /* 数值 带符号 整数 */
    __建方法_数值(short, 0)
    __建方法_数值(int, 0)
    __建方法_数值(long, 0)
    __建方法_数值(__int64, 0)

    __建数组_方法_数值(short, 0)
    __建数组_方法_数值(int, 0)
    __建数组_方法_数值(long, 0)
    __建数组_方法_数值(__int64, 0)
    /* 数值 无符号 */
    __建方法_数值(unsigned char, 枚举_值类型_正数)
    __建方法_数值(unsigned short, 枚举_值类型_正数)
    __建方法_数值(unsigned int, 枚举_值类型_正数)
    __建方法_数值(unsigned long, 枚举_值类型_正数)
    __建方法_数值(unsigned __int64, 枚举_值类型_正数)
    
    __建数组_方法_数值(unsigned char, 枚举_值类型_正数)
    __建数组_方法_数值(unsigned short, 枚举_值类型_正数)
    __建数组_方法_数值(unsigned int, 枚举_值类型_正数)
    __建数组_方法_数值(unsigned long, 枚举_值类型_正数)
    __建数组_方法_数值(unsigned __int64, 枚举_值类型_正数)
/* ======================================= 布尔型 & null相关功能 ======================================= */
/* 布尔型 & null */
#define __建方法_布尔型(参数类型) \
    树定义_p标识值 建(const char *标识, 参数类型 标识值) { return this->__处理(标识, (void*)&标识值, 枚举_值类型_字面值_布尔型, sizeof(标识值)); }

#define __建数组_方法_布尔型(参数类型) \
    树定义_p标识值 建(const char *标识, 参数类型 *标识列表值, unsigned int 个数) { \
        if (!个数) return 0; \
        树定义_p标识值 _主项 = this->__处理(标识, 0, 枚举_值类型_数组, 个数); \
        参数类型 *_指针 = &标识列表值[0]; \
        _主项->值 = (char*)this->__处理(0, (void*)&_指针[0], 枚举_值类型_字面值_布尔型, sizeof(_指针[0]), 0); \
        for(unsigned int i=1; i<个数; i++) { 树定义_p标识值 _项 = this->__处理(i, (void*)&_指针[i], 枚举_值类型_字面值_布尔型, sizeof(_指针[i]), (树定义_p标识值)_主项->值); } \
        return _主项; \
    }

    __建方法_布尔型(bool);
    
    __建数组_方法_布尔型(bool);

    /* null ,void *标识值=0 */
    树定义_p标识值 建(const char *标识) { return this->__处理(标识, 0, 枚举_值类型_字面值_null, 1); }
    
    /* 对象 */
    树定义_p标识值 建(const char *标识, 类定义_标识值 *对象项) {
        树定义_p标识值 _主项 = this->__处理(标识, 0, 枚举_值类型_对象, sizeof(void*));
        _主项->值 = (char*)((树定义_p标识值)对象项);
        return _主项;
    }
/* ======================================= 建数组相关功能 ======================================= */
    void 类定义_标识值::建数组(const char *标识, char* 格式化字串_值, ...)
    {
        #define __读参(_类型) _类型 _读取值 = va_arg(arg_ptr, _类型);
        
        #define __设字符串值() \
            if (id==0) { _主项->值 = (char*)this->__处理(0, (void*)&_读取值[0], 枚举_值类型_字符串, strlen(_读取值), 0); \
            } else { this->__处理(id, (void*)&_读取值[0], 枚举_值类型_字符串, strlen(_读取值), (树定义_p标识值)_主项->值); \
            } _主项->长度++; id++;

        #define __设值(值类型) \
            if (id==0) { _主项->值 = (char*)this->__处理(0, (void*)&_读取值, (枚举_值类型_数字 | 值类型 | sizeof(_读取值)), sizeof(_读取值), 0); \
            } else { this->__处理(id, (void*)&_读取值, (枚举_值类型_数字 | 值类型 | sizeof(_读取值)), sizeof(_读取值), (树定义_p标识值)_主项->值); \
            } _主项->长度++; id++;

        #define __设布尔值() \
            if (id==0) { _主项->值 = (char*)this->__处理(0, (void*)&_读取值, 枚举_值类型_字面值_布尔型, sizeof(_读取值), 0); \
            } else { this->__处理(id, (void*)&_读取值, 枚举_值类型_字面值_布尔型, sizeof(_读取值), (树定义_p标识值)_主项->值); \
            } _主项->长度++; id++;

        #define __设null值() \
            if (id==0) { _主项->值 = (char*)this->__处理(0, (void*)&_读取值, 枚举_值类型_字面值_null, 1, 0); \
            } else { this->__处理(id, 0, 枚举_值类型_字面值_null, 1, (树定义_p标识值)_主项->值); \
            } _主项->长度++; id++;

        unsigned int id = 0;
        树定义_p标识值 _主项 = this->__处理(标识, 0, 枚举_值类型_数组, 0);
        va_list arg_ptr;
        va_start(arg_ptr, 格式化字串_值);
        char *_指针 = &格式化字串_值[0];
        while (*_指针) {
            if(*_指针=='\\') {_指针+=2;}
            if(*_指针=='%') {
                _指针++;
                int iCount = 0;
                while(*_指针 && iCount<=5) {
                    if (*_指针=='b' || *_指针=='B') {
                        __读参(bool)
                        __设布尔值()
                        break;
                    } else if (*_指针=='c' || *_指针=='C') {
                        __读参(char)
                        if (_读取值==0) {
                            __设null值();
                        } else {
                            __设值(0)
                        }
                        break;
                    } else if (*_指针=='e' || *_指针=='f' ||
                              *_指针=='E' || *_指针=='F') {
                        __读参(double)
                        __设值(枚举_值类型_小数)
                        break;
                    } else if (*_指针=='i' || *_指针=='I') {
                        _指针++; iCount++;
                        bool isInt64 = false, isUnsigned = false;
                        while(*_指针) {
                            if(*_指针==',' || *_指针=='%' || *_指针==']' || *_指针=='}') { break; }
                            if (*_指针=='6' && *(_指针+1)=='4') { isInt64 = true; }
                            if (*_指针=='u' || *_指针=='U') { isUnsigned = true; }
                            _指针++; iCount++;
                        }
                        if (isInt64) {
                            if (isUnsigned) {
                                __读参(unsigned __int64)
                                __设值(枚举_值类型_正数)
                            } else {
                                __读参(__int64)
                                __设值(0)
                            }
                        } else {
                            if (isUnsigned) {
                                __读参(unsigned int)
                                __设值(枚举_值类型_正数)
                            } else {
                                __读参(int)
                                __设值(0)
                            }
                        }
                        break;
                    } else if (*_指针=='u' || *_指针=='U') {
                        __读参(unsigned int)
                        __设值(枚举_值类型_正数)
                        break;
                    } else if (*_指针=='d' || *_指针=='l' || *_指针=='x' ||
                              *_指针=='D' || *_指针=='L' || *_指针=='X') {
                        __读参(int)
                        __设值(0)
                        break;
                    } else if (*_指针=='s' || *_指针=='S') {
                        __读参(char*)
                        __设字符串值()
                        break;
                    } else {
                        if(*(_指针+1)==',' || *(_指针+1)=='%' || *(_指针+1)==']' || *(_指针+1)=='}') { break; }
                        _指针++; iCount++;
                    }
                }
            }
            _指针++;
        }
        va_end(arg_ptr);
    }
/* ======================================= 编辑相关功能 ======================================= */
    void 改(树定义_p标识值 _项, const void *标识值, const unsigned int 标识值长度)
    {
        if(_项->值) free(_项->值);
        if (_项->类型 == 枚举_值类型_对象 || _项->类型 == 枚举_值类型_数组) {
            _项->长度 = 标识值长度;
            _项->值 = 0;
        } else if (_项->类型 == 枚举_值类型_字面值_null) {
            _项->长度 = 1;
            _项->值 = 0;
        } else {
            _项->长度 = 标识值长度;
            _项->值 = (char*)malloc(_项->长度+16);
            memset(_项->值, 0, _项->长度+16);
            memcpy(&_项->值[0], 标识值, 标识值长度);
        }
    }
/* ======================================= 转字符串相关功能(排序) ======================================= */
    void _快速排序(树定义_p标识值 *_列表, short _左, short _右)
    {
        if (_左 >= _右) return;

        short i=_左, j=_右;

        树定义_p标识值 _项 = _列表[_左];
        while (i<j)
        {
            // 从右往左查找第一个小于基准元素的元素
            while (i<j && strcmp(_列表[j]->标识, _项->标识)>=0) --j;
            if (i<j) _列表[i++] = _列表[j];
            
            // 从左往右查找第一个大于基准元素的元素
            while (i<j && strcmp(_列表[i]->标识, _项->标识)<0) ++i;
            if (i<j) _列表[j--] = _列表[i];
        }

        _列表[i] = _项; // 将基准元素放回正确位置
        this->_快速排序(_列表,   _左, i - 1);  // 对左子序列递归排序
        this->_快速排序(_列表, i + 1,   _右);  // 对右子序列递归排序
    }

    const char *排序_转字符串()
    {
        USHORT _个数 = 0, id=0;
        树定义_p标识值 _项 = &this->_主;
        while (_项) { _个数++; _项=_项->下一个; };

        //当s1<s2时，返回为负数；
        //当s1=s2时，返回值= 0；
        //当s1>s2时，返回正数。
        树定义_p标识值 *_列表 = (树定义_p标识值*)malloc(sizeof(void*)*_个数*2);
        memset(_列表, 0, sizeof(void*)*_个数*2);

        _项 = &this->_主;
        while (_项) { _列表[id++] = _项; _项=_项->下一个; };
        
        this->_快速排序(_列表, 0, _个数-1);

        memset(this->_结果串, 0, sizeof(char)*2049);
        id=0;
        strcat(this->_结果串, "{");
        while (_列表[id])
        {
            //std::cout << "=======================处理:" << _项->标识 << std::endl;
            this->__分析_项值(_列表[id]);
            id++;
        }
        unsigned int _last= strlen(this->_结果串);
        if (this->_结果串[_last-1] == ',') this->_结果串[_last-1]=0;
        strcat(this->_结果串, "}");

        free(_列表);

        return &this->_结果串[0];
    }

    const char *转字符串()
    {
        memset(this->_结果串, 0, sizeof(char)*2049);
        树定义_p标识值 _项 = &this->_主;
        strcat(this->_结果串, "{");
        while (_项)
        {
            //std::cout << "=======================处理:" << _项->标识 << std::endl;
            this->__分析_项值(_项);
            _项 = _项->下一个;
        }
        unsigned int _last= strlen(this->_结果串);
        if (this->_结果串[_last-1] == ',') this->_结果串[_last-1]=0;
        strcat(this->_结果串, "}");
        return &this->_结果串[0];
    }
};

#endif
