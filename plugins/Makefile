obj-m += dummy_plugin.o

# Path to your core build Module.symvers
EXTRA_SYMBOLS := ../kernel/src/Module.symvers

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) EXTRA_SYMBOLS=$(EXTRA_SYMBOLS) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
