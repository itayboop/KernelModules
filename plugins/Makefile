obj-m += dummy_plugin.o

# Path to your core build Module.symvers
EXTRA_SYMBOLS := $(PWD)/../kernel/Module.symvers
PWD := $(CURDIR)

all:
	make -C /lib/modules/6.14.0-24-generic/build M=$(PWD) KBUILD_EXTRA_SYMBOLS=$(EXTRA_SYMBOLS) modules

clean:
	make -C /lib/modules/6.14.0-24-generic/build M=$(PWD) clean
