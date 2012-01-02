/* AlphaOS v1.0
 * text.h - handles text printing functions
 * Copyright (c) 2011, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#ifndef TEXT_H
#define TEXT_H

#include "colors.h"
#include "core.h"

void put(char c);

void clear();

void kprintf(char *c);

void kputs(char *c);

void put_c(char c, u8int backColour, u8int foreColour);

void print(char c);

void kprintc(char *c, u8int bg, u8int fg);

void error(char *c);

#endif
