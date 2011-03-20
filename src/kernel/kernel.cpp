/*********************************************************
  AlphaOS Kernel - kernel.cpp
  Version 0.1
  Copyright (c) 2011, Robert Schofield and Matthew Carey
**********************************************************/

// #include "include/keyboard.h"
// #include "include/console.h"
// #include "include/memory.h"
#include "includes/Video.h"

int main(void)
{
    Video vid;
    vid.clear();
    vid.write("AlphaOS Kernel\nVersion 0.1\nCopyright (c) 2011, Robert Schofield and Matthew Carey\n\n");
}
