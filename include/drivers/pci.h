#ifndef PCI_H
#define PCI_H

#define PCI_DATA_PORT 0xCFC
#define PCI_COMMAND_PORT 0xCF8

#include "cpu/types.h"

typedef struct pci_dev {
	u32 portBase;
    u32 interrupt;
        
    u16 bus;
    u16 device;
    u16 function;

    u16 vendor_id;
    u16 device_id;
        
    u8 class_id;
    u8 subclass_id;
    u8 interface_id;

    u8 revision;

} pci_dev_t;

u32 pci_dev_read(u16 bus, u16 device, u16 function, u32 registeroffset);
void pci_dev_write(u16 bus, u16 device, u16 function, u32 registeroffset, u32 value);
int pci_dev_has_func(u16 bus, u16 device);
void pci_get_drivers();

pci_dev_t pci_get_dev_desc(u16 bus, u16 device, u16 function);


#endif