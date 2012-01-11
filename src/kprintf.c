#include "include/core.h"
#include "include/text.h"

#ifndef VA_LIST

#define va_list __builtin_va_list
#define va_start __builtin_va_start
#define va_arg(x,y) __builtin_va_arg(x,y)
#define va_end(x) __builtin_va_end(x)

#endif
char num[] = {'0','1','2','3','4','5','6','7','8','9'};

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

void kprintfc(char const *fmt, ...)
{
  va_list args;
  va_start(args, *fmt);
  int state = 0;
  int bg    = BLACK;
  int fg    = WHITE;
  for(; fmt != 0; fmt++)
  {
    switch(fmt)
    {
      case '%':
           if(state == 1)
          {
            put_c('%', bg, fg);
          }
          else
          {
            state++;
          }
          break;
      case 'F':
           if(state == 1)
           {
             fg = va_arg(args, int);
             state--;
           }
           else
           {
             put_c('F', bg, fg);
           }
           break;
      case 'B':
           if(state == 1)
           {
             bg = va_arg(args, int);
             state--;
           }
           else
           {
             put_c('B', bg, fg);
           }
           break;
      default:
           put_c(*fmt, bg, fg);
           break;
    }
  }
  va_end(args);
}

char *sprintf(char *str, char const *fmt, ...)
{
  char *save = str;
  va_list args;
  va_start(args, *fmt);
  int state;
  for(; fmt != 0; fmt++)
  {
    switch(fmt)
    {
      case '%':
           if(state == 1)
           {
             str++ = '%';
             state--;
           }
           else
           {
             state++;
           }
           break;
      case 's':
           if(state == 1)
           {
             char *tmp = va_arg(args, char *);
             for(; tmp != '\0'; tmp++) str++ = tmp;
           }
           else
           {
             str++ = 's';
           }
           break;
      case 'd':
           if(state == 1)
           {
              char *temp;
              itoa(va_arg(args, int), temp, 10);
              while(temp != '\0') str++ = temp++;
           }
	   else 
	   {
	     str++ = 'd';
	   }
           break;
      case 'x':
	if(state == 1)
	  {
            char *temp;
	    itoa(va_arg(args, int), temp, 16);
            while(temp != '\0') str++ = temp++;
	  }
        else
	  {
            str++ = 'x';
	  }
	break;
      case 'c':
	if(state == 1)
	  {
	    str++ = va_arg(args, char);
	  }
	else
	  {
	    str++ = 'c';
	  }
	break;
      default:
	str++ = fmt;
    }
  }
  str = '\0';
  va_end(args);
  return save;
}
