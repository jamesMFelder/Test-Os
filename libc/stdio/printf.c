#include "stdio.h"
#include "string.h"
#include "vga.h"
#include "stdlib.h"
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>

const char hex[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
const char HEX[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
const char dec[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

//like printf but unbuffered directly to screen
int vprintvga(const char *format, ...)
{
	va_list parameters;//The extra parameters
	va_list secondary;//Here when I need to access a parameter twice
	va_start(parameters, format);
	va_copy(secondary, parameters);
	char *where;//Where in the format string we are
	char nums[20];//A string to use for turning %d, %x and %X into strings
	int written=0;//Number of bytes written
	//If we can't even get the memory to allocate a string the size of the format specifier
	for(where=format;*where != '\0';where++){
		//If it isn't a '%', just output it (driver handles newline and compiler handles \)
		if(*where != '%'){
			terminal_putchar(*where);
			written++;
		//If it's %%, output %
		} else if(*(where+1)=='%'){
			terminal_putchar('%');
			where++;//Skip ahead
			written++;
		//If it is a string, output the string
		} else if(*(where+1)=='s'){
			//TODO: add amount output
			terminal_writestring(va_arg(parameters, const char *));
			written+=strlen(va_arg(secondary, const char *));
			where++;
		//If it is a character, output that
		} else if(*(where+1)=='c'){
			terminal_putchar(va_arg(parameters, int));
			va_arg(secondary, int);//I *really* wish I didn't have to do this
			where++;//Skip ahead
			written++;
		//If it is a decimal, output a decimal
		} else if(*(where+1)=='d'){
			nums[0]='\0';//Reset if we've done this before
			Itoa(va_arg(parameters, const int), nums, 10);
			va_arg(secondary, int);//I *really* wish I didn't have to do this
			terminal_writestring(nums);
			written+=strlen(nums);
			where++;
		} else if(*(where+1)=='X'){
			nums[0]='\0';//Reset if we've done this before
			Itoa(va_arg(parameters, const int), nums, 16);
			va_arg(secondary, int);//I *really* wish I didn't have to do this
			terminal_writestring("0x");
			terminal_writestring(nums);
			written+=strlen(nums);
			where++;
		} else if(*(where+1)=='x'){
			nums[0]='\0';//Reset if we've done this before
			Itoa(va_arg(parameters, const int), nums, 16);
			terminal_writestring("0x");
			terminal_writestring(nums);
			written+=strlen(nums);
			where++;
		} else if(*(where+1)=='p'){
			nums[0]='\0';//Reset if we've done this before
			Itoa(va_arg(parameters, const int), nums, 16);
			terminal_writestring("0x");
			terminal_writestring(nums);
			written+=strlen(nums);
			where++;
		//Otherwise, just output a percent and continue to the next character
		} else{
			terminal_putchar('%');
			written++;
		}
	}
	return written;
}
