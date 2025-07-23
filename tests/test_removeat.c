#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "ustr.h"

/*
Run in a loop, taking in a string, and an index
separated by a single space

Prints out the result of removing the index from the input string
*/
int main() {
	char input[512];
	while(fgets(input, sizeof(input), stdin)) {
		size_t l = strlen(input);
		if (l > 0 && input[l - 1] == '\n') {
            		input[l - 1] = '\0';
        	}
		// Parse out from input the string and the index to remove
		char str[256];
		int trem;
		sscanf(input, "%255s %d", str, &trem);

		UStr s = new_ustr(str);
		UStr r = removeAt(s,trem);
		print_ustr(r);
		printf("\n");
		// check if r and s are same address to free only once
		/*if(&r == &s) { free_ustr(r); }
		else {
			free_ustr(r);
			free_ustr(s);
		}*/
	}
	return 0;
}
