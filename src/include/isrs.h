/* AlphaOS v0.1
 * Copyright (c) 2012, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#ifndef ISRS_H
#define ISRS_H

void isrs_install(void);
void fault_handler(struct regs *r);

#endif
