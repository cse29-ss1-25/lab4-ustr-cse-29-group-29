#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "list.h"

/*
Returns an empty list of initial_capacity
*/
List new_list(int32_t initial_capacity) {
    List list;
    list.size = 0;
    list.capacity = initial_capacity;
    list.data = malloc(initial_capacity * sizeof(struct UStr));
    return list;
}

/*
Initializes an list of length size with elements from array
*/
List new_list_from_array(struct UStr* array, int32_t size) {
    List list = new_list(size);
    for (int32_t i = 0; i < size; i++) {
        list.data[i] = array[i];
    }
    list.size = size;
    return list;
}


/*
Given a list of strings and a separator string, returns a single string 
containing all the strings in list joined by the separator.
*/
UStr join(List* list, UStr separator) {
	int total_len = 0;
	for (int i = 0; i < list->size; i++) {
		total_len+=list->data[i].bytes;
		if (i < list->size-1) {
			total_len+=separator.bytes;
		}
	}
	char* result = malloc (total_len + 1);
	int pos = 0;
	for (int i=0; i < list->size; i++) {
		for (int j = 0; j<list->data[i].bytes;j++) {
			result[pos] = list->data[i].contents[j];
			pos++;
		}
		if (i < list->size -1) {
			for (int j = 0; j < separator.bytes; j++) {
				result[pos++] = separator.contents[j];
			}
		}
	}
	result[pos] = '\0';
	return new_ustr(result);
}

/*
Inserts string s into list at index s, shifting elements to the right.
Expands the list's capacity if necessary (double the capacity, or set to 1 if 0).

Returns 1 on success, 0 if the index is invalid (out of bounds).
*/
int8_t insert(List* list, UStr s, int32_t index) {
    // TODO: implement this

	// bounds
	if(index < 0 || index > list->size){ return 0; }

	// expand
	if(list->size >= list->capacity){
		list->data = realloc(list->data,2*sizeof(UStr)*list->capacity);
		list->capacity *= 2;
	}
	for(int i = list->size; i > index; i -= 1){
		list->data[i] = list->data[i-1];
	}
	list->data[index] = new_ustr(s.contents);
	list->size += 1;
	return 1;
}

/*
Removes the element at the given index and shifts all subsequent elements left.

Returns 1 on success, 0 if the index is invalid (out of bounds).
*/
int8_t listRemoveAt(List* list, int32_t index) {
    // TODO: implement this

}

/*
Splits the given string s into substrings separated by the given delimiter string.

Returns a List of String objects, each containing a segment between delimiters.

If the delimiter is the empty string, return a list containing the original 
string as a single element.

If the input string ends with the delimiter, include an empty string at the 
end of the result.

Note that the delimiter could be of a length of more than 1 character
*/
List split(UStr s, UStr separator) {
    // TODO: implement this

}
