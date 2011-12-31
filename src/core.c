/* AlphaOS v1.0
 * core.c - defines some global functions
 * Copyright (c) 2011, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#include "include/core.h"

// Write a byte out to the specified port.
void outb(u16int port, u8int value)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
    u8int ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

u16int inw(u16int port)
{
    u16int ret;
    __asm__ __volatile__ ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

// Copy len bytes from src to dest.
void memcpy(u8int *dest, const u8int *src, u32int len)
{
   const char *sp = (const char *)src; 
   /* sp stands for source pointer and the (const char *) is a cast */ 
   char *dp = (char *)dest; /* destination pointer, cast */
   for( ; len != 0; len--) *dp++ = *sp++;
   //return dest;
} 


// Write len copies of val into dest.
void memset(u8int *dest, u8int val, u32int len)
{
    char *dp = (char *)dest;
    for( ; len != 0; len--) *dp++ = val;
    //return dest;
}

// Compare two strings. Should return -1 if 
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(char *str1, char *str2)
{
    int len[2] = {0, 0};
    int i = 0;
    for( ; str1[i]; i++);
    len[0] = i;
    for(i = 0 ; str1[i]; i++);
    len[1] = i;
    if(len[0] < len[1])
    {
        return(-1);
    }
    else
    {
        if(len[0] == len[1])
        {
            return(0);
        }
        else
        {
            return(1);
        } 
    }
}

// Copy the NULL-terminated string src into dest, and
// return dest.
char *strcpy(char *dest, const char *src)
{
    while(*src)
    {
       *dest++ = *src++;
    }
    return dest;
}

// Concatenate the NULL-terminated string src onto
// the end of dest, and return dest.
char *strcat(char *dest, const char *src)
{
    for( ; *dest; *dest++);
    for( ; *src; *dest++ = *src++);
    return dest;
}

int strlen(char *str)
{
    int i;
    for(i = 0; *str; *str++) i++;
    return i;
}
