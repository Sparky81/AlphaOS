#!/bin/bash
if [ -f build/Kernel.bin ];
then
   qemu -kernel build/Kernel.bin
else
   make && qemu -kernel build/Kernel.bin
fi 
  
