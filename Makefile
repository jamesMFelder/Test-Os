SOURCES=boot.o kernel.o

CC=x86_64-linux-gnu-gcc-10
LD=x86_64-linux-gnu-gcc-10
AS=nasm
CFLAGS=-ffreestanding -O2 -Wall -Wextra -std=gnu99 -m32
LDFLAGS=-Tlinker.ld -nostdlib -lgcc -m32
ASFLAGS=-felf32

all: os.iso

os.iso: kernel
	cp kernel iso/boot/kernel
	grub-mkrescue -o os.iso iso

clean:
	-rm -f *.o kernel iso/boot/kernel os.iso

kernel: $(SOURCES)
	$(LD) $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	$(AS) $(ASFLAGS) $<

run: os.iso
	echo 'c' | bochs -f bochsrc.txt
