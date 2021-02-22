ARCH=x86
KERNEL=arch/$(ARCH)/kernel/boot.o kernel/kernel.o
DRIVERS=arch/$(ARCH)/kernel/drivers/vga/vga.o
LIBC=libc/string/strlen.o libc/stdio/printf.o libc/stdlib/Itoa.o
SOURCES=$(KERNEL) $(DRIVERS) $(LIBC)

CC=x86_64-linux-gnu-gcc-10
LD=x86_64-linux-gnu-gcc-10
AS=nasm
CFLAGS=-ffreestanding -O2 -Wall -Wextra -std=gnu99 -m32 -Ilibc -Iarch/$(ARCH)/kernel/drivers -Iarch/$(ARCH)/kernel/headers
LDFLAGS=-Tlinker.ld -nostdlib -lgcc -m32
ASFLAGS=-felf32

all: os.iso

os.iso: kernel
	cp kernel/kernel iso/boot/kernel
	grub-mkrescue -o os.iso iso

clean:
	-rm -f kernel/*.o kernel/kernel libc/*/*.o iso/boot/kernel os.iso

kernel: $(SOURCES)
	$(LD) $(LDFLAGS) -o kernel/kernel $(SOURCES)

.s.o:
	$(AS) $(ASFLAGS) $<

run: os.iso
	echo 'c' | bochs -f bochsrc.txt
