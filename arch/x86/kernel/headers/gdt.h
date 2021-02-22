#ifndef _KERN_GDT_H
#define _KERN_GDT_H

void create_descriptor(uint32_t base, uint32_t limit, uint16_t flag);
void disable_gdt();

#endif //_KERN_GDT_H
