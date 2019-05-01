
# $@: target file
# $^: all the targets's dependency file
# $<: the first dependency file
all : os.img

run : all
	bochs

# automatically expand to a list of existing source files
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)

# create a list of object files, replacing .c to .o
OBJS = $(C_SOURCES:.c=.o)

kernel.bin : kernel/kernel_entry.o ${OBJS}
	ld -melf_i386 -Ttext 0x1000 $^ --oformat binary -o $@

# generic rule for building .c to .o
%.o : %.c
	gcc -m32 -fno-pie -ffreestanding -c $^ -o $@

# assemble kernel_entry
%.o : %.asm
	nasm $^ -f elf -o $@

# assemble boot_sector
%.bin : %.asm
	nasm $^ -f bin -I boot/ -o $@

os.img : boot/boot_sector.bin kernel.bin
	cat $^ > $@

kernel.dis : kernel.bin
	ndisasm -b 32 $^ > $@

clean:
	rm -f *.bin *.o *.img *.dis 
	rm -f kernel/*.o boot/*.bin drivers/*.o

