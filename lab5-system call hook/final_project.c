#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kallsyms.h>
#include <linux/unistd.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("ShiChen Sun");
MODULE_DESCRIPTION("Linux Kernel Final Project To Hook A System Call");

typedef asmlinkage long (*sys_clone_t)(unsigned long, unsigned long, int __user*,
	int __user*, unsigned long);
// define system call table
unsigned long *sys_call_table = NULL;
// define initial clone system call
sys_clone_t initial_clone = NULL;
// define cr0 register
long initial_cr0 = 0;

// allow OS to write read-only files
unsigned long allow_write_read_only_files(void) {
	unsigned int cr0 = 0;
	unsigned int ret = 0;
	asm volatile ("mov %%cr0, %%eax"
		: "=a"(cr0));
	ret = cr0;
	cr0 &= 0xfffeffff;
	asm volatile ("mov %%eax, %%cr0":: "a"(cr0)	);
	return ret;
}

// forbid OS to write read-only files
void forbid_write_read_only_files(unsigned long oldval) {
	asm volatile("mov %%eax, %%cr0":: "a"(oldval));
}

// modified clone system call
asmlinkage long modified_clone(unsigned long x1, unsigned long x2, int __user *x3,
                                 int __user *x4, unsigned long x5) {
	long ret_val = initial_clone(x1, x2, x3, x4, x5);
	printk(KERN_INFO "hello, I have hacked this syscall");
	return ret_val;
}

// module init function 
static int __init final_project_init(void) {
	// find system call table
	sys_call_table = (unsigned long *)kallsyms_lookup_name("sys_call_table");
	
	// record initial clone system call 
	initial_clone = (sys_clone_t)sys_call_table[__NR_clone];

	// allow OS to write read-only files, prepare for writing the system call table
	initial_cr0 = allow_write_read_only_files();

	// write the system call table and change the clone system call
	sys_call_table[__NR_clone] = (unsigned long)modified_clone;

	// forbid OS to write read-only files
	forbid_write_read_only_files(initial_cr0);

	printk(KERN_INFO "installed sys_clone_hook");
	return 0;
}

// module exit function
static void __exit final_project_exit(void) {
	// allow OS to write read-only files, prepare for restoring the system call table
	initial_cr0 = allow_write_read_only_files();

	// restore the clone system call
	sys_call_table[__NR_clone] = (unsigned long)initial_clone;

	// forbid OS to write read-only files
	forbid_write_read_only_files(initial_cr0);

	printk(KERN_INFO "uninstalled sys_clone_hook");
}

module_init(final_project_init);
module_exit(final_project_exit);
