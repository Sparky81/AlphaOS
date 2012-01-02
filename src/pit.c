#include "include/core.h"

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
  if (timer_ticks % 18 == 0)
  {
    kputs("One second has passed");
  }
}

void timer_install()
{
  irq_install_handler(0, timer_handler);
}
