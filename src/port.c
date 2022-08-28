#include <stdint.h>
#include <stdarg.h>

#define PORT_COM1 0x3f8



uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

void outb(uint16_t port, uint8_t val){
    asm volatile("outb %1, %0" : : "dN"(port), "a"(val));
}

int32_t com1_is_transmit_empty() {
	return inb(PORT_COM1 + 5) & 0x20;
}

void com1_write_char(char a) {
	while (com1_is_transmit_empty() == 0);
	outb(PORT_COM1, a);
}




void qemu_print(char *format) {
     int32_t i = 0;
     char *string;
     while (format[i]) {
         com1_write_char(format[i]);
         i++;
     }
 }


void qemu_printf(char *text) {
	qemu_print(text);
}
