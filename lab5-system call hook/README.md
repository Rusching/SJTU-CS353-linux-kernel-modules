# lab5 system call hook

## Contents
This module replaces the `clone` system (with the system call number of `__NR_clone`) call in the system call table with a modified version of `clone` system call. The modified version also calls `clone`, but prints a prompt after the call.

Expected experiment output is:
* `Dmesg`: 

  system log output once "hacked" information.
* Run attached `test.o`: 

  system log output once "hacked" message.
* Run attached `Benchmark. o`: 

  system log outputs the message "hacked" six times.



## Run
Make the moduel using included `Makefile`. A test scipt `test_script.sh` is also attached.
