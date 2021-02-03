
FWPIC_RTLDIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

ifneq (1,$(RULES))

ifeq (,$(findstring $(FWPIC_RTLDIR),$(MKDV_INCLUDED_DEFS)))
MKDV_INCLUDED_DEFS += $(FWPIC_RTLDIR)
MKDV_VL_INCDIR += $(FWPIC_RTLDIR)
MKDV_VL_SRCS += $(wildcard $(FWPIC_RTLDIR)/*.v)
endif

else # Rules

endif
