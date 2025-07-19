#include <linux/slab.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/string.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include "plugin_manager/src/core_module.h"
#include "plugin_manager/src/common.h"

#define SAFE_FREE(ptr) \
    do { \
        if (ptr) { \
            kfree(ptr); \
            ptr = NULL; \
        } \
    } while (0)

static plugin_t* g_plugin = NULL;

static int start_plugin(void) {
    printk(KERN_INFO "starting dummy plugin\n");

    return 0;
}

static int stop_plugin(void) {
    printk(KERN_INFO "stopping dummy plugin\n");

    return 0;
}

static int cleanup(void) {
    printk(KERN_INFO "cleaning up dummy plugin\n");

    return 0;
}

static int __init init_entry(void) {
    int ret = -1;
    printk(KERN_INFO "loading dummy plugin\n");

    g_plugin = kmalloc(sizeof(plugin_t), GFP_KERNEL);

    ASSERT(g_plugin != NULL, -ENOMEM);

    g_plugin->name = "dummy_plugin";
    g_plugin->start = start_plugin;
    g_plugin->stop = stop_plugin;
    g_plugin->cleanup = cleanup;

    ASSERT(register_plugin(g_plugin) != -1, -1);

    ret = 0;
cleanup:
    if (ret != 0) {
        printk(KERN_ERR "Failed to register dummy plugin.\n");
        SAFE_FREE(g_plugin);
    }

    return ret;
}

static void __exit exit_entry(void) {
    printk(KERN_INFO "unloading dummy plugin\n");

    unregister_plugin(g_plugin);
    printk(KERN_INFO "Dummy plugin unregistered successfully.\n");
    SAFE_FREE(g_plugin);
}

module_init(init_entry);
module_exit(exit_entry);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ReiN & Hadad");
MODULE_DESCRIPTION("Dummy plugin");
