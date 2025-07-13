#include "core_modules.h"
#include <linux/slab.h>

int start_my_plugin(void) {
    printk(KERN_INFO "starting dummy plugin\n");
}

int stop_my_plugin(void) {
    printk(KERN_INFO "stopping dummy plugin\n");
}

void __init dummy_plugin_init(void) {
    printk(KERN_INFO "loading dummy plugin\n");

    struct plugin_ops* ops = kmalloc(sizeof(struct plugin_ops));
    ops->name = "dummy_plugin";
    ops->start = start_my_plugin;
    ops->stop = stop_my_plugin;
    register_plugin();
}

void __exit dummy_plugin_exit(void) {
    printl(KERN_INFO "unloading dummy plugin\n");
}

module_init(dummy_plugin_init);
module_exit(dummy_plugin_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ReiN & Hadad");
MODULE_DESCRIPTION("Dummy plugin");
