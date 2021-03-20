// import necessary libraries
#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/moduleparam.h>
// define the max size of the int array
#define MAX_SIZE 10
// define the variables to accept parameters from users and assign initial values
static int int_var=603;
static char* string="hello,abyss";
static int array_num=10;
static int int_array[MAX_SIZE]={1,2,3,4,5};
// specify the variables to accept parameters and indicate permissions
module_param(int_var,int,S_IRUGO);
module_param(string,charp,S_IRUGO);
module_param_array(int_array,int,&array_num,S_IRUGO);
// define the initial function
static int __init module2_init(void){
	printk(KERN_INFO "module2 loaded\n");
	printk(KERN_INFO "Params: int_var: %d\n",int_var);
	printk(KERN_INFO "Params: string:  %s\n",string);
	printk(KERN_INFO "Params: int_array:");
	int length=array_num>MAX_SIZE?MAX_SIZE:array_num;
	int i=0;
	for(i=0;i<length;++i){
		printk(KERN_INFO"Element %d: %d",i+1,int_array[i]);
	}
	printk(KERN_INFO "The total number of elements in array is %d \n",length);
	return 0;
}
// define the exit funciton
static void __exit module2_exit(void){
	printk(KERN_INFO"module2 unloaded\n");
}
// specify the initial and exit function
module_init(module2_init);
module_exit(module2_exit);
