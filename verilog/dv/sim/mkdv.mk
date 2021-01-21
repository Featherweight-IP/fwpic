MKDV_MK:=$(abspath $(lastword $(MAKEFILE_LIST)))
TEST_DIR:=$(dir $(MKDV_MK))
MKDV_TOOL ?= icarus

MKDV_VL_SRCS += $(TEST_DIR)/fwpic_tb.sv
TOP_MODULE = fwpic_tb

MKDV_PLUGINS += pybfms cocotb
PYBFMS_MODULES += rv_bfms

#MKDV_COCOTB_MODULE


include $(TEST_DIR)/../common/defs_rules.mk

RULES := 1


include $(TEST_DIR)/../common/defs_rules.mk
