#ifndef MOUSE_H

#define MOUSE_H

#include "../cpu/types.h"

#define MOUSE_COMMAND_PORT 0x64
#define MOUSE_DATA_PORT 0x60

void init_mouse();

#endif