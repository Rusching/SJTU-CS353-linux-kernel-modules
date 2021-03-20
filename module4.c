#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
struct proc_dir_entry *my_dir;
struct proc_dir_entry *my_entry;
static char my_buffer[256];
static int my_show(struct seq_file *m, void *v){
	if(strlen(my_buffer)==0){
		seq_printf(m,"This is a readable and writable file, so far nothing has been written in.\n");
	}
	else{
		seq_printf(m,"The content of this file: ");
		seq_printf(m,my_buffer);
	}
	return 0;
}
static int my_open(struct inode *inode, struct file *file){
	return single_open(file, my_show, NULL);
}
static ssize_t my_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos){
	if (copy_from_user(my_buffer,buffer,count)) {
		return -EFAULT;
	}
	else{
		return count;
	}
}
static struct file_operations my_fops = {
	.owner	= THIS_MODULE,
	.open	= my_open,
	.release = single_release,
	.read	= seq_read,
	.llseek	= seq_lseek,
	.write 	= my_write,
};
 
static int __init module4_init(void)
{
	my_dir=proc_mkdir("abyss",NULL);
	my_entry = proc_create("Gate", 0644, my_dir, &my_fops);
	if (!my_entry){
		return -ENOMEM;
 	}
	else{
		return 0;
	}
}
 
static void __exit module4_exit(void)
{
	remove_proc_entry("Gate", my_dir);
	remove_proc_entry("abyss",NULL);
}
module_init(module4_init);
module_exit(module4_exit);
