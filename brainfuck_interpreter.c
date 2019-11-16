/* Brainfuck Interpreter - (c) Fabian Beskow 2020
 *
 * A small brainfuck interpreter written in C
 *
 */

#include <stdio.h>

const char* code = "++++++++[>++++++++<-]>+."; // Should output "A"

int main (void) {
	char program_data[256]; // this limits brainfuck to 256 cells
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
			case '.':
				printf("%c", *data_ptr);
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
		}
		++code_ptr;
	}

	printf("\n");
	return 0;
}
