#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include <linux/module.h>
#include <linux/kernel.h>

#define PROC_ENTRY_NAME ("hello_proc")
static struct proc_dir_entry *proc_entry = NULL;

static ssize_t proc_read(struct file* File, char* buf, size_t size, loff_t* offset) {
    static const char *msg = "Hello from the kernel!\n";
    size_t len = strlen(msg);
    if (len > 0) {
        if (copy_to_user(buf, msg, len)) {
            return -EFAULT;
        }
        return len;
    }
    return 0; // EOF
}

static ssize_t proc_write(struct file *file, const char* buf, size_t count, loff_t *ppos) {
    ssize_t ret = -1;
    char kbuf[128] = {};

    if (count > sizeof(kbuf) - 1)
        ret = -EINVAL;
        goto cleanup;

    if (copy_from_user(kbuf, buf, count))
        ret = -EFAULT;
        goto cleanup;

    kbuf[count] = '\0';
    printk(KERN_INFO "proc_write received: %s\n", kbuf);

    ret = count; // Return the number of bytes written

cleanup:
    return ret;
}

static struct proc_ops fops = {
    .proc_read = proc_read,
    .proc_write = proc_write,
};

static int core_proc_show(struct seq_file *m, void *v)
{
    static const char *msg = "Hello from the kernel!\n";
	seq_puts(m, msg);
	seq_putc(m, '\n');
	return 0;
}


static int __init init_entry(void) {
    int ret = -1;
    printk(KERN_INFO "core inited!\n");
    proc_entry = proc_create_single(PROC_ENTRY_NAME, 0666, NULL, core_proc_show);
    if (proc_entry == NULL) {
        printk(KERN_ERR "Failed to create proc entry: %s\n", PROC_ENTRY_NAME);
        ret = -ENOMEM;
        goto cleanup;
    }
    printk(KERN_INFO "Proc entry created successfully.\n");

    ret = 0;

cleanup:
    return ret;
}

static void __exit exit_entry(void) {
    if (proc_entry) {
        proc_remove(proc_entry);
        printk(KERN_INFO "Proc entry removed successfully.\n");
    } else {
        printk(KERN_WARNING "No proc entry to remove.\n");
    }
    printk(KERN_INFO "core destroyed!\n");
}

module_init(init_entry);
module_exit(exit_entry);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ReiN & Hadad");
MODULE_DESCRIPTION("A core module with proc filesystem support");
