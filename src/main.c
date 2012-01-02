/* AlphaOS v1.0
 * main.c - beginning of the kernel
 * Copyright (c) 2011, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#include "include/core.h"
#include "include/text.h"
#include "include/gdt.h"
void show_intro(void);


int main(void) 
{ 
  // init_descriptor_tables(); // Loads the IDT. 
  gdt_install();
  idt_install();
  isrs_install();
  irq_install();
  clear();
  show_intro();
  return 1;
}

void show_intro(void) 
{
  kputs("AlphaOS Kernel - Version 1.0");
  kputs("Copyright (c) 2011, Robert Schofield and Matthew Carey");
  kputs("All rights reserved.");
  kputs("\n*** NOTICE ***");
  kputs("The Kernel currently does not have working keyboard handling or a console.");
  return;
}
