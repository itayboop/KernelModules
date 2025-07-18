# CONFIG_MODULE_SIG disabled the module signature verfication.
# This is useful for development purposes, but should be enabled for production.
CONFIG_MODULE_SIG=n	

# CURDIR resolves the cwd after the Makefile is executed.
PWD := $(CURDIR)

obj-m += src/core_module.o

all:
	make -C /lib/modules/6.14.0-24-generic/build M=$(PWD) modules

clean:
	make -C /lib/modules/6.14.0-24-generic/build M=$(PWD) clean
