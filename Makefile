all: clean init os.bin

boot.o: src/boot.asm
	nasm -f elf32 src/boot.asm -o build/boot.o

kernel.o: src/kernel.c
	gcc -m32 -c src/kernel.c -o build/kernel.o

terminal.o: src/terminal.c
	gcc -m32 -c src/terminal.c -o build/terminal.o

gdt.o: src/gdt.c
	gcc -m32 -c src/gdt.c -o build/gdt.o

tss.o: src/tss.c
	gcc -m32 -c src/tss.c -o build/tss.o

port.o: src/port.c
	gcc -m32 -c src/port.c -o build/port.o

os.bin: boot.o kernel.o terminal.o port.o tss.o gdt.o
	ld -m elf_i386 -T src/linker.ld -o build/os.bin build/boot.o build/terminal.o build/tss.o build/gdt.o build/port.o build/kernel.o


clean:
	rm build -rf || true

init:
	mkdir build
