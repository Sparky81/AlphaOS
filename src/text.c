/* AlphaOS v0.1
 * Copyright (c) 2012, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

/* AlphaOS v1.0
 * text.c - handles text printing functions
 * Copyright (c) 2011, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#include "include/text.h"
#include "include/colors.h"
// The VGA framebuffer starts at 0xB8000.
u16int *video_memory = (u16int *)0xB8000;
// Stores the cursor position.
u8int cursor_x = 0;
u8int cursor_y = 0;
u8int previous_cursor_x = 0;
u8int previous_cursor_y = 0;

// Updates the hardware cursor.
static void move_cursor()
{
    // The screen is 80 characters wide...
    u16int cursorLocation = cursor_y * 80 + cursor_x;
    outportb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    outportb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
    outportb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    outportb(0x3D5, cursorLocation);      // Send the low cursor byte.
}

void set_cursor_point(u8int x, u8int y)
{
  previous_cursor_x = cursor_x;
  previous_cursor_y = cursor_y;
  cursor_x = x;
  cursor_y = y;
}
/* For this function, keep in mind that the screen is 80 wide and 24 long (because of the 
 * banner at the top). */

// Scrolls the text on the screen up by one line.
static void scroll()
{

    // Get a space character with the default colour attributes.
    u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    u16int blank = 0x20 /* space */ | (attributeByte << 8);

    // Row 25 is the end, this means we need to scroll up
    if(cursor_y >= 24)
    {
        // Move the current text chunk that makes up the screen
        // back in the buffer by a line
        int i;
        for (i = 1*80; i < 23*80; i++)
        {
            video_memory[i] = video_memory[i+80];
        }

        // The last line should now be blank. Do this by writing
        // 80 spaces to it.
        for (i = 23*80; i < 24*80; i++)
        {
            video_memory[i] = blank;
        }
        // The cursor should now be on the last line.
        cursor_y = 23;
    }
}


void put_c(char c, u8int backColour, u8int foreColour)
{
    // The attribute byte is made up of two nibbles - the lower being the
    // foreground colour, and the upper the background colour.
    u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
    // The attribute byte is the top 8 bits of the word we have to send to the
    // VGA board.
    u16int attribute = attributeByte << 8;
    u16int *location;

    // Handle a backspace, by moving the cursor back one space
    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }

    // Handle a tab by increasing the cursor's X, but only to a point
    // where it is divisible by 8.
    else if (c == 0x09)
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }

    // Handle carriage return
    else if (c == '\r')
    {
        cursor_x = 0;
    }

    // Handle newline by moving cursor back to left and increasing the row
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    // Handle any other printable character.
    else if(c >= ' ')
    {
        location = video_memory + (cursor_y*80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    // Check if we need to insert a new line because we have reached the end
    // of the screen.
    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
    }

    /* NOTICE: This was commented to allow the print_to_point function to work
     * properly. This needs to be fixed! */
    // scroll();
    
    // Move the hardware cursor.
    move_cursor();

}

// Writes a single character out to the screen.
void put(char c)
{
    // The background colour is black (0), the foreground is white (15).
    u8int backColour = BLACK;
    u8int foreColour = WHITE;

    // The attribute byte is made up of two nibbles - the lower being the 
    // foreground colour, and the upper the background colour.
    u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);
    // The attribute byte is the top 8 bits of the word we have to send to the
    // VGA board.
    u16int attribute = attributeByte << 8;
    u16int *location;

    // Handle a backspace, by moving the cursor back one space
    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }

    // Handle a tab by increasing the cursor's X, but only to a point
    // where it is divisible by 8.
    else if (c == 0x09)
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }

    // Handle carriage return
    else if (c == '\r')
    {
        cursor_x = 0;
    }

    // Handle newline by moving cursor back to left and increasing the row
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    // Handle any other printable character.
    else if(c >= ' ')
    {
        location = video_memory + (cursor_y*80 + cursor_x);
        *location = c | attribute;
        cursor_x++;
    }

    // Check if we need to insert a new line because we have reached the end
    // of the screen.
    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
    }

    // Scroll the screen if needed.
    scroll();
    // Move the hardware cursor.
    move_cursor();

}

