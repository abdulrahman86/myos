#include "mouse.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../kernel/util.h"

int mouse_x;
int mouse_y;
u8 buffer[3];
int offset;

int sensitivity;
int skip;


static void mouse_callback(registers_t regs) {
    
    buffer[offset] = port_byte_in(MOUSE_DATA_PORT);

    char x_offset[5];
    char y_offset[5];

    char mouse_x_offset[5];
    char mouse_y_offset[5];


    offset = (offset + 1) % 3;

    if (offset == 0) {

        int_to_ascii(buffer[1], x_offset);
        int_to_ascii(buffer[2], y_offset);

        skip = (skip + 1) % sensitivity;

        //if (skip == 0) {

            int old_x = mouse_x;
            int old_y = mouse_y;

            if (buffer[2] > 0) {

                mouse_x = mouse_x + sensitivity;
            }
            else {

                mouse_x = mouse_x - sensitivity;
            }

            if (buffer[1] > 0) {

                mouse_y = mouse_y - sensitivity;
            }
            else {
                mouse_y = mouse_y + sensitivity;
            }


            if (mouse_x > 79) {
                mouse_x = 79;
            }

            if (mouse_x < 0) {
                mouse_x = 0;
            }


            if (mouse_y > 24) {
                mouse_y = 24;
            }

            if (mouse_y < 0) {
                mouse_y = 0;
            }

            trigger_move_mouse_pointer(old_x, old_y, mouse_x, mouse_y);

        //}



        // if (mouse_x > 79) 
        //     mouse_x = 79;
        // else if (mouse_x < 0)
        //     mouse_x = 0;

        // if (mouse_y > 24) 
        //     mouse_y = 24;
        // else if (mouse_y < 0)
        //     mouse_y = 0;


        // kprint("Xoffset: ");
        // kprint(x_offset);
        // kprint(", ");

        // kprint("Yoffset: ");
        // kprint(y_offset);
        // kprint("\n");


        // int_to_ascii(mouse_x, mouse_x_offset);
        // int_to_ascii(mouse_y, mouse_y_offset);

        // kprint("Mouse Xoffset: ");
        // kprint(mouse_x_offset);
        // kprint(", ");

        // kprint("Mouse Yoffset: ");
        // kprint(mouse_y_offset);
        // kprint("\n");

        //kprint("Mouse Interrupt!");


    

    }

    //kprint("Mouse Interrupt!");
    
}


void trigger_move_mouse_pointer(int old_x, int old_y, int new_x, int new_y) {

    change_color(WHITE_ON_BLACK, old_x, old_y);

    change_color(BLACK_ON_WHITE, new_x, new_y);
}

void init_mouse() {

    port_byte_out(MOUSE_COMMAND_PORT, 0xA8);
    port_byte_out(MOUSE_COMMAND_PORT, 0x20);

    u8 status = port_byte_in(MOUSE_DATA_PORT) | 2;

    port_byte_out(MOUSE_COMMAND_PORT, 0x60);
    port_byte_out(MOUSE_DATA_PORT, status);
    port_byte_out(MOUSE_COMMAND_PORT, 0xD4);
    port_byte_out(MOUSE_DATA_PORT, 0xF4);
    port_byte_in(MOUSE_DATA_PORT);

   	register_interrupt_handler(IRQ12, mouse_callback); 

    mouse_x = 40;
    mouse_y = 12;
    skip = 0;
    sensitivity = 5;

    offset = 0;

    trigger_move_mouse_pointer(mouse_x, mouse_y, mouse_x, mouse_y);
}