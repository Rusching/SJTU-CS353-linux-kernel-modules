# LinuxKernelModule
In this project there are some trivial linux kernel moudles to help realizing the module programming. Four simple modules show the basic structure of a kernel module, how to accept parameters from the user, and the simple use of the proc file system. Can be used as an introduction to kernel module programming
## Contents
Module 1 is a simplest kernel module which printed prompt information can be viewed by `dmesg`.

Module 2 can accept parameters passed in when importing the module, including an int, a string, and an int array types (the number of elements in the array is up to 10).

Module 3 created a read-only file under the proc file directory

Module 4 created a directory under the proc file directory, and a readable and writable file is created under the new directory.
## Run
Use the attached `Makefile` to complile the 4 kernel modules. Use `insmod module__.ko` to import compiled module, and `rmmod module__` to remove it. When importing a kernel module and entering parameters, you need to specify the variables that accept the parameters. You can use `echo` to write the writable file. The command should be run from the root user or a user with root privileges.



