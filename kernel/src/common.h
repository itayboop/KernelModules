#pragma once

#define ASSERT_AND_GOTO_LABEL(condition, error, label) \
    do { \
        if (!(condition)) { \
            printk(KERN_ERR "Assertion failed: %s, file: %s, line: %d\n", #condition, __FILE__, __LINE__); \
            ret = error; \
            goto label; \
        } \
    } while (0)

#define ASSERT(condition, error) ASSERT_AND_GOTO_LABEL(condition, error, cleanup)
