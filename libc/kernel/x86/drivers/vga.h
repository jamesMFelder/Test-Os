#ifndef KERN_VGA_H
#define KERN_VGA_H
#include <stddef.h>
#include <stdint.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

//Takes a foreground and background color (from the vga_color enum) and returns a uint8_t with them both embedded
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

//Takes a character and color (from vga_entry_color) and returns a uint16_t with them both embedded
static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}


//Initialize the screen
void terminal_initialize(void);

//Sets the default color
void terminal_setcolor(uint8_t color);

//Put a character at a location with specified color
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

//Scroll the screen one line
void terminal_scroll();

//Put a character on the terminal (next spot default color)
void terminal_putchar(char c);

//Write size characters from data to the screen
void terminal_write(const char* data, size_t size);

//Write a null-terminated string to the screen
void terminal_writestring(const char* data);

#endif //KERN_VGA_H
