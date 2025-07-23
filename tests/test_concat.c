#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ustr.h"

/*
Run in a loop, taking in a string, and another string
separated by a single space

Prints out the concatenated result of the input strings
*/
int main() {
	char input[1024];
	while(fgets(input, sizeof(input), stdin)) {
		size_t l = strlen(input);
		if (l > 0 && input[l - 1] == '\n') {
            		input[l - 1] = '\0';
        	}
		// Parse out input strings space separated
		char str1[256];
		char str2[256];
		sscanf(input, "%255s %255s", str1, str2);

		UStr s1 = new_ustr(str1);
		UStr s2 = new_ustr(str2);

		/*
		printf("s1:\n");
		print_ustr(s1);
		printf("\ns2:\n");
		print_ustr(s2);
		*/

		UStr conc = concat(s1, s2);
		print_ustr(conc);
		printf("\n");
		free_ustr(conc);
		free_ustr(s1);
		free_ustr(s2);
	}
	return 0;
}
