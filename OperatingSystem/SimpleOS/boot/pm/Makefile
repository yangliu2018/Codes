test.bin : test_switch.asm
	nasm test_switch.asm -o test.bin

run : test.bin
	bochs

clean:
	rm *.bin
