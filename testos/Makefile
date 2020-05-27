
# Automatically expand to a list of existing files that
# match the patterns
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)

HEADERS = $(wildcard kernel/*.h drivers/*.h)

# Create a list of object files to build , simple by replacing
# the ’.c’ extension of filenames in C_SOURCES with ’.o’
OBJ = ${C_SOURCES:.c=.o}

all: os-image

os-image: boot/boot_sect.bin kernel.bin
	cat $^ > os-image

# Link kernel object files into one binary , making sure the
# entry code is right at the start of the binary .
kernel.bin: kernel/kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary


# Assemble the kernel_entry .
%.o: %.asm
	nasm $< -f elf -o $@

# Generic rule for compiling C code to an object file
# For simplicity , we C files depend on all header files .
%.o: %.c ${HEADERS}
	gcc -m32 -ffreestanding -c $< -o $@

%.bin: %.asm
	nasm -i'boot/' $< -f bin -o $@

clean:
	rm -fr *.bin *.dis *.o os-image
	rm -fr kernel/*.o boot/*.bin drivers/*.o


