/* AlphaOS v0.1
 * Copyright (c) 2012, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#include "include/core.h"
#include "include/text.h"
#include "include/irq.h"

int timer_ticks = 0;

void timer_phase(int hz)
{
  int divisor = 1193810 / hz;
  outportb(0x43, 0x36);
  outportb(0x40, divisor & 0xFF);
  outportb(0x40, divisor >> 8);
}

void timer_handler(struct regs *r)
{
  timer_ticks++;
}

void timer_install()
{
  kprintc(":: Installing ", BLACK, LIGHT_RED);
  kprintc("IRQ Handler -> ", BLACK, GREEN);
  kprintc("[ ", BLACK, LIGHT_MAGENTA);
  kprintc("PIT", BLACK, LIGHT_CYAN);
  kprintc(" ]\n", BLACK, LIGHT_MAGENTA);
 
  irq_install_handler(0, timer_handler);
}

void timer_wait(int ticks)
{
    unsigned long eticks;

    eticks = timer_ticks + ticks;
    while(timer_ticks < eticks);
}
