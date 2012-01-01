/* AlphaOS v1.0
 * main.c - beginning of the kernel
 * Copyright (c) 2011, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#include "include/core.h"
#include "include/text.h"
void show_intro(void);


int main(void) 
{ 
  // init_descriptor_tables(); // Loads the IDT. 
  clear();
  show_intro();
}

void show_intro(void) 
{
  puts("AlphaOS Kernel - Version 1.0");
  puts("Copyright (c) 2011, Robert Schofield and Matthew Carey");
  puts("All rights reserved.");
  puts("\n*** NOTICE ***");
  puts("The Kernel currently does not have working keyboard handling or a console.");
}
