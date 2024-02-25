#include <main.h>
#include <string.h>

extern uint32_t _MSP;  // Defined in link.ld

void Reset_Handler(void) {

    extern uint8_t __data_start__, __data_end__, __data_FLASH_end__, __bss_start__, __bss_end__;
    /* Copy the .data from flash to RAM */
    memcpy(&__data_start__, &__data_FLASH_end__, (uint32_t)(&__data_end__ - &__data_start__));
    /* Fill the .bss section in RAM with all Zeros */
    memset(&__bss_start__, 0, (uint32_t)(&__bss_end__ - &__bss_start__));

    main();
    for(;;);
}

__attribute__((section(".isr_vector"), used)) uint32_t vector_table [] = {
    (uint32_t)&_MSP,
    (uint32_t)&Reset_Handler,
};

