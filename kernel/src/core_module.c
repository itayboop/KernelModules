#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/string.h>

#include <linux/module.h>
#include <linux/kernel.h>

#include "core_module.h"
#include "common.h"

#define BUFFER_SIZE (1024)
#define NUM_PLUGINS (10)
#define PROC_ENTRY_NAME ("core_module")

static struct plugin_ops_s* g_plugins[NUM_PLUGINS] = {};
static struct proc_dir_entry* g_core_proc_entry = NULL;

static ssize_t proc_read(struct file* File, char* buf, size_t size, loff_t* offset)
static ssize_t proc_write(struct file *file, const char* user_buffer, size_t count, loff_t *ppos)

struct proc_ops g_pops = {
    .proc_read = proc_read,
    .proc_write = proc_write,
};

int start_plugin(const char* name) {
    for (size_t i = 0; i < NUM_PLUGINS; i++) {
        if (g_plugins[i] && strcmp(g_plugins[i]->name, name) == 0) {
            printk(KERN_INFO "Starting plugin: %s\n", name);
            return g_plugins[i]->start();
        }
    }
    printk(KERN_ERR "Plugin %s not found\n", name);
    return -ENOENT;
}

static int str_to_int(const char* str) {
    int value = 0;
    while (*str) {
        if (*str < '0' || *str > '9') {
            return -EINVAL; // Invalid character
        }
        value = value * 10 + (*str - '0');
        str++;
    }
    return value;
}

static int callback(unsigned int id, const char* data, size_t size) {
    int ret_val = -EINVAL;
    printk(KERN_INFO "Callback called with id: %u, data: %s, size: %zu\n", id, data, size);
    plugin_commands_t command = str_to_int(data);
    switch(command) {
        case PLUGIN_START:
            return start_plugin("dummy_plugin");
        case PLUGIN_STOP:
            // Implement stop logic if needed
            printk(KERN_INFO "Stopping plugin with id: %u\n", id);
            break; // Return 0 on success
        case PLUGIN_STATUS:
            // Implement status logic if needed
            printk(KERN_INFO "Status request for plugin with id: %u\n", id);
            break; // Return 0 on success
        default:
            printk(KERN_ERR "Unknown command: %c\n", data[0]);
            goto cleanup;
    }
    ret_val = 0;
cleanup:
    return -EINVAL;
}

static ssize_t proc_read(struct file* File, char* buf, size_t size, loff_t* offset) {
    int ret_val = -EFAULT;
    printk(KERN_INFO "proc_read called with size: %zu\n", size);
    static const char *msg = "Hello from the kernel!\n";
    size_t len = strlen(msg);
    if (len > 0) {
        ASSERT(copy_to_user(buf, msg, len) == 0, -EFAULT);

        ret_val = len;
        goto cleanup;
    }

    ret_val = 0; // EOF
cleanup:
    return ret_val;
}

static ssize_t proc_write(struct file *file, const char* user_buffer, size_t count, loff_t *ppos) {
    printk(KERN_INFO "proc_write called with count: %zu\n", count);
    unsigned int id = pde_data(file_inode(file));
    ssize_t ret = -1;
    char* kbuf = NULL;
 
    ASSERT(count < sizeof(kbuf), -EINVAL);
    kbuf = kmalloc(count, GFP_KERNEL);
    ASSERT(kbuf != NULL, -ENOMEM);

    ASSERT(copy_from_user(kbuf, user_buffer, count) == 0, -EFAULT);

    kbuf[count] = '\0';
    printk(KERN_INFO "proc_write received: %s\n", kbuf);

    ASSERT(callback(id, kbuf, count) != -1, -EFAULT);

    ret = count;
cleanup:
    return ret;
}

EXPORT_SYMBOL(register_plugin);
int register_plugin(struct plugin_ops_s* ops) {
    int ret = -1;
    static size_t current_plugin_count = 0;
    ASSERT(ops != NULL, -EINVAL);

    g_plugins[current_plugin_count++] = ops;
    ASSERT(current_plugin_count <= NUM_PLUGINS, -ENOMEM);
    printk(KERN_INFO "plugin_register called with ops: %p\n", ops);

    ops->plugin_entry = proc_create(ops->name, 0666, g_core_proc_entry, &g_pops);
    ASSERT(ops->plugin_entry != NULL, -ENOMEM);

    ret = 0;
cleanup:
    return 0;
}

static int __init init_entry(void) {
    int ret = -1;
    printk(KERN_INFO "core inited!\n");

    g_core_proc_entry = proc_mkdir(PROC_ENTRY_NAME, NULL);
    ASSERT(g_core_proc_entry != NULL, -ENOMEM);
    printk(KERN_INFO "Proc entry %s created successfully.\n", PROC_ENTRY_NAME);

    ret = 0;
cleanup:
    return ret;
}

static void __exit exit_entry(void) {
    if (g_core_proc_entry) {
        for (size_t i = 0; i < NUM_PLUGINS; i++) {
            if (g_plugins[i] && g_plugins[i]->plugin_entry) {
                proc_remove(g_plugins[i]->plugin_entry);
                printk(KERN_INFO "Removed proc entry for plugin: %s\n", g_plugins[i]->name);
            }
        }
        proc_remove(g_core_proc_entry);
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
