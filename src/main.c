/* AlphaOS v1.0
 * main.c - beginning of the kernel
 * Copyright (c) 2011, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#include "include/core.h"
#include "include/text.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/isrs.h"
#include "include/irq.h"
#include "include/pit.h"
#include "include/keyboard.h"

void show_intro(void);


int main(void) 
{ 
  clear();
  show_intro();
  gdt_install();
  idt_install();
  isrs_install();
  irq_install();
  timer_install();
  keyboard_install();
  __asm__ __volatile__ ("sti");
  timer_wait(10);
  kputs("Hello world!");
  for(;;); //Not sure if we need an infinite loop here. Lets test it out.
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
