#include <stdint.h>
#include <config.h>
#include <flashrom.h>

void config_load(void) {
    extern char configmem[];
   if (*((uint16_t*) configmem) ==  CONFIG_KEY) {
       memcpy(&sysconfig, (configmem + sizeof(CONFIG_KEY)), sizeof(sysconfig));
   }
   else {
       config_save();
   }
}

uint8_t config_save(void) {
    configmem_t mem = { CONFIG_KEY, sysconfig  };
    return (flashrom_erase((uint8_t*) &configmem) && flashrom_write((uint8_t*) &configmem, (char*) &mem, sizeof(mem)));
}
