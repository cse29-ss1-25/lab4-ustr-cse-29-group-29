#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char* contents) {
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char* contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy
	};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s) {
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive) 
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end) {
	// TODO: implement this
	// bounds check on indices
	int ulen = len(s);
	if((start < 0) || (start >= ulen) || (start >= end) || (end > ulen)){
		return new_ustr("");
	}
	else {
		// work with codepoint indices as input,
		// operate on byte indices
		// above was in cpi, not bi
		int bi_start = bi_of_cpi(s.contents,start);
		int bi_end = bi_of_cpi(s.contents,end);
		int diff = bi_end - bi_start;
		char* newc = malloc(diff+1);
		int i = bi_start;
		while(i < bi_end){
			// check length of codepoint and copy accordingly
			newc[i-bi_start] = s.contents[i];
			i += 1;
		}
		newc[bi_end] = 0;
		UStr res = new_ustr(newc);
		return res;
	}
}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	// TODO: implement this
	int rlen = s1.bytes + s2.bytes;
	char* new = malloc(rlen + 1);
	int index = 0;
	while(s1.contents[index]!=0){
		new[index]= s1.contents[index];
		index++;
	}
	int index2 = 0;
	while(s2.contents[index2]!= 0){
		new[index + index2] = s2.contents[index2];
		index2 += 1;
	}
	// could run strncpy to copy from each to dest, must walk pointer in b/w
	//strncpy(new,
	new[index + index2] = 0;
	UStr res = new_ustr(new);
	return res;
}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
        if (index < 0 || index >= s.codepoints) {return s;}
	int bytepos = bi_of_cpi(s.contents,index);
        if (bytepos < 0 || bytepos >= s.bytes) {return s;}

	int rmbytelen = utf8_codepoint_size(s.contents[bytepos]);
	int len = strlen(s.contents);
	char* result = malloc(len - rmbytelen + 1);

	strncpy(result, s.contents, bytepos);
	strcpy(result+bytepos,s.contents+bytepos+rmbytelen);
	UStr res = new_ustr(result);
	return res;
}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this
	int lengthOfReversedString = s.bytes;
	char* contentsReversed = malloc(lengthOfReversedString + 1);
	int index =0;
	while(s.contents[index]!='\0'){
		contentsReversed[index] =s.contents[s.bytes- index];
		index++;
	}
	UStr reversedStr = new_ustr(contentsReversed);
	return reversedStr;

}


void print_ustr(UStr s) {
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s) {
	if (s.contents != NULL) {
		free(s.contents);
		s.contents = NULL;
	}
}

