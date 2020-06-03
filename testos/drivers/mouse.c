#include "mouse.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"

static void mouse_callback(registers_t regs) {
    

    u8 scancode = port_byte_in(0x60);

    kprint("Mouse Interrupt!");
    
}

void init_mouse() {


	       //  commandport.Write(0xA8);
        // commandport.Write(0x20); // command 0x60 = read controller command byte
        // uint8_t status = dataport.Read() | 2;
        // commandport.Write(0x60); // command 0x60 = set controller command byte
        // dataport.Write(status);

        // commandport.Write(0xD4);
        // dataport.Write(0xF4);
        // dataport.Read();    
   
    port_byte_out(MOUSE_COMMAND_PORT, 0xA8);
    port_byte_out(MOUSE_COMMAND_PORT, 0x20);

    u8 status = port_byte_in(MOUSE_DATA_PORT) | 2;

    port_byte_out(MOUSE_COMMAND_PORT, 0x60);
    port_byte_out(MOUSE_DATA_PORT, status);
    port_byte_out(MOUSE_COMMAND_PORT, 0xD4);
    port_byte_out(MOUSE_DATA_PORT, 0xF4);
    port_byte_in(MOUSE_DATA_PORT);

   	register_interrupt_handler(IRQ12, mouse_callback); 
}