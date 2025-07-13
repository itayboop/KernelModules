#ifndef __CORE_MODULE_H__
#define __CORE_MODULE_H__

struct plugin_ops {
    const char* name;
    void (*start)(void);
    void (*stop)(void);
};

int register_plugin(struct plugin_ops* ops);

#endif // __CORE_MODULE_H__