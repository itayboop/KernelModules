#include "core_modules.h"
#include <linux/slab.h>
#include "core_modules.h"

plugin_ops_t* ops;

static int start_my_plugin(void) {
    printk(KERN_INFO "starting dummy plugin\n");
}

static int stop_my_plugin(void) {
    printk(KERN_INFO "stopping dummy plugin\n");
}

void __init dummy_plugin_init(void) {
    printk(KERN_INFO "loading dummy plugin\n");

    ops = kmalloc(sizeof(struct plugin_ops));
    if(!ops) {
        printk(KERN_ERR "failed to allocate memory for plugin_ops.\n");
        return;
    }
    ops->name = "dummy_plugin";
    ops->start = start_my_plugin;
    ops->stop = stop_my_plugin;

    register_plugin(ops);
}

void __exit dummy_plugin_exit(void) {
    printk(KERN_INFO "unloading dummy plugin\n");

    kfree(ops);
}

module_init(dummy_plugin_init);
module_exit(dummy_plugin_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ReiN & Hadad");
MODULE_DESCRIPTION("Dummy plugin");
