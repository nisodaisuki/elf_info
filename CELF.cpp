#include "CELF.h"

void print_elf_header_ident(elf32_header* p_elf32_header)
{
	printf("ELF Header\r\n");

	char buf[8] = { 0 };
	memcpy(buf, p_elf32_header, 4);
	printf("    Magic:%s\r\n", buf);

	//ei_class
	if (p_elf32_header->e_ident[4] == 0x01)
	{
		//elf class 32
		printf("    ELF CLASS:32位程序\r\n");
	}
	else if (p_elf32_header->e_ident[4] == 0x02)
	{
		//elf class 64
		printf("    ELF CLASS:64位程序\r\n");
	}
	else
	{
		printf("    ELF CLASS:未知\r\n");
	}

	//ei_data
	if (p_elf32_header->e_ident[5] == 0x01)
	{
		//elf data lsb
		printf("    ELF Data:小尾\r\n");
	}
	else if (p_elf32_header->e_ident[5] == 0x02)
	{
		//elf data msb
		printf("    ELF Data:大尾\r\n");
	}
	else
	{
		printf("    ELF Data:%x[error]\r\n", p_elf32_header->e_ident[5]);
	}

	//ei_version
	if (p_elf32_header->e_ident[6] == 0x01)
	{
		printf("    ELF 版本:01(EV_CURRENT)\r\n");
	}
	else
	{
		printf("    ELF 版本:%02x[error]\r\n");
	}

	//os/abi
	printf("    OS/ABI:%02x\r\n", p_elf32_header->e_ident[7]);
	//obi version
	printf("    ABI Version:%02x\r\n", p_elf32_header->e_ident[8]);

	//ei pad 填充
	printf("    EI_PAD:");
	for (int i = 0; i < 6; i++)
	{
		printf("%02x ", p_elf32_header->e_ident[9 + i]);
	}

	//
	printf("\r\n    _elf32_header[e_ident]:%02x\r\n", p_elf32_header->e_ident[EI_NIDENT - 1]);
}

void print_elf_header_type(elf32_header* p_elf32_header)
{
	switch (p_elf32_header->e_type)
	{
	case 0x00:
		//EI_NONE 未知文件类型格式
	{
		printf("文件类型：未知\r\n");
		break;
	}
	case 0x01:
		//EI_REL 可重定位文件
	{
		printf("文件类型：可重定位文件\r\n");
		break;
	}
	case 0x02:
		//EI_EXEC 可执行文件格式
	{
		printf("文件类型：可执行文件\r\n");
		break;
	}
	case 0x03:
		//EI_DYN 共享目标文件格式
	{
		printf("文件类型：共享目标文件(SO)\r\n");
		break;
	}
	default:
	{
		printf("文件类型：[error]\r\n");
		break;
	}
	}
}

void print_elf_header_machine(elf32_header* p_elf32_header)
{
	switch (p_elf32_header->e_machine)
	{
	case 0x03:
	{
		// EM_386
		printf("文件目标CPU架构：x86\r\n");
		break;
	}
	case 0x28:
	{
		// EM_ARM
		printf("文件目标CPU架构：ARM\r\n");
		break;
	}
	default:
		printf("文件目标CPU架构：%02x\r\n", p_elf32_header->e_machine);
		break;
	}
}
