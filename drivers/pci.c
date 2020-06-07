#include "drivers/pci.h"

u32 pci_dev_read(u16 bus, u16 device, u16 function, u32 registeroffset) {


	u32 id =
		0x1 << 31
		| ((bus & 0xFF) << 16)
        | ((device & 0x1F) << 11)
        | ((function & 0x07) << 8)
        | (registeroffset & 0xFC);

    port_dword_out(PCI_COMMAND_PORT, id);
    u32 result = port_dword_in (PCI_DATA_PORT);
    return result >> (8* (registeroffset % 4));
}

void pci_dev_write(u16 bus, u16 device, u16 function, u32 registeroffset, u32 value) {

	u32 id = 0x1 << 31
        			| ((bus & 0xFF) << 16)
        			| ((device & 0x1F) << 11)
        			| ((function & 0x07) << 8)
        			| (registeroffset & 0xFC);

    port_dword_out(PCI_COMMAND_PORT, id);
    port_dword_out(PCI_DATA_PORT, value);
}

int pci_dev_has_func(u16 bus, u16 device) {

	 return pci_dev_read(bus, device, 0, 0x0E) & (1<<7);
}

void pci_get_drivers() {

	kprint("Getting PCI Drivers!");

	for(u16 bus = 0; bus < 8; bus++)
    {
        for(u16 device = 0; device < 32; device++)
        {
            //u16 numFunctions = pci_dev_has_func(bus, device) ? 8 : 1;

            for(u16 function = 0; function < 8; function++)
            {
            	kprint("PCI Device Detected!");
            	
            	//pci_dev_t dev = pci_get_dev_desc(bus, device, function);
                
             // 	if(dev.vendor_id == 0x0000 || dev.vendor_id == 0xFFFF) {

             // 		kprint("PCI No Device!");
             //        continue;
             //    }
             //   	else {

             //   		kprint("PCI Device Detected!");
             //   	}
            }
        }
    }
}

// pci_dev_t pci_get_dev_desc(u16 bus, u16 device, u16 function) {
	
// 	pci_dev_t result;
    
//     // result.bus = bus;
//     // result.device = device;
//     // result.function = function;
    
//     // result.vendor_id = pci_dev_read(bus, device, function, 0x00);
//     // result.device_id = pci_dev_read(bus, device, function, 0x02);

//     // result.class_id = pci_dev_read(bus, device, function, 0x0b);
//     // result.subclass_id = pci_dev_read(bus, device, function, 0x0a);
//     // result.interface_id = pci_dev_read(bus, device, function, 0x09);

//     // result.revision = pci_dev_read(bus, device, function, 0x08);
//     // result.interrupt = pci_dev_read(bus, device, function, 0x3c);
    
// 	return result;
// }