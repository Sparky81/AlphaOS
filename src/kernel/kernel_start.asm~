[BITS 32]

[global start]
[extern main]



;;;;;;;;;;;;;;;;;;;;;;;; MULTIBOOT
MB_MODULEALIGN          equ 1<<0                         ; align loaded modules on page boundaries
MB_MEMINFO              equ 1<<1                         ; provide memory map
MB_AOUT                 equ 1<<16                       
MB_FLAGS                equ MB_MODULEALIGN | MB_MEMINFO | MB_AOUT        ; this is the Multiboot 'flag' field
MB_MAGIC                equ 0x1badb002                   ; 'magic number' lets bootloader find the header
MB_CHECKSUM             equ -(MB_MAGIC + MB_FLAGS)              ; checksum required


;;;;;;;;;;;;;;;;;;;;;;;; KERNEL STUFF
STACKSIZE               equ 0x4000                        ; set size for stack, 16k stack


;;;;;;;;;;;;;;;;;;;;;;;; OTHER STUFF
VIDEO_MEMORY            equ 0xb8000

MultiBootHeader:
  dd MB_MAGIC
  dd MB_FLAGS
  dd MB_CHECKSUM
  dd MultiBootHeader
  dd start
  dd kernel_end
  dd kernel_end
  dd start

start:
  
  mov ax, 10h             ; Save data segment identifyer
  mov ds, ax              ; Move a valid data segment into the data segment register
  mov ss, ax              ; Move a valid data segment into the stack segment register
  mov esp, 0x1ffffc ; set up the stack
  push eax ; pass Multiboot magic number
  push ebx ; pass Multiboot info structure
  
  CALL main

  CLI 
  

hang:
   hlt                                ; halt machine should kernel return
   jmp   hang

kernel_end:


