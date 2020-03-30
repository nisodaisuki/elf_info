#include "CFile.h"
#include <string>
CFILE_RV CFILE::open(const char* file_name, OPEN_MODE mode)
{
    string err_info;
    _file_ptr = fopen(file_name, open_mode[mode]);
    if (_file_ptr != nullptr)
    {
        err_info.append("���ļ�[").append(file_name).append("]�ɹ���");
        err_info_list.push_back(err_info);
        return CFILE_RV::SUCCESS;
    }

    err_info.append("���ļ�[").append(file_name).append("]ʧ�ܡ�");
    err_info_list.push_back(err_info);
    return CFILE_RV::OPEN_FILE_FAIL;
}

CFILE_RV CFILE::read(char* buf, long offset, unsigned int size)
{
    char infobuf[256] = { 0 };
    string info;
    if (_file_ptr == nullptr)
    {
        info.append("�ļ�ָ��Ϊ�ա�");
        return CFILE_RV::FILE_PTR_NULL;
    }

    fseek(_file_ptr, offset, SEEK_SET);
    fread(buf, size, 1, _file_ptr);
    
    sprintf(infobuf, "��[0x%X]��ʼ��ȡ��[0x%X]�ֽڡ�", offset, size);
    info.append(infobuf);
    err_info_list.push_back(info);
    return CFILE_RV::SUCCESS;
}

CFILE_RV CFILE::write(const char* content, unsigned int size, long offset)
{
    fseek(_file_ptr, offset, SEEK_SET);
    fwrite(content, size, 1, _file_ptr);
    return CFILE_RV::SUCCESS;
}

long CFILE::get_file_size()
{
    fseek(_file_ptr, 0, SEEK_END);
    return ftell(_file_ptr);
}
