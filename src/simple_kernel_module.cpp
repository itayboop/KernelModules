#include <linux/init.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>

MODULE_AUTHOR("I & R");
MODULE_DESCRIPTION("Simple helllo world KM");

static int __init custom_init(void)
{
    printk(KERN_INFO "Hello world.");
    return 0;
}

static void __exit custom_exit(void)
{
    printk(KERN_INFO "Goodbye world");
}

module_init(custom_init);
module_exit(custom_exit);
