/* AlphaOS v0.1
 * Copyright (c) 2012, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#ifndef TEXT_H
#define TEXT_H

#include "colors.h"
#include "core.h"

void put(char c);

void clear();

void kprint(char *c);

void kputs(char *c);

void put_c(char c, u8int backColour, u8int foreColour);

void print(char c);

void kprintc(char *c, u8int bg, u8int fg);

void error(char *c);

void kprintf(char const *fmt, ...);

char *sprintf(char *str, char const *fmt, ...);

#endif
