obj-m += dummy_plugin.o

PWD := $(CURDIR)
MODULE_NAME := dummy_plugin
ROOT_DIR ?= ~/src/KernelModules
SRC_DIR := $(PWD)
EXTRA_SYMBOLS := $(ROOT_DIR)/plugin_manager/build/Module.symvers

include $(ROOT_DIR)/common/ko_makefile_template.mk
