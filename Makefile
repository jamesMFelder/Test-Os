#List of commands and options in variables
OBJECTS := loader.o
LDFLAGS := -T linker.ld -melf_x86_64
AS := nasm
ASFLAGS := -f elf64

#Important targets
#Default target is to make an iso
all: os.iso

#The iso needs the kernel
os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	grub-mkrescue -o os.iso iso

#Build the kernel from the objects
kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@


#Extra targets
#Run the iso
run: os.iso
	echo c | bochs -f bochsrc.txt -q

#Clean up files
clean:
	rm -rf *.o kernel.elf os.iso iso/boot/kernel.elf
