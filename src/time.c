/*
   This code was inspired by that of which can be found at http://code.google.com/p/microsea/source/browse/trunk_old/kernel/time.c
   I attemped to read the CMOS technical writing but was unable to decipher it, this got me moving
*/

#include "include/core.h"
#include "include/time.h"
#define b2b(bb) ((((bb) & 15) + ((bb) >> 6) * 10))

#ifndef TIME
#define TIME
typedef struct time_ {
  unsigned int sec;
  unsigned int min;
  unsigned int hour;
  unsigned int day;
  unsigned int month;
  unsigned int year;
} Time;
#endif

unsigned char readCMOS(unsigned char addr)
{

  outportb(0x70, addr);
  __asm__ __volatile__("jmp 1f; 1: jmp 1f; 1:"); //So this code is from microsea, and it seems stupid
   addr = inportb(0x71);                          //however its much more readable and useable than the
  __asm__ __volatile__("jmp 1f; 1: jmp 1f; 1:"); //OSDev example
}

void writeCMOS(unsigned char addr, unsigned int val)
{
  outportb(0x70, addr);
  __asm__ __volatile__("jmp 1f; 1: jmp 1f;1:");
  outportb(0x71, val);
  __asm__ __volatile__("jmp 1f; 1: jmp 1f;1:");
}

Time current_time()
{
  __asm__("cli");
  Time *t;
  t->sec   = (int)b2b(readCMOS(0x0));
  t->min   = (int)b2b(readCMOS(0x2));
  t->hour  = (int)b2b(readCMOS(0x4));
  t->day   = (int)b2b(readCMOS(0x7));
  t->month = (int)b2b(readCMOS(0x8));
  t->year  = (int)b2b(readCMOS(0x9));
  __asm__("sti");
  return *t;
}
