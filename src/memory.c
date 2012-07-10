#include "include/multiboot.h"
#include "include/core.h"
#define PAGE_SIZE 0x1000

void init_memory(struct multiboot *mboot)
{
  u32int i = mboot->mmap_addr;
  int num_pages=0;
  unsigned int j=0;
  mmap_entry_t *me = (mmap_entry_t *)(i);
  kprintf("\n\n[Memory]: Minimum %d: %x - Maximum %x\n", me->type, me->base_addr_low, 
  mboot->mmap_addr);
}
