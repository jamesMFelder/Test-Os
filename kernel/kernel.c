#include "stdio.h"
#include "vga.h"
#include "stdlib.h"
#include "string.h"
#include <stdbool.h>

void kernel_main(void)
{
	/* Initialize terminal interface */
	terminal_initialize();

	terminal_setcolor(vga_entry_color(VGA_COLOR_RED, VGA_COLOR_GREEN));
	vprintvga("Hello world from the %s%c\n", "kernel", '!');
	vprintvga("kernel_main is at: %p\n", kernel_main);
	vprintvga("strlen is at: %p\n", strlen);
	vprintvga("vprintvga is at: %p\n", vprintvga);
	vprintvga("Itoa is at: %p\n", Itoa);
	return;
}
