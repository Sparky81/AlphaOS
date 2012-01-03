/* AlphaOS v0.1
 * Copyright (c) 2012, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

#ifndef IRQ_H
#define IRQ_H

void irq_install_handler(int irq, void (*handler)(struct regs *r), char *handler_name);
void irq_uninstall_handler(int irq);
void irq_remap(void);
void irq_install(void);
void irq_handler(struct regs *r);

#endif
