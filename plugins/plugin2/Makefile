obj-m += dummy_plugin2.o

PWD := $(CURDIR)
MODULE_NAME := dummy_plugin2
ROOT_DIR ?= ~/dev/KernelModules
SRC_DIR := $(PWD)
EXTRA_SYMBOLS := $(ROOT_DIR)/plugin_manager/build/Module.symvers
INCLUDE := $(ROOT_DIR)/plugin_manager

include $(ROOT_DIR)/makefiles/build_makefile.mk
