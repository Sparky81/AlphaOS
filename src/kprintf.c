#include "include/core.h"
#include "include/text.h"

#ifndef VA_LIST

#define va_list __builtin_va_list
#define va_start __builtin_va_start
#define va_arg(x,y) __builtin_va_arg(x,y)
#define va_end(x) __builtin_va_end(x)

#endif

void kprintf(char *fmt, ...)
{
  va_list args;
  va_start(args, *fmt);
  int i;
  int state = 0;
  char tmp;
  for(i = 0; fmt[i] != 0; i++)
  {
    char chr = fmt[i];
    if (chr == '%')
    {
         if(state == 1)
         {
           put('%');
           state--;
         }
         else
         {
           state++;
         }
    }
    else if(chr == 'd')
    {
         if(state == 1)
         {
           monitor_write_dec((u32int)va_arg(args, int));
           state--;
         }
         else
         {
           put('i');
         }
    }
    else if(chr == 'c')
    {
         if(state == 1)
         {
           put((char )va_arg(args, int));
           state--;
         }
         else
         {
           put('c');
         }
    }
    else if(chr == 's')
    {
         if(state == 1)
         {
           kprint((char *)va_arg(args, char *));
           state--;
         }
         else
         {
           put('s');
         }
    }
    else
    {
        put(chr);
    }
  }
  va_end(args);
}
