AlphaOS Kernel - **README**
-----------------------
Version 1.0
===========

___Copyright (c) 2011, Robert Schofield and Matthew Carey___
-----------------------------------------------------------------------------------------------------------------------
*License information is in the file named LICENSE.*
**Read the above before using this code, in development or in testing of AlphaOS.**

Contact Information:

> Robert  S.: <mailto:rjschofield81@gmail.com>
> <br />Matthew C.: <mailto:matthew.b.carey@gmail.com>

> IRC Network: AlphaChat 
> <br />Host: [irc.alphachat.net](irc://irc.alphachat.net:6667)
> <br />Project Channel: #AlphaOS

-----------------------------------------------------------------------------------------------------------------------

### I. About
>  AlphaOS is an Operating System originally created by Robert Schofield and 
>  Matthew Carey, as a way to experiment with our knowledge in the different
>  programming languages, like Assembly, C, and C++.  It currently is in the
>  very early stages of development and does not have a bootloader yet that 
>  works with a disk. 

  To build the kernel:
======================
    
        make
    
  To test it out:
=================
    
        qemu -kernel build/Kernel.bin
    
  To build and test the kernel:
===============================

	./run.sh