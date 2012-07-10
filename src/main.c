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
#include "include/time.h"
#include "include/multiboot.h"
#define DIE(msg) die(msg, __FILE__, __LINE__)
void show_intro(void);

struct multiboot *mtboot;

void main(struct multiboot *mboot_header, u32int initial_stack) 
{ 
  clear();
  gdt_install();
  idt_install();
  isrs_install();
  irq_install();
  timer_install();
  keyboard_install();
  init_paging();
  init_memory(mtboot);
  __asm__ __volatile__ ("sti");
  timer_wait(15);;
  show_intro();
  print_to_point("Status bar: Will include information about HDD usage, RAM usage, etc.           ", 1, 25, BLUE, WHITE);
  //Time tm = current_time();
  //kprintf("%d:%d:%d\n", tm.hour, tm.min, tm.sec);
  for(;;);
}

void show_intro(void) 
{
  clear();
  kprintc("AlphaOS Kernel - Version 0.1                                                    ", BLUE, WHITE);
  kputs("Copyright (c) 2012, Robert Schofield and Matthew Carey");
  kputs("All rights reserved.");
  kputs("\n\nKeyboard handling has just been added. Type anything to test it out.");
  return;
}
