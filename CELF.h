#ifndef BE3B4CD62AE345D9BCEB84EC5A658A0B	
#define BE3B4CD62AE345D9BCEB84EC5A658A0B

#include <stdio.h>
#include "file/CFile.h"

typedef signed int		int32_t;
typedef unsigned int	uint32_t;
typedef unsigned short	uint16_t;

typedef uint32_t Elf32_Addr;	//Program address
typedef uint32_t Elf32_Off;		//File Offset
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Word;
typedef int32_t	 Elf32_Sword;

enum class RV
{
	SUCCESS = 0,
	SUBMIT_ERROR,
	OPEN_FILE_FAIL
};

#define EI_NIDENT 16
struct elf32_header
{
	unsigned char e_ident[EI_NIDENT];//0-3幻数 4文件类（32/64）5大小端 6文件版本 7os/abi 8abi版本 9-14填充数据(0) 15仍然0
	Elf32_Half	e_type;		//elf 文件类型 可执行文件/动态链接库等
	Elf32_Half e_machine;	//文件目标系统架构 arm/x86等
	Elf32_Word e_version;
	Elf32_Addr e_entry;
	Elf32_Off e_phoff;
	Elf32_Off e_shoff;
	Elf32_Word e_flags;
	Elf32_Half e_ehsize;
	Elf32_Half e_phentsize;
	Elf32_Half e_phnum;
	Elf32_Half e_shentsize;
	Elf32_Half e_shnum;
	Elf32_Half e_shstrndx;
};




void print_elf_header_ident(elf32_header* p_elf32_header);
void print_elf_header_type(elf32_header* p_elf32_header);
void print_elf_header_machine(elf32_header* p_elf32_header);
////////////////////////////////////////////

class CELF
{
	// 保存内存中elf文件的地址
	void* elf_file_ptr = nullptr;
	// elf文件头的指针
	elf32_header _elf32_header;


public:
	CFILE _elf_file;
	RV read_elf_file(char* elf_file_name) {
		CFILE_RV rst = _elf_file.open(elf_file_name, RXXB);
		_elf_file.print_err();

		if (rst != CFILE_RV::SUCCESS)
		{
			return RV::SUBMIT_ERROR;

		}
		
		return RV::SUCCESS;
	}

	void print_elf32_header()
	{		
		int file_offset = 0;

		
		_elf_file.read((char*)&_elf32_header, 0, sizeof(elf32_header));
		_elf_file.print_err();
		print_elf_header_ident(&_elf32_header);
		//e_type
		print_elf_header_type(&_elf32_header);
		//e_machine
		print_elf_header_machine(&_elf32_header);
		//e_version
		printf("目标文件版本：%02x\r\n", _elf32_header.e_version);
		//e_entry
		printf("程序入口点:%p\r\n", _elf32_header.e_entry);
		//e_phoff
		printf("Program Header Table偏移量：%p\r\n", _elf32_header.e_phoff);
		//e_shoff
		printf("Section Header Table偏移量：%p\r\n", _elf32_header.e_shoff);
	}
};



#endif
			




