
DV_COMMON_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
PACKAGES_DIR := $(abspath $(DV_COMMON_DIR)/../../../packages)
RTL_DIR := $(abspath $(DV_COMMON_DIR)/../../rtl)
DV_MK := $(shell $(PACKAGES_DIR)/python/bin/python -m mkdv mkfile)

ifneq (1,$(RULES))

MKDV_VL_INCDIRS += $(PACKAGES_DIR)/fwprotocol-defs/src/sv
MKDV_VL_SRCS += $(RTL_DIR)/fwpic.v
MKDV_VL_SRCS += $(abspath $(dir $(DV_MK)))/../include/resetgen.sv

include $(DV_MK)

else # Rules

include $(DV_MK)
endif