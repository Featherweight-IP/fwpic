
FW_PIC_SWDIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

ifneq (1,$(RULES))

ifeq (,$(findstring $(FW_PIC_SWDIR),$(MKDV_INCLUDED_DEFS)))
MKDV_INCLUDED_DEFS += $(FW_PIC_SWDIR)
ZEPHYR_MODULES += $(FW_PIC_SWDIR)/fw_pic
endif

else # Rules

endif
