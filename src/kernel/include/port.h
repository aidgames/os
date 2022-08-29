#ifndef PORT_H_
#define PORT_H_

#include <stdint.h>

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t val);
void io_wait();

int32_t com1_is_transmit_empty();
void com1_write_char(char a);
void qemu_print(char *format);
void qemu_printf(char *text);

#endif
