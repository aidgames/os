all: clean init os.bin

boot.o: src/boot.asm
	nasm -f elf32 src/boot.asm -o build/boot.o

kernel.o: src/kernel.c
	gcc -m32 -c src/kernel.c -o build/kernel.o

tty.o: src/tty.c
	gcc -m32 -c src/tty.c -o build/tty.o

gdt.o: src/gdt.c
	gcc -m32 -c src/gdt.c -o build/gdt.o

tss.o: src/tss.c
	gcc -m32 -c src/tss.c -o build/tss.o

port.o: src/port.c
	gcc -m32 -c src/port.c -o build/port.o

memset.o: src/memset.c
	gcc -m32 -c src/memset.c -o build/memset.o


os.bin: boot.o kernel.o tty.o port.o tss.o gdt.o memset.o
	ld -m elf_i386 -T src/linker.ld -o build/os.bin build/boot.o build/tty.o build/memset.o build/tss.o build/gdt.o build/port.o build/kernel.o


clean:
	rm build -rf || true

init:
	mkdir build
