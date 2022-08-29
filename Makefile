KSRC=src/kernel
LIBC=src/libc
KERNEL_OBJECTS = $(patsubst %.c,%.o,$(wildcard $(KSRC)/*.c))
LIBC_OBJECTS = $(patsubst %.c,%.o,$(wildcard $(LIBC)/*.c))

ALL: src/os.bin

$(KSRC)/boot.o: $(KSRC)/boot.asm
	nasm -f elf32 $(KSRC)/boot.asm -o $(KSRC)/boot.o

%.o: %.c
	gcc -m32 -c $< -I $(LIBC)/include -I $(KSRC)/include -o $@


src/libc.a: $(LIBC_OBJECTS)
	ar rcs src/libc.a $(LIBC_OBJECTS)

src/os.bin: $(KERNEL_OBJECTS) src/libc.a $(KSRC)/boot.o
	ld -m elf_i386 -o src/os.bin -T $(KSRC)/linker.ld $(KSRC)/boot.o $(KERNEL_OBJECTS) src/libc.a

.PHONY: clean
clean:
	rm $(KERNEL_OBJECTS) $(LIBC_OBJECTS) src/os.bin src/libc.a $(KSRC)/boot.o
