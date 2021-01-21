MKDV_MK:=$(abspath $(lastword $(MAKEFILE_LIST)))
TEST_DIR:=$(dir $(MKDV_MK))
MKDV_TOOL ?= icestorm

TOP_MODULE = fwpic

include $(TEST_DIR)/../common/defs_rules.mk

RULES := 1


include $(TEST_DIR)/../common/defs_rules.mk
