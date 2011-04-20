/* 
 * AlphaOS Kernel - Version 1.0 
 * main.c
 * Copyright (c) 2011, Robert Schofield and Matthew Carey
 */

#include "includes/video.h"
// #include "cpuid.c"

int main(void)
{
    init_descriptor_tables();
    clear();
    printf("Loading Dependencies...\n");
    printf("   Initializing GDT...");

    printf("   Initializing IDT...");

    asm volatile("int $0x3");
    asm volatile("int $0x4");
    asm volatile("sti");

    printf(
      "AlphaOS Kernel\n"
      "Version 1.0\n"
      "Copyright (c) 2011, Robert Schofield and Matthew Carey.\n"
      "All rights reserved.\n\n"
    ); 

    init_timer();
    //clear();
    /*printf(
      "AlphaOS Kernel\n"
      "Version 1.0\n"
      "Copyright (c) 2011, Robert Schofield and Matthew Carey.\n"
      "All rights reserved.\n\n"); */
    // detect_cpu();
    return 0;
}
