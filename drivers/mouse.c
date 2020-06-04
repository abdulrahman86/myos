#include "drivers/mouse.h"
#include "drivers/ports.h"
#include "cpu/isr.h"
#include "drivers/screen.h"
#include "kernel/util.h"

int mouse_x;
int mouse_y;
s8 buffer[3];
int offset;
int buttons;




static void mouse_callback(registers_t regs) {

    u8 status = port_byte_in(MOUSE_COMMAND_PORT);

    if (!(status & 0x20))
        return;
    
    buffer[offset] = port_byte_in(MOUSE_DATA_PORT);


    offset = (offset + 1) % 3;

    if (offset == 0) {

        int old_x = mouse_x;
        int old_y = mouse_y;


        mouse_x += buffer[1] / 10;

        mouse_y -= buffer[2] / 10;


        if (mouse_x >= 80) {
            mouse_x = 79;
        }

        if (mouse_x < 0) {
            mouse_x = 0;
        }


        if (mouse_y >= 25) {
            mouse_y = 24;
        }

        if (mouse_y < 0) {
            mouse_y = 0;
        }

        trigger_move_mouse_pointer(old_x, old_y, mouse_x, mouse_y);

        for(u8 i = 0; i < 3; i++)
        {
            char button_index[3];

            int_to_ascii(i, button_index);

            if((buffer[0] & (0x1<<i)) != (buttons & (0x1<<i)))
            {
                if(buttons & (0x1<<i)) {

                    kprint("Mouse up detected for ");
                    kprint(button_index);

                    //handler->OnMouseUp(i+1);
                }
                else {

                    kprint("Mouse down detected for ");
                    kprint(button_index);
                }
            }
        }
        
        buttons = buffer[0];

    }

    //kprint("Mouse Interrupt!");
    
}


void trigger_move_mouse_pointer(int old_x, int old_y, int new_x, int new_y) {

    u16* VideoMemory = (u16*)0xb8000;

    VideoMemory[80*old_y+old_x] = (VideoMemory[80*old_y+old_x] & 0x0F00) << 4
                        | (VideoMemory[80*old_y+old_x] & 0xF000) >> 4
                        | (VideoMemory[80*old_y+old_x] & 0x00FF);



    VideoMemory[80*new_y+new_x] = (VideoMemory[80*new_y+new_x] & 0x0F00) << 4
                        | (VideoMemory[80*new_y+new_x] & 0xF000) >> 4
                        | (VideoMemory[80*new_y+new_x] & 0x00FF);
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
    offset = 0;
    buttons = 0;

    //trigger_move_mouse_pointer(mouse_x, mouse_y, mouse_x, mouse_y);
}