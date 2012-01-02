/* AlphaOS v1.0
 * text.h - handles text printing functions
 * Copyright (c) 2011, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#ifndef TEXT_H
#define TEXT_H

#include "core.h"

void put(char c);

void clear();

void printf(char *c);

void puts(char *c);

void put_c(char c, u8int backColour, u8int foreColour);

void printc(char *c, u8int bg, u8int fg);

void error(char *c);

#endif
