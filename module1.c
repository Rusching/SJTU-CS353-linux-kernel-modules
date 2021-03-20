#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
static int __init module1_init(void){
	printk(KERN_INFO "module1 loaded\n");
	return 0;
}
static void __exit module1_exit(void){
	printk(KERN_INFO"module1 unloaded\n");
}
module_init(module1_init);
module_exit(module1_exit);
