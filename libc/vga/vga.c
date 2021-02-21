#include "string.h"
#include "vga.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

//Initialize the screen
void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

//Sets the default color
void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

//Put a character at a location with specified color
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

//Scroll the screen one line
void terminal_scroll()
{
	unsigned int row, col;
	for(row=0;row<VGA_HEIGHT-1;row++){
		for(col=0;col<VGA_WIDTH;col++){
			terminal_buffer[row*VGA_WIDTH+col]=terminal_buffer[(row+1)*VGA_WIDTH+col];
		}
	}
	for(col=0;col<VGA_WIDTH;col++){
		terminal_buffer[VGA_WIDTH*VGA_HEIGHT+col]=vga_entry(' ', vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
	}
	return;
}

//Put a character on the terminal (next spot default color)
void terminal_putchar(char c)
{
	if('\n'==c){
		terminal_column=0;
		if(++terminal_row==VGA_HEIGHT){
			terminal_scroll();
		}
		return;
	}
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_scroll();
	}
}

//Write size characters from data to the screen
void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

//Write a null-terminated string to the screen
void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}
