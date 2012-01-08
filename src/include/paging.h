#ifndef CORE_H
#include "core.h"
#endif

#ifndef PAGING_H
#define PAGING_H

typedef struct page
{
    u32int present    : true;   // Page present in memory
    u32int rw         : true;   // Read-only if clear, readwrite if set
    u32int user       : true;   // Supervisor level only if clear
    u32int accessed   : true;   // Has the page been accessed since last refresh?
    u32int dirty      : true;   // Has the page been written to since last refresh?
    u32int unused     : true;   // Amalgamation of unused and reserved bits
    u32int frame      : 20;     // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
    page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
    /**
       Array of pointers to pagetables.
    **/
    page_table_t *tables[1024];
    /**
       Array of pointers to the pagetables above, but gives their *physical*
       location, for loading into the CR3 register.
    **/
    u32int tablesPhysical[1024];

    /**
       The physical address of tablesPhysical. This comes into play
       when we get our kernel heap allocated and the directory
       may be in a different location in virtual memory.
    **/
    u32int physicalAddr;
} page_directory_t;


void alloc_frame(page_t *page, bool is_kernel, bool is_writeable);

void free_frame(page_t *page);

void init_paging(void);

void switch_page_directory(page_directory_t *dir);

page_t *get_page(u32int address, int make, page_directory_t *dir);

void page_fault(struct regs regist);

#endif
