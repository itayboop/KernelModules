#ifndef __CORE_MODULE_H__
#define __CORE_MODULE_H__

#include <linux/proc_fs.h>

struct plugin_ops {
    const char* name;
    int (*start)(void);
    int (*stop)(void);
    struct proc_dir_entry* plugin_entry;
};

typedef enum plugin_commands_e {
    PLUGIN_START,
    PLUGIN_STOP,
    PLUGIN_STATUS,
} plugin_commands_t;

int register_plugin(struct plugin_ops* ops);

#endif // __CORE_MODULE_H__