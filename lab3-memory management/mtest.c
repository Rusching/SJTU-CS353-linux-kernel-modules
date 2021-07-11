#include <linux/module.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/vmalloc.h>
#include <linux/highmem.h>
#include <linux/slab.h>


static struct proc_dir_entry *mtest_proc_entry;


static void listvma(void) {
    struct mm_struct *mm = current->mm;
    struct vm_area_struct *vma = mm->mmap;

    down_read(&(mm->mmap_sem)); 
    
	for (vma; vma; vma = vma->vm_next) {
        printk("VMA 0x%lx - 0x%lx\n", vma->vm_start, vma->vm_end);
		if (vma->vm_flags & VM_READ) {
			printk("r\n");
		}
		else {
			printk("-\n");
		}
		if (vma->vm_flags & VM_WRITE) {
			printk("w\n");
		}
		else {
			printk("-\n");
		}
		if (vma->vm_flags & VM_EXEC) {
			printk("x\n");
		}
		else {
			printk("-\n");
		}
        printk("\n");
    }
    up_read(&(mm->mmap_sem));
}


static struct page *inner_find_page(unsigned long vma) {
    struct mm_struct *mm = current->mm;
    struct page *page_c;

    pgd_t *pgd;
    pud_t *pud;
    pmd_t *pmd;
    pte_t *pte;

    pgd = pgd_offset(mm, vma);
    if (pgd_none(*pgd) || pgd_bad(*pgd)) {
        return NULL;
    }
    pud = pud_offset(pgd, vma);
    if (pud_none(*pud) || pud_bad(*pud)) {
        return NULL;
    }
    pmd = pmd_offset(pud, vma);
    if (pmd_none(*pmd) || pmd_bad(*pmd)) {
        return NULL;
    }
    pte = pte_offset_kernel(pmd, vma);
    if (pte_none(*pte)) {
        return NULL;
    }
    page_c = pte_page(*pte);
	get_page(page_c);
	return page_c;
}


static void findpage(unsigned long vma) {
    unsigned long pma;
    unsigned long page_address;
    unsigned long page_offset;

    struct page *page_c = inner_find_page(vma);

    if (!page_c) {
        printk("Translation not found\n");
        return;
    }

    page_address = page_to_phys(page_c) & PAGE_MASK;
    page_offset = vma & (~PAGE_MASK);
    pma = page_address | page_offset;

    printk("vma 0x%lx -> pma 0x%lx\n", vma, pma);
}


static void writeval(unsigned long vmad, unsigned long value) {
    struct vm_area_struct *vma = find_vma(current->mm, vmad);
    struct page *page_c = inner_find_page(vmad);

    if (!page_c || !vma || vma->vm_start > vmad || vma->vm_end < vmad) {
        printk("vma invalid\n");
        return;
    }
    if (!(vma->vm_flags & VM_WRITE)) {
        printk("unwritable\n");
        return;
    }

    unsigned long *k_address;
    k_address = (unsigned long*)page_address(page_c);
    k_address += vmad & (~PAGE_MASK);
    *k_address = value;
    printk("written 0x%lx to address 0x%lx\n", value, (unsigned long)k_address);
}



static ssize_t my_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos) {
    unsigned long address, value;
    unsigned short index;


	char buf[512];
	char data[512];
    if (*f_pos > 0 || count > 512)
        return -EFAULT;
    if (copy_from_user(buf, buffer, count))
        return -EFAULT;
    sscanf(buf, "%s", data);

    if (!strcmp(data, "listvma")) {
        listvma();
    } else if (!strcmp(data, "findpage")) {
        index = 9;
        sscanf(buf + index, "%s", data);
        kstrtoul(data, 16, &address);
        findpage(address);
    } else if (!strcmp(data, "writeval")) {
        index = 9;
        sscanf(buf + index, "%s", data);
        kstrtoul(data, 16, &address);
        while (*(buf + index) != ' ') index ++;
        index ++;
        sscanf(buf + index, "%s", data);
        kstrtoul(data, 16, &value);
        writeval(address, value);        
    }

    *f_pos = strlen(buf);
    return *f_pos;
}

static struct file_operations proc_mtest_operations = {
    .owner = THIS_MODULE,
    .write = my_write
};


static int __init mtest_init(void) {
    mtest_proc_entry = proc_create("mtest", 0666, NULL, &proc_mtest_operations);
	printk(KERN_INFO"Memory management module loaded\n");
	return 0;
}


static void __exit mtest_exit(void) {
    proc_remove(mtest_proc_entry);
	printk(KERN_INFO"Memory management module unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Memory management module");
MODULE_AUTHOR("Abyss");

module_init(mtest_init);
module_exit(mtest_exit);