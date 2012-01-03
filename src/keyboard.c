/* AlphaOS v0.1
 * Copyright (c) 2012, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#include "include/core.h"
#include "include/irq.h"
#include "include/text.h"
#include "include/colors.h"

#define LEFT_SHIFT 1
#define RIGHT_SHIFT 2
#define CAPS_LOCK 3

int state = 0;

unsigned char kbdus[128] = \
{\
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */\
  '9', '0', '-', '=', '\b',	/* Backspace */\
  '\t',			/* Tab */\
  'q', 'w', 'e', 'r',	/* 19 */\
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */\
    0,			/* 29   - Control */\
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */\
 '\'', '`',   LEFT_SHIFT,		/* Left shift */\
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */\
  'm', ',', '.', '/',   RIGHT_SHIFT,		/* Right shift */\
  '*',\
    0,	/* Alt */\
  ' ',	/* Space bar */\
    CAPS_LOCK,	/* Caps lock */\
    0,	/* 59 - F1 key ... > */\
    0,   0,   0,   0,   0,   0,   0,   0,\
    0,	/* < ... F10 */\
    0,	/* 69 - Num lock*/\
    0,	/* Scroll Lock */\
    0,	/* Home key */\
    0,	/* Up Arrow */\
    0,	/* Page Up */\
  '-',\
    0,	/* Left Arrow */\
    0,\
    0,	/* Right Arrow */\
  '+',\
    0,	/* 79 - End key*/\
    0,	/* Down Arrow */\
    0,	/* Page Down */\
    0,	/* Insert Key */\
    0,	/* Delete Key */\
    0,   0,   0,\
    0,	/* F11 Key */\
    0,	/* F12 Key */\
    0,	/* All other keys are undefined */\
};

unsigned char uc_kb[128] = \
{\
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',     /* 9 */\
  '9', '0', '-', '=', '\b',     /* Backspace */\
  '\t',                 /* Tab */\
  'Q', 'W', 'E', 'R',   /* 19 */\
  'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n',         /* Enter key */\
    0,                  /* 29   - Control */\
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';',     /* 39 */\
 '\'', '`',   LEFT_SHIFT,               /* Left shift */\
 '\\', 'Z', 'X', 'C', 'V', 'B', 'N',                    /* 49 */\
  'M', ',', '.', '/',   RIGHT_SHIFT,            /* Right shift */\
  '*',\
    0,  /* Alt */\
  ' ',  /* Space bar */\
    CAPS_LOCK,  /* Caps lock */\
    0,  /* 59 - F1 key ... > */\
    0,   0,   0,   0,   0,   0,   0,   0,\
    0,  /* < ... F10 */\
    0,  /* 69 - Num lock*/\
    0,  /* Scroll Lock */\
    0,  /* Home key */\
    0,  /* Up Arrow */\
    0,  /* Page Up */\
  '-',\
    0,  /* Left Arrow */\
    0,\
    0,  /* Right Arrow */\
  '+',\
    0,  /* 79 - End key*/\
    0,  /* Down Arrow */\
    0,  /* Page Down */\
    0,  /* Insert Key */\
    0,  /* Delete Key */\
    0,   0,   0,\
    0,  /* F11 Key */\
    0,  /* F12 Key */\
    0,  /* All other keys are undefined */\
};


/* Handles the keyboard interrupt */
void keyboard_handler(struct regs *r)
{
    unsigned char scancode;

    /* Read from the keyboard's data buffer */
    scancode = inportb(0x60);

    /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
    if (scancode & 0x80)
    {
        if ((char)kbdus[scancode] == LEFT_SHIFT || (char)kbdus[scancode] == RIGHT_SHIFT)
        {
           state--;
        }
        else if (kbdus[scancode] == CAPS_LOCK)
        {
            if (state == 0)
            {
                state++;
            }
            else
            {
                state--;
            }
        }
    }
    else
    {
	if ((char)kbdus[scancode] == LEFT_SHIFT || (char)kbdus[scancode] == RIGHT_SHIFT)
        {
            state++;
        }
        else if ((char)kbdus[scancode] == '\b')
        {
            put(0x08);
            put(' ');
            put(0x08);
        }
        else
        {
            if (state == 1)
            {
                put(uc_kb[scancode]);
            }
            else
            {
                put(kbdus[scancode]);
            }
        }
    }
}


void keyboard_install()
{
  irq_install_handler(1, keyboard_handler, "Keyboard");
}

