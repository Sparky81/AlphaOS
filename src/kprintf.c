#include "include/core.h"
#include "include/text.h"

#ifndef VA_LIST

#define va_list __builtin_va_list
#define va_start __builtin_va_start
#define va_arg(x,y) __builtin_va_arg(x,y)
#define va_end(x) __builtin_va_end(x)

#endif
char num[] = {'0','1','2','3','4','5','6','7','8','9'};

/* kprintf(char const *fmt, ...);
   kprintf(1) - Prints a string from a format.
  |%s| Prints a string from the args list.
  |%d| Prints an integer
  |%x| Prints a hex
  |%c| Prints a character
  |%f| Prints a floating point number --TO BE IMPLEMENTED--
  |%p| Prints a pointer address  --TO BE IMPLEMENTED--
*/

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

/* kprintfc(char const *fmt, ...);
   kprintfc(1) - Print color formatted strings. %F is foreground, %B sets background. Starts at
   default BLACK|WHITE color scheme.
*/

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

/* sprintf(char *str, char const *fmt, ...)
   sprintf(1) - returns a string version of the formatted
   string. Works the exact same as printf, but outputs to the buffer string instead
   of the screen.
*/

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

/* char *ftostr(float flt, string str, int prec);
   ftostr(1) - Conversion of floating point number to a string.
   The string will be placed in string as well as returning it.
   Prec is the floating point precision. If precision is higher than
   digits after the decimal, they will be filled by '0'. ex. ftostr(19.99, char_str, 5)
   puts "19.99000" into char_str.
*/ 

char *ftostr(float flt, string str, int prec) //Float, precision
{
  char *save = str;
  int dec_plc;
  float flt_temp = flt;
  char *str_temp = str;
  for(;(flt_temp % 1) != 0; dec_plc++) flt_tmp *= 10; //We now know when to place the decimal.
  itoa((int)flt_temp, str_temp, 10); //If flt_temp started as 13.37 it is now in str_temp as "1337"
  static int len = strlen(str_temp);
  for(; len != dec_plc; len--); *str++ = *str_temp++;
  *str++ = '.';
  static bool the_end = false; 
  for(; prec != 0; prec--)
  {
     if(the_end == true)
     {
        *str++ = '0';
     }
     else
     {
        if(*str_temp == '\0')
        {
            the_end = true;
            *str++ = '0';
        }
        else
        {
            *str++ = *str_temp++;
        }
     }
  }
  *str = '\0';
  return save;
}
