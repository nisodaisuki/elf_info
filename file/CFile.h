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
    �ļ���ģʽ��
    R�����ж�Ȩ��
    W������дȨ��
    C�����д������ļ�Ȩ��
    B�������ƴ�
    T���ı�ģʽ��
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
    // �ļ�ָ��
    FILE* _file_ptr = nullptr;
    
public:
    //  *****************************
    //  ���캯��
    //  file_name: �ļ���
    //  mode���򿪷�ʽ��ö���е�һ��
    //  expected_file_size:�����ڴ����ļ��ı��ʡ�
    //   �磬Ԥ���������ļ��Ĵ�С��ԭʼ�ļ���1.5�����Ϳ���д2��Ĭ��ֵΪ1.
    //  *****************************
    CFILE_RV open(const char* file_name, OPEN_MODE mode);

    //  *****************************
    //  ���ļ�
    //  buf: Ŀ�껺����
    //  size����ȡ�ļ��Ĵ�С
    //  offset:    ���ļ��е�ƫ��
    //  ���ز������
    //  *****************************
    CFILE_RV read(char* buf, long offset, unsigned int size);

    //  **********************************
    //  д�ļ�
    //  content: Ҫд�������
    //  size:       д��Ĵ�С
    //  offset:    ���ļ��е�ƫ��
    //  **********************************
    CFILE_RV write(const char* content, unsigned int size, long offset);

    //  **********************************
    //  ��ȡ�ļ���С
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
�ļ�����


��ģʽ
    ���д�������
    �����д������ԣ�����
    Ĭ�����û������ļ��ͱ���

��Ա��
����1��
    �ļ�ָ��
    �ļ�ƫ��
    �ļ���С

����2��
�ļ�ӳ���ڴ�
    �ڴ�ѵ�ַָ��
    �ļ�ƫ��
    �ļ���С

���캯��������ļ�ָ�룬��Ϊ�գ��洢�ļ�ָ�룬���򱨴�
    myfile(enum mode, char);

��
    myread(char* buf, unsiged int size)
    //  �����ļ�ָ��
    myreread(char* buf, unsiged int size)
д
    mywrite(char* buf, unsiged int size)
    //  �����ļ�ָ��
    myrewrite(char* buf, unsiged int size)

����
    �ر��ļ������ͷŶ��ڴ�
*/




#endif // !FILEC_H_NISODAISUKI

