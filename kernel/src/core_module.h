#ifndef __CORE_MODULE_H__
#define __CORE_MODULE_H__

#include <linux/proc_fs.h>

typedef enum plugin_state_e {
    PLUGIN_STATE_INITIALIZED,
    PLUGIN_STATE_RUNNING,
    PLUGIN_STATE_STOPPED,
    PLUGIN_STATE_DESTROYED,
    PLUGIN_STATE_ERROR,
} plugin_state_t;

typedef struct plugin_s {
    plugin_state_t state;
    const char* name;
    int (*start)(void);
    int (*stop)(void);
    int (*cleanup)(void);
    struct proc_dir_entry* plugin_entry;
} plugin_t;

typedef enum plugin_commands_e {
    PLUGIN_START,
    PLUGIN_STOP,
    PLUGIN_STATUS,
} plugin_commands_t;

int register_plugin(plugin_t* ops);
int unregister_plugin(plugin_t* ops);

#endif // __CORE_MODULE_H__
