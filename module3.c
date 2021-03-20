#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/proc_fs.h>
#include<linux/seq_file.h>
struct proc_dir_entry *my_entry;
static int open_show(struct seq_file *m, void *v){
	seq_printf(m,"May you find and create something new in life\n");
	return 0;
}
static int my_open(struct inode *inode,struct file *file){
	return single_open(file,open_show,NULL);
}
static const struct file_operations proc_file_fops={
	.owner=THIS_MODULE,
	.open=my_open,
	.read=seq_read,
	.llseek=seq_lseek,
	.release=single_release,
};
static int __init module3_init(void){
	my_entry=proc_create("Gate",0,NULL,&proc_file_fops);
	if(!my_entry){
		return -1;
	}
	else{
		printk(KERN_INFO"Created a read-only proc file\n");
		return 0;
	
	}
}
static void __exit module3_exit(void){
	remove_proc_entry("Gate",NULL);
	printk(KERN_INFO"Take care, my friend\n");
}
module_init(module3_init);
module_exit(module3_exit);
