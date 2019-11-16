/* Brainfuck Interpreter - (c) Fabian Beskow 2020
 *
 * A small brainfuck interpreter written in C
 *
 * It works with nested loops but has no error checking
 *
 */

#include <stdio.h>
#include <stdlib.h>

const char* load_brainfuck(char* filepath) {
	char* buffer = 0;
	long length;
	FILE* file_ptr = fopen (filepath, "rb");

	if (!file_ptr) {
		printf("File does not exist!\n");
		exit(1);
	} else {
		fseek(file_ptr, 0, SEEK_END);
		length = ftell(file_ptr);
		fseek(file_ptr, 0, SEEK_SET);
		buffer = malloc(length);
		if (buffer) {
			fread(buffer, 1, length, file_ptr);
		}
		fclose(file_ptr);
	}
	return (const char*)buffer;
}

int main (unsigned int argc, char** argv) {
	
	// get filepath
	char* filepath;
	if (argc > 1) {
		filepath = argv[1];
	} else {
		printf("No file specified\n");
		exit(1);
	}

	const char* code = load_brainfuck(filepath);

	char program_data[256]; // this limits brainfuck to 256 cells :-/
	char* data_ptr = (char*)program_data;
	char* code_ptr = (char*)code;

	char* loop_ptr_array[256];
	char** loop_ptr_ptr = (char**)loop_ptr_array;
	


	while (*code_ptr != 0x00) {
		switch (*code_ptr) {
			case '+':
				++*data_ptr;
				break;
			case '-':
				--*data_ptr;
				break;
			
			case '>':
				++data_ptr;
				break;
			case '<':
				--data_ptr;
				break;

			case '[':
				loop_ptr_array[loop_ptr_ptr - loop_ptr_array] = (char*)(code_ptr);
				++loop_ptr_ptr;
				break;
			case ']':
				if (*data_ptr != 0){
					code_ptr = loop_ptr_array[loop_ptr_ptr - loop_ptr_array - 1];
				} else {
					--loop_ptr_ptr;
				}
				break;

			case '.':
				printf("%c", *data_ptr);
				break; 
			// TODO: add input
			default:
				break;
		}
		++code_ptr;
	}
	return 0;
}
