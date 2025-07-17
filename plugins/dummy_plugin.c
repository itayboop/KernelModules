#include <linux/slab.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/string.h>

#include <linux/module.h>
#include <linux/kernel.h>
#include "../kernel/src/core_module.h"
#include "../kernel/src/common.h"

plugin_ops_t* ops;

static int start_plugin(void) {
    printk(KERN_INFO "starting dummy plugin\n");

    return 0;
}

static int stop_plugin(void) {
    printk(KERN_INFO "stopping dummy plugin\n");

    return 0;
}

static int __init init_entry(void) {
    int ret = -1;
    printk(KERN_INFO "loading dummy plugin\n");

    ops = kmalloc(sizeof(plugin_ops_t), GFP_KERNEL);

    ASSERT_AND_GOTO_LABEL(ops != NULL, -ENOMEM, cleanup);

    ops->name = "dummy_plugin";
    ops->start = start_plugin;
    ops->stop = stop_plugin;

    ASSERT_AND_GOTO_LABEL(register_plugin(ops) != -1, -1 ,cleanup);

    ret = 0;
cleanup:
    if (ret != 0) {
        printk(KERN_ERR "Failed to register dummy plugin.\n");
        if (ops) {
            kfree(ops);
            ops = NULL;
        }
    }

    return ret;
}

static void __exit exit_entry(void) {
    printk(KERN_INFO "unloading dummy plugin\n");

    if (ops) {
        kfree(ops);
        ops = NULL;
    }
}

module_init(init_entry);
module_exit(exit_entry);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ReiN & Hadad");
MODULE_DESCRIPTION("Dummy plugin");
