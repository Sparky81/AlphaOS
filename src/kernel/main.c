/* 
 * AlphaOS Kernel - Version 1.0 
 * main.c
 * Copyright (c) 2011, Robert Schofield and Matthew Carey
 */

#include "includes/video.h"
#include "cpuid.c"

int main(struct multiboot *mboot_ptr)
{
    clear();
    printf("AlphaOS Kernel\nVersion 1.0\nCopyright (c) 2011, Robert Schofield and Matthew Carey\n\n");
    detect_cpu();
    return 0;
}