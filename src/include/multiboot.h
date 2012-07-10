#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "core.h"

struct multiboot
{
        u32int flags;
        u32int mem_lower;
        u32int mem_upper;
        u32int boot_device;
        u32int cmdline;
        u32int mods_count;
        u32int mods_addr;
        u32int num;
        u32int size;
        u32int addr;
        u32int shndx;
        u32int mmap_length;
        u32int mmap_addr;
        u32int drives_length;
        u32int drives_addr;
        u32int config_table;
        u32int boot_loader_name;
        u32int apm_table;
        u32int vbe_control_info;
        u32int vbe_mode_info;
        u32int vbe_mode;
        u32int vbe_interface_seg;
        u32int vbe_interface_off;
        u32int vbe_interface_len;
} __attribute__((packed));

typedef struct
{
  uint32_t size;
  uint32_t base_addr_low;
  uint32_t base_addr_high;
  uint32_t length_low;
  uint32_t length_high;
  uint32_t type;
} __attribute__((packed)) mmap_entry_t;

#endif