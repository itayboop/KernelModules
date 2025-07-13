# CONFIG_MODULE_SIG disabled the module signature verfication.
# This is useful for development purposes, but should be enabled for production.
CONFIG_MODULE_SIG=n

# CURDIR resolves the cwd after the Makefile is executed.
PWD := $(CURDIR)

obj-m += dummy_plugin.o

all:
	make -C /lib/modules/$(shell uname -r)+/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
