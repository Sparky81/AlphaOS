/* AlphaOS v1.0
 * main.c - beginning of the kernel
 * Copyright (c) 2011, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#include "include/core.h"
#include "include/text.h"

int main(void) 
{ 
  // init_descriptor_tables(); // Loads the IDT. 
  clear();
  
  show_intro();
}

int show_intro() 
{
  print("AlphaOS Kernel - Version 1.0\n");
  print("Copyright (c) 2011, Robert Schofield and Matthew Carey\n");
  print("All rights reserved.\n");
  print("\n\n*** NOTICE ***\n");
  print("The Kernel currently does not have working keyboard handling or a console.\n");
}