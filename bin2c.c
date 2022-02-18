//C99
/*
 * 	bin2c
 * 
 * Christian Strauch (flinti) 2021
 *
 * Converts a file into a const char array definition. Output is like:
 * 
 * const char data[] = { 0xF4, 0x83, 0x14, ... };
 *
 * USAGE:
 *
 * bin2c <filename> [[<varname> <columns count>]]
*/


#include <stdio.h>
#include <stdlib.h>

void print_hex(char c);


int main(int argc, char *argv[])
{
	const char *varname = "data";
	const char *filename = "";
	int column_mod = 0;
	if(argc == 1)
	{
		printf("Specify file as first argument\n");
		return 1;
	}
	else
	{
		filename = argv[1];
		if(argc > 2)
			varname = argv[2];
		if(argc > 3)
		{
			column_mod = atoi(argv[3]);
			if(column_mod < 0)
				column_mod = 0;
		}
	}
	FILE *f = fopen(filename, "r");
	if(!f)
	{
		printf("Unable to open file '");
		printf("%s", filename);
		printf("'\n");
		return 1;
	}

	printf("const char ");
	printf("%s", varname);
	printf("[] = {");
	printf(column_mod != 0 ? "\n    " : " ");

	size_t count = 0;
	size_t linecount = 0;
	int c = getc(f);
	if(c != EOF)
	{
		print_hex(c);
		++count;
	}
	while((c = getc(f)) != EOF)
	{
		printf(", ");
		if(column_mod && ! (count % column_mod))
		{
			printf("\n    ");
			++linecount;
		}
		++count;
		print_hex(c);
	}
	printf(linecount > 0 ? "\n" : " ");
	printf("};\n");
	/*printf("};\nsize_t ");
	printf(varname);
	printf("_length = %zu;\n", count);*/
	return 0;
}

void print_hex(char c)
{
	printf("0x\%02hhX", c);
}
