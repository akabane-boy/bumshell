#include "../include/input.h" /* own header */
#include <ctype.h> /* For size_t */

/* 
 * is_blank_string:	if they are blank, then return 1
 * 			if they not, return 0
 */
int is_blank_string(char *buffer, size_t buff_size)
{
	for (size_t i = 0; i < buff_size; i++) {
		if (!isspace(buffer[i])) {
			return 0;
		}
	}
	return 1;
}
