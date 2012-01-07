/* AlphaOS v0.1
 * Copyright (c) 2012, Robert Schofield and Matthew Carey
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
#include "include/paging.h"

void show_intro(void);


int main(void) 
{ 
  clear();
  
  gdt_install();
  idt_install();
  isrs_install();
  irq_install();
  timer_install();
  keyboard_install();
  __asm__ __volatile__ ("sti");
  timer_wait(10);
  init_paging();
  timer_wait(20);
  show_intro();
  //kputs("Hello world!");
  for(;;); //Not sure if we need an infinite loop here. Lets test it out.
  return 1;
}

void show_intro(void) 
{
  clear();
  //kputs("AlphaOS Kernel - Version 1.0");
  kprintc("AlphaOS Kernel - Version 0.1                                                    ", BLUE, WHITE);
  kputs("Copyright (c) 2012, Robert Schofield and Matthew Carey");
  kputs("All rights reserved.");
  kputs("\n\nKeyboard handling has just been added. Type anything to test it out.");
  return;
}
