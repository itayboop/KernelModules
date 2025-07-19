		# Kernel build dir
KDIR ?= /lib/modules/$(shell uname -r)+/build

# PWD — current working dir
PWD := $(shell pwd)

# REQUIRED: MODULE_NAME and SRC_DIR must be set by including Makefile!
ifndef MODULE_NAME
  $(error MODULE_NAME is not set!)
endif

ifndef SRC_DIR
  $(error SRC_DIR is not set!)
endif

# Compose EXTRA_SYMBOLS option only if given
ifdef EXTRA_SYMBOLS
  EXTRA_KERNEL_SYM := KBUILD_EXTRA_SYMBOLS=$(EXTRA_SYMBOLS)
endif

BUILD_DIR ?= build
INCLUDE := $(ROOT_DIR)/

TARGET := $(SRC_DIR)/$(MODULE_NAME).o

obj-m := $(TARGET)

$(info ${SRC_DIR})
all:
	mkdir -p $(BUILD_DIR)
	echo "obj-m := $(MODULE_NAME).o" > $(BUILD_DIR)/Makefile
	echo "SRC_DIR := ." >> $(BUILD_DIR)/Makefile
	echo 'ccflags-y += -I$${SRC_DIR}' >> $(BUILD_DIR)/Makefile
	cp $(SRC_DIR)/*.c $(BUILD_DIR)/ 2>/dev/null || true
	cp $(SRC_DIR)/*.h $(BUILD_DIR)/ 2>/dev/null || true

	$(MAKE) -C $(KDIR) M=$(PWD)/$(BUILD_DIR) $(EXTRA_KERNEL_SYM) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD)/$(BUILD_DIR) clean
	@rm -rf $(BUILD_DIR)
