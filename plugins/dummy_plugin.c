#include <linux/slab.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/string.h>

#include <linux/module.h>
#include <linux/kernel.h>
#include "../kernel/src/core_module.h"
#include "../kernel/src/common.h"

#define SAFE_FREE(ptr) \
    do { \
        if (ptr) { \
            kfree(ptr); \
            ptr = NULL; \
        } \
    } while (0)

static struct plugin_ops_s* g_ops;

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

    g_ops = kmalloc(sizeof(plugin_ops_t), GFP_KERNEL);

    ASSERT(g_ops != NULL, -ENOMEM);

    g_ops->name = "dummy_plugin";
    g_ops->start = start_plugin;
    g_ops->stop = stop_plugin;

    ASSERT(register_plugin(g_ops) != -1, -1);

    ret = 0;
cleanup:
    if (ret != 0) {
        printk(KERN_ERR "Failed to register dummy plugin.\n");
        SAFE_FREE(g_ops);
    }

    return ret;
}

static void __exit exit_entry(void) {
    printk(KERN_INFO "unloading dummy plugin\n");

    SAFE_FREE(g_ops);
}

module_init(init_entry);
module_exit(exit_entry);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ReiN & Hadad");
MODULE_DESCRIPTION("Dummy plugin");