// Clears the screen, by copying lots of spaces to the framebuffer.
void clear()
{
    // Make an attribute byte for the default colours
    u8int attributeByte = (0 /*black*/ << 4) | (15 /*white*/ & 0x0F);
    u16int blank = 0x20 /* space */ | (attributeByte << 8);

    int i;
    for (i = 0; i < 80*25; i++)
    {
        video_memory[i] = blank;
    }

    // Move the hardware cursor back to the start.
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

// Outputs a null-terminated ASCII string to the monitor.
void kprint(char *c)
{
    int i = 0;
    while (c[i])
    {
        put(c[i++]);
    }
}

/* Syntax: 
 * ("Text to print", BackgroundColor, ForegroundColor);  */
void kprintc(char *c, u8int bg, u8int fg)
{
    int i = 0;
    while(c[i])
    {
      put_c(c[i++], bg, fg);
    }
}

void print_to_point(char *text, u8int column, u8int line, u8int backColor, u8int foreColor)
{
  set_cursor_point(column-1, line-1);
  kprintc(text, backColor, foreColor);
  set_cursor_point(previous_cursor_x, previous_cursor_y);
  put(0x20); put(0x08);
}

void monitor_write_hex(u32int n)
{
    s32int tmp;

    kprint("0x");

    char noZeroes = 1;

    int i;
    for (i = 28; i > 0; i -= 4)
    {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && noZeroes != 0)
        {
            continue;
        }
    
        if (tmp >= 0xA)
        {
            noZeroes = 0;
            put (tmp-0xA+'a' );
        }
        else
        {
            noZeroes = 0;
            put( tmp+'0' );
        }
    }
  
    tmp = n & 0xF;
    if (tmp >= 0xA)
    {
        put(tmp-0xA+'a');
    }
    else
    {
        put(tmp+'0');
    }

}

void monitor_write_dec(u32int n)
{
    if (n == 0)
    {
        kprint("0");
        return;
    }

    s32int acc = n;
    char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    kprint(c2);
}

/* Added a dummy version of this function to trick the compiler.
 * When compiling without this written here, the compiler gave an 
 * error code stating that __stack_chk_fail was undefined. Even 
 * though this is never called in the actual program, the compiler
 * still thought it was... Not quite sure why this is happening, but
 * having the function below here is a quick workaround. This issue
 * will eventually be fixed.    */
void __stack_chk_fail(void)
{
  return;
}


void kputs(char *c)
{
  kprint(c);
  kprint("\n");
}

void error(char *c)
{
  kprintc(c, BLACK, LIGHT_MAGENTA);
}

#ifndef VA_LIST

#define va_list __builtin_va_list
#define va_start __builtin_va_start
#define va_arg(x,y) __builtin_va_arg(x,y)
#define va_end(x) __builtin_va_end(x)

#endif

void kprintf(char const *fmt, ...)
{
  va_list args;
  va_start(args, *fmt);
  int i;
  int state = 0;
  for(i = 0; fmt[i] != 0; i++)
  {
    char chr = fmt[i];
    if (chr == '%')
    {
         if(state == 1)
         {
           put('%');
           state = 0;
         }
         else
         {
           state++;
         }
    }
    else if(chr == 'd' || chr == 'i')
    {
         if(state == 1)
         {
           u32int arg = (u32int)va_arg(args, int);
           if (arg < 0)
           {
             put('-');
           }
           monitor_write_dec(arg);
           state = 0;
         }
         else
         {
           if (chr == 'd')
           {
             put('d');
           }
           else
           {
             put('i');
           }
         }
    }
    else if(chr == 'c')
    {
         if(state == 1)
         {
           put((char )va_arg(args, int));
           state = 0;
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
           state = 0;
         }
         else
         {
           put('s');
         }
    }
    else if(chr == 'x')
    {
         if(state == 1)
         {
           monitor_write_hex((u32int)va_arg(args, u32int));
           state = 0;
         }
         else
         {
           put('x');
         }
    }
    else if(chr == 'X')
    {
         if(state == 1)
         {
           monitor_write_hex((u32int)va_arg(args, u32int));
           state = 0;
         }
         else
         {
           put('X');
         }
    }
    else if(chr == '?')
    {
         if(state == 1)
         {
           char *temp__ = (char *)va_arg(args, char *);
           if((bool)va_arg(args, bool))
           {
             kprint(temp__);
           }
           else
           {
           }
           state = 0;
         }
         else
         {
           put('?');
         }
    }
    else
    {
        put(chr);
    }
  }
  va_end(args);
}

char *sprintf(char *str, char const *fmt, ...)
{
  char *save = str;
  va_list args;
  va_start(args, *fmt);
  static int state;
  for(; *fmt != 0; *fmt++)
  {
    switch(*fmt)
    {
      case '%':
           if(state == 1)
           {
             *str++ = '%';
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
             while ((*str++ = *tmp++) != 0);
           }
           else
           {
             *str++ = 's';
           }
           break;
      case 'd':
           if(state == 1)
           {
              char *temp;
              itoa(va_arg(args, int), temp, 10);
              while(temp != '\0') *str++ = *temp++;
           }
	   else 
	   {
	     *str++ = 'd';
	   }
           break;
      case 'x':
	if(state == 1)
	  {
            char *temp;
	    itoa(va_arg(args, int), temp, 16);
            while(temp != '\0') *str++ = *temp++;
	  }
        else
	  {
            *str++ = 'x';
	  }
	break;
      case 'c':
	if(state == 1)
	  {
	    *str++ = va_arg(args, int);
	  }
	else
	  {
	    *str++ = 'c';
	  }
	break;
      default:
	*str++ = *fmt;
    }
    kprintf("state: %d", state);
  }
  str = '\0';
  va_end(args);
  return save;
}
