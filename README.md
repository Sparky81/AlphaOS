AlphaOS Kernel - **README**
-----------------------
Version 1.0
===========

___Copyright (c) 2011, Robert Schofield and Matthew Carey___
-----------------------------------------------------------------------------------------------------------------------
*License information is in the file named LICENSE.*
**Read the above before using this code, in development or in testing of AlphaOS.**

Contact Information:
+ Email: <mailto:Sparky@AlphaChat.net>
+ Email: <mailto:matthew.b.carey@gmail.com>
+ IRC Network: AlphaChat 
+ Host: [irc.alphachat.net](irc://irc.alphachat.net:6667)
+ Project Channel: #AlphaOS
-----------------------------------------------------------------------------------------------------------------------

### I. About
>  AlphaOS is an Operating System originally created by Robert Schofield and 
>  Matthew Carey, as a way to experiment with our knowledge in the different
>  programming languages, like Assembly, C, and C++.  It currently is in the
>  very early stages of development and does not have a bootloader yet that 
>  works with a disk. This will change in the coming months, as we will 
>  create our own bootloader, and allow the usage of grub with it as well.

  To build the kernel:
  ====================
    
        make
    
  To test it out:
  ===============
    
        qemu -kernel build/Kernel.bin
    