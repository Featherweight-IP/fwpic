/*
 * fw_pic.h
 *
 *  Created on: Feb 1, 2021
 *      Author: mballance
 */

#ifndef INCLUDED_FW_PIC_H
#define INCLUDED_FW_PIC_H
#include <stdint.h>

typedef struct fw_pic_regs_s {
	// 0 - level-triggered
	// 1 - edge-triggered
	uint32_t			edge_en;

	// 0 - active-low
	// 1 - active-high
	uint32_t			polarity;

	// 0 - not masked (enabled)
	// 1 - masked (disabled)
	uint32_t			mask;

	// 0 - not pending
	// 1 - pending
	//
	// Clear by writing a '1' to the desired bits
	uint32_t			pending;

} fw_pic_regs_t;



#endif /* INCLUDED_FW_PIC_H */
