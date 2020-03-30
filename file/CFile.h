#pragma once
#ifndef FILEC_H_NISODAISUKI
#define FILEC_H_NISODAISUKI

#include <stdio.h>
#include <string>
#include <list>
#include <iterator>
using std::string;
using std::list;
using std::iterator;

/*
    文件打开模式：
    R：具有读权限
    W：具有写权限
    C：具有创建新文件权限
    B：二进制打开
    T：文本模式打开
*/
enum OPEN_MODE
{
    RWXB,           
    RXXB
};
const char open_mode[][8] =
{
    "rb+",
    "rb"
};

enum class CFILE_RV
{
    SUCCESS,
    OPEN_FILE_FAIL,
    FILE_PTR_NULL
};



class CFILE
{
    // 文件指针
    FILE* _file_ptr = nullptr;
    
public:
    //  *****************************
    //  构造函数
    //  file_name: 文件名
    //  mode：打开方式，枚举中的一个
    //  expected_file_size:申请内存与文件的倍率。
    //   如，预估处理后的文件的大小是原始文件的1.5倍，就可以写2。默认值为1.
    //  *****************************
    CFILE_RV open(const char* file_name, OPEN_MODE mode);

    //  *****************************
    //  读文件
    //  buf: 目标缓冲区
    //  size：读取文件的大小
    //  offset:    在文件中的偏移
    //  返回操作结果
    //  *****************************
    CFILE_RV read(char* buf, long offset, unsigned int size);

    //  **********************************
    //  写文件
    //  content: 要写入的内容
    //  size:       写入的大小
    //  offset:    在文件中的偏移
    //  **********************************
    CFILE_RV write(const char* content, unsigned int size, long offset);

    //  **********************************
    //  获取文件大小
    //  **********************************
    long get_file_size();


    list<string> err_info_list;
    void print_err() {
        list<string>::iterator it_bg = err_info_list.begin();
        list<string>::iterator it_ed = err_info_list.end();
        for ( ; it_bg != it_ed; it_bg++)
        {
            string info = *it_bg;
            printf("%s\r\n", info.c_str());
        }
        err_info_list.clear();
    }
};

/*
文件操作


打开模式
    具有创建属性
    不具有创建属性，报错
    默认如果没有这个文件就报错

成员：
方案1：
    文件指针
    文件偏移
    文件大小

方案2：
文件映射内存
    内存堆地址指针
    文件偏移
    文件大小

构造函数：检查文件指针，不为空，存储文件指针，否则报错。
    myfile(enum mode, char);

读
    myread(char* buf, unsiged int size)
    //  重置文件指针
    myreread(char* buf, unsiged int size)
写
    mywrite(char* buf, unsiged int size)
    //  重置文件指针
    myrewrite(char* buf, unsiged int size)

析构
    关闭文件或者释放堆内存
*/




#endif // !FILEC_H_NISODAISUKI

