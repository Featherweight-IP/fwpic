/*
 * fw_pic.c
 *
 *  Created on: Feb 1, 2021
 *      Author: mballance
 */

#define DT_DRV_COMPAT fw_pic

#include <device.h>
#include <irq_nextlevel.h>
#include "fw_pic.h"

static int fw_pic_init(const struct device *dev) {
	fw_pic_regs_t *regs = (fw_pic_regs_t *)DT_INST_REG_ADDR(0);

	// Disable all interrupts initially
	sys_write32(0xFFFFFFFF, (mem_addr_t)&regs->mask);

	// Enable level-triggered active-high interrupts
	sys_write32(0x00000000, (mem_addr_t)&regs->edge_en);
	sys_write32(0xFFFFFFFF, (mem_addr_t)&regs->polarity);

	// Clear any pending interrupts just because
	sys_write32(0xFFFFFFFF, (mem_addr_t)&regs->pending);
	return 0;
}

#ifdef CONFIG_MULTI_LEVEL_INTERRUPTS
static void fw_pic_isr(const struct device *dev) {
	fw_pic_regs_t *regs = (fw_pic_regs_t *)DT_INST_REG_ADDR(0);
	uint32_t pending, i;
	int32_t  target = -1;

	// Get pending
	pending = sys_read32((mem_addr_t)&regs->pending);

	for (i=0; i<32; i++) {
		if (pending & (1 << i)) {
			target = i;
		}
	}

	if (target != -1) {
		if (_sw_isr_table[target].isr) {
			_sw_isr_table[target].isr(
					_sw_isr_table[target].arg);

			// Clear pending on the way out
			sys_write32((1 << target), (mem_addr_t)&regs->pending);
		} else {
			printk("Unregistered interrupt fired\n");
		}
	} else {
//		z_irq_spurious(arg)
	}
}
#endif

static inline void fw_pic_intr_enable(
		const struct device *dev,
		uint32_t			irq) {
	printk("fw_pic_intr_enable %d\n", irq);
	fw_pic_regs_t *regs = (fw_pic_regs_t *)DT_INST_REG_ADDR(0);
	uint32_t mask = sys_read32((mem_addr_t)&regs->mask);
	mask &= ~(1 << irq);
	sys_write32(mask, (mem_addr_t)&regs->mask);
}

static inline void fw_pic_intr_disable(
		const struct device *dev,
		uint32_t			irq) {
	printk("fw_pic_intr_disable %d\n", irq);
	fw_pic_regs_t *regs = (fw_pic_regs_t *)DT_INST_REG_ADDR(0);
	uint32_t mask = sys_read32((mem_addr_t)&regs->mask);
	mask |= (1 << irq);
	sys_write32(mask, (mem_addr_t)&regs->mask);
}

static inline unsigned int fw_pic_intr_get_state(
		const struct device *dev,
		uint32_t			irq) {
	return 0;
}

static inline unsigned int fw_pic_intr_get_line_state(
		const struct device *dev,
		uint32_t			irq) {
	return 0;
}



static const struct irq_next_level_api fw_pic_apis = {
		.intr_enable = fw_pic_intr_enable,
		.intr_disable = fw_pic_intr_disable,
		.intr_get_state = fw_pic_intr_get_state,
		.intr_get_line_state = fw_pic_intr_get_line_state
};

#ifndef CONFIG_MULTI_LEVEL_INTERRUPTS
void arch_irq_enable(unsigned int irq) {
	fw_pic_intr_enable(0, irq);
}

void arch_irq_disable(unsigned int irq) {
	fw_pic_intr_disable(0, irq);
};

int arch_irq_is_enabled(unsigned int irq) {
	return fw_pic_intr_get_state(0, irq);
}

unsigned int __soc_handle_irq(int cause) {
	fw_pic_regs_t *regs = (fw_pic_regs_t *)DT_INST_REG_ADDR(0);
	uint32_t pending, i;

	// Get pending
	pending = sys_read32((mem_addr_t)&regs->pending);

	for (i=0; i<32; i++) {
		if (pending & (1 << i)) {
			return i;
		}
	}

	// TODO:
	return -1;
}

#endif

typedef struct fw_pic_config_s {
} fw_pic_config_t;

static fw_pic_config_t fw_pic_config = {
};

static void fw_pic_config_irq(const struct device *dev);

DEVICE_AND_API_INIT(fw_pic_ictl, DT_INST_LABEL(0),
		fw_pic_init, NULL, &fw_pic_config,
		PRE_KERNEL_1, 0, &fw_pic_apis);
// SYS_INIT(fw_pic_init, PRE_KERNEL_1, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT);

static void fw_pic_config_irq(const struct device *dev) {
	/*
	IRQ_CONNECT(
			DT_INST_IRQN(0),
			DT_INST_IRQ(0, priority),
			fw_pic_isr,
			DEVICE_GET(fw_pic_ictl),
			DT_INST_IRQ(0, sense)); // Architecture IRQ
//			DT_INST_IRQ(0, sense));
	 */
}

