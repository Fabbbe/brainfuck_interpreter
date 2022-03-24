/* Brainfuck Interpreter - (c) Fabian Beskow 2020
 *
 * A small brainfuck interpreter written in C
 *
 * It works with nested loops but has no error checking
 *
 */

#include <stdio.h>
#include <stdlib.h>

const char* load_brainfuck(char* filepath) { // just reads a file to buffer
	char* buffer = 0;
	long length;
	FILE* file_ptr = fopen (filepath, "rb");

	if (!file_ptr) {
		printf("File does not exist!\n");
		exit(1);
	} else {
		fseek(file_ptr, 0, SEEK_END);
		length = ftell(file_ptr)+1; // +1 for adding a null terminator
		fseek(file_ptr, 0, SEEK_SET);
		buffer = malloc(length);
		if (buffer) {
			fread(buffer, 1, length, file_ptr);
		}
		fclose(file_ptr);
		buffer[length] = '\0';
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

	// Memory of the program
	char* program_data = (char*)calloc(5120, sizeof(char));
	char* data_ptr = (char*)program_data;
	char* code_ptr = (char*)code;

	// This theoretically limits the amount of nested loops
	char** loop_ptr_array = (char**)calloc(64, sizeof(char*));
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
				putchar(*data_ptr);
				break; 
			case ',':
				*data_ptr = getchar();
				break; 
			// TODO: add input
			default:
				break;
		}
		++code_ptr;
	}

	free(program_data);
	free(loop_ptr_array);
	return 0;
}
