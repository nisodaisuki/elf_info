#include <stdio.h>

#include "CELF.h"

int main()
{
	CELF e;
	char file_name[] = "test.so";
	e.read_elf_file(file_name);
	e.print_elf32_header();
	return 0;
}