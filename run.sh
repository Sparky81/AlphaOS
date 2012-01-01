#!/bin/bash
if [ -f build/Kernel.bin ];
then
   qemu-system-i386 -kernel build/Kernel.bin
else
   make && qemu-system-i386 -kernel build/Kernel.bin
fi 
  
