#include "terminal.h"
#include "port.h"

#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_DATA_PORT 0x60

char keycode;
unsigned char status;

void kernel_main(void)
{
    terminal_initialize();
    terminal_writestring("Hello, kernel!\n");
    outb(0x20, 0x20);
    status = inb(KEYBOARD_STATUS_PORT);
    qemu_printf((int*)status);
    if (status & 0x01) {
        for(;;){
            keycode = inb(KEYBOARD_DATA_PORT);
            terminal_putchar((char *) keycode);
	}
    }

}
