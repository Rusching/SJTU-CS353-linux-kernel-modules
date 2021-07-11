# lab file system management

## Contents
This module is written based on the `/fs/romfs` file system, and can receive 3 kinds of parameters:
* `hided_file_name=xxx`

  Hide the file/path with name xxx.
* `encrypted_file_name=xxx`

  Encrypt the file content with name xxx.
* `exec_file_name`

  Change the permissions of the file xxx to executable.

## Run
Make the module using included `Makefile`. 

Test instructions may be useful:

```
apt-get install genromfs
genromfs –V "vromfs" –f test.img –d test
insmod romfs.ko hided_file_name=aa encrypted_file_name=bb exec_file_name=ft
mount -o loop test.img t
ls -l t
