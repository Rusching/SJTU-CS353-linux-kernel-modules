# lab2 memory management

## Contents
This lab contain a kernel module, which can create a file `mtest` under the directory `/proc`, and this file can receive 3 kinds of parameters:
* `listvma`
  Print all the virtual memory addresses of current process, in the format of `start address end address permission`.
* `findpage addr`
  Translate given virtual address of current process to physical address and print out, if there doesn't exist such translation, print "translation not found". 'addr' is the address to find translation.
* `write addr val`
  Write certain value into specific virtual address. `addr` is the virtual address to be write value in, and `val` is the value to be written. 

## Run
Make this module using included `Makefile`.
