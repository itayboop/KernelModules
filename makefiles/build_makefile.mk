# Kernel build dir
KDIR ?= /lib/modules/6.14.0-24-generic/build
BUILD_DIR ?= build
TARGET := $(SRC_DIR)/$(MODULE_NAME).o
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

obj-m := $(TARGET)

all:
	mkdir -p $(BUILD_DIR)
	echo "obj-m := $(MODULE_NAME).o" > $(BUILD_DIR)/Makefile
	echo "INCLUDE := $(INCLUDE)" >> $(BUILD_DIR)/Makefile
	echo "SRC_DIR := $(SRC_DIR)" >> $(BUILD_DIR)/Makefile
	echo 'ccflags-y += -I$${SRC_DIR} $${INCLUDE}' >> $(BUILD_DIR)/Makefile
	cp $(INCLUDE) -r $(BUILD_DIR)/ 2>/dev/null || true
	cp $(SRC_DIR)/*.c $(BUILD_DIR)/ 2>/dev/null || true
	cp $(SRC_DIR)/*.h $(BUILD_DIR)/ 2>/dev/null || true

	$(MAKE) -C $(KDIR) M=$(PWD)/$(BUILD_DIR) $(EXTRA_KERNEL_SYM) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD)/$(BUILD_DIR) clean
	@rm -rf $(BUILD_DIR)
