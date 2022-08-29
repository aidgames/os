bits 32			;директива nasm - 32 bit
section .text
        ;multiboot spec
        align 4
        dd 0x1BADB002            ;магические числа
        dd 0x00                  ;флаги
        dd - (0x1BADB002 + 0x00) ;контрольная сумма. мч+ф+кс должно равняться нулю


global start
extern kernel_main	        ;kmain определена в C-файле

%include 'src/kernel/asm/gdt.asm'
%include 'src/kernel/asm/tss.asm'

start:
  cli 			;блокировка прерываний
  mov esp, stack_space	;установка указателя стека
  ; load gdt
  call kernel_main
  hlt		 	;остановка процессора

section .bss
resb 8192		;8KB на стек
stack_space:
