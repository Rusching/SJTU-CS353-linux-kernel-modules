// import necessary libraries
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
// define the initial function 
static int __init module1_init(void){
	printk(KERN_INFO "module1 loaded\n");
	return 0;
}
// define the exit function
static void __exit module1_exit(void){
	printk(KERN_INFO"module1 unloaded\n");
}
// specify the initial and exit function
module_init(module1_init);
module_exit(module1_exit);
