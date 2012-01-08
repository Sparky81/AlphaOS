/* AlphaOS v0.1
 * Copyright (c) 2012, Robert Schofield and Matthew Carey
 * All rights reserved.
 */

/* NOTICE:
 * This code was taken from James Molloy's kernel development tutorial.
 * Website: http://jamesmolloy.co.uk/tutorial_html/
 * Our own version will eventually be written and implemented, this is 
 * currently being used solely for the purpose of testing. */

// paging.c -- Defines the interface for and structures relating to paging.
//             Written for JamesM's kernel development tutorials.

#include "include/core.h"
#include "include/paging.h"
#include "include/kmalloc.h"
#include "include/text.h"

// The kernel's page directory
page_directory_t *kernel_directory=0;

// The current page directory;
page_directory_t *current_directory=0;

// A bitset of frames - used or free.
u32int *frames;
u32int nframes;

// Defined in kheap.c AlphaOS
extern u32int placement_address;

// Macros used in the bitset algorithms.
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

// Static function to set a bit in the frames bitset
static void set_frame(u32int frame_addr)
{
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    frames[idx] |= (0x1 << off);
}

// Static function to clear a bit in the frames bitset
static void clear_frame(u32int frame_addr)
{
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    frames[idx] &= ~(0x1 << off);
}

// Static function to test if a bit is set.
static u32int test_frame(u32int frame_addr)
{
    u32int frame = frame_addr/0x1000;
    u32int idx = INDEX_FROM_BIT(frame);
    u32int off = OFFSET_FROM_BIT(frame);
    return (frames[idx] & (0x1 << off));
}

// Static function to find the first free frame.
static u32int first_frame()
{
    u32int i, j;
    for (i = 0; i < INDEX_FROM_BIT(nframes); i++)
    {
        if (frames[i] != 0xFFFFFFFF) // nothing free, exit early.
        {
            // at least one bit is free here.
            for (j = 0; j < 32; j++)
            {
                u32int toTest = 0x1 << j;
                if ( !(frames[i]&toTest) )
                {
                    return i*4*8+j;
                }
            }
        }
    }
}

// Function to allocate a frame.
void alloc_frame(page_t *page, bool is_kernel, bool is_writeable)
{
    if (page->frame != 0)
    {
        return;
    }
    else
    {
        u32int idx = first_frame();
        if (idx == (u32int)-1)
        {
            // PANIC! no free frames!!
        }
        set_frame(idx*0x1000);
        page->present = 1;
        page->rw = (is_writeable)?true:false;
        page->user = (is_kernel)?false:true;
        page->frame = idx;
    }
}

// Function to deallocate a frame.
void free_frame(page_t *page)
{
    u32int frame;
    if (!(frame=page->frame))
    {
        return;
    }
    else
    {
        clear_frame(frame);
        page->frame = 0x0;
    }
}

void init_paging()
{
    // The size of physical memory. For the moment we 
    // assume it is 16MB big.
    u32int mem_end_page = 0x1000000;
    
    nframes = mem_end_page / 0x1000;
    frames = (u32int*)kmalloc(INDEX_FROM_BIT(nframes));
    kmemset((u8int *)frames, (u8int)0, (u32int)INDEX_FROM_BIT(nframes));
    
    // Let's make a page directory.
    kernel_directory = (page_directory_t*)kmalloc_a(sizeof(page_directory_t));
    current_directory = kernel_directory;

    // We need to identity map (phys addr = virt addr) from
    // 0x0 to the end of used memory, so we can access this
    // transparently, as if paging wasn't enabled.
    // NOTE that we use a while loop here deliberately.
    // inside the loop body we actually change placement_address
    // by calling kmalloc(). A while loop causes this to be
    // computed on-the-fly rather than once at the start.
    int i = 0;
    while (i < placement_address)
    {
        // Kernel code is readable but not writeable from userspace.
        alloc_frame( get_page(i, 1, kernel_directory), 0, 0);
        i += 0x1000;
    }
    // Before we enable paging, we must register our page fault handler.
    irq_install_handler(3, page_fault, "Paging: Page Fault");

    // Now, enable paging!
    switch_page_directory((page_directory_t *)kernel_directory);
}

extern void write_cr3(unsigned long);
extern void write_cr0(unsigned long);
extern unsigned int read_cr0(void);

void switch_page_directory(page_directory_t *dir)
{
    current_directory = dir;
    write_cr3(*dir->tablesPhysical);
    //write_cr0(read_cr0() | 0x80000000);
    //__asm__ __volatile__("mov %0, %%cr3":: "b"(&dir->tablesPhysical));
    //unsigned int cr0;
    //asm volatile("mov %%cr0, %0": "=b"(cr0));
    //cr0 |= 0x80000000;
    //asm volatile("mov %0, %%cr0":: "b"(cr0));
}

page_t *get_page(u32int address, int make, page_directory_t *dir)
{
    // Turn the address into an index.
    address /= 0x1000;
    // Find the page table containing this address.
    u32int table_idx = address / 1024;
    if (dir->tables[table_idx]) // If this table is already assigned
    {
        return &dir->tables[table_idx]->pages[address%1024];
    }
    else if(make)
    {
        u32int tmp;
        dir->tables[table_idx] = (page_table_t*)kmalloc_ap(sizeof(page_table_t), &tmp);
        dir->tablesPhysical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
        return &dir->tables[table_idx]->pages[address%1024];
    }
    else
    {
        return 0;
    }
}


void page_fault(struct regs regist)
{
    // A page fault has occurred.
    // The faulting address is stored in the CR2 register.
    u32int faulting_address;
    asm volatile("mov %%cr2, %0" : "=r" (faulting_address));
    
    // The error code gives us details of what happened.
    bool present   = !(regist.err_code & 0x1); // Page not present
    bool rw = regist.err_code & 0x2;           // Write operation?
    bool us = regist.err_code & 0x4;           // Processor was in user-mode?
    bool reserved = regist.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
    bool id = regist.err_code & 0x10;          // Caused by an instruction fetch?

    // Output an error message.
    //char *status;
    kprintf("Page fault!:( %?%?%? ):%x\n",
                                           present,  "present ",
                                           rw,       "read-only ",
                                           us,       "user-mode ",
                                           reserved, "reserved",
                                           faulting_address);

    die("Page fault");
}
