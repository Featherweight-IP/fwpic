/****************************************************************************
 * fwpic_tb.sv
 ****************************************************************************/

`ifdef NEED_TIMESCALE
`timescale 1ns/1ns
`endif

`include "rv_addr_line_en_macros.svh"
  
/**
 * Module: fwpic_tb
 * 
 * TODO: Add module documentation
 */
module fwpic_tb(input clock);

	wire reset;
	
`ifdef HAVE_HDL_CLOCKGEN
	reg clk_r = 0;
	initial begin
		forever begin
`ifdef NEED_TIMESCALE			
			#10;
`else
			#10ns;
`endif
			clk_r <= ~clk_r;
		end
	end
`endif
	
`ifdef IVERILOG
	`include "iverilog_control.svh"
`endif
	
	resetgen u_rstgen(
			.clock(clock),
			.reset(reset)
		);
	
	
	
	`RV_ADDR_LINE_EN_WIRES(bfm2dut_, 4, 32);
	
	rv_addr_line_en_initiator_bfm #(
			.ADR_WIDTH(4),
			.DAT_WIDTH(32)
		) u_bfm (
			.clock(clock),
			.reset(reset),
			`RV_ADDR_LINE_EN_CONNECT(, bfm2dut_)
		);
	
	fwpic #(
		.N_IRQ  (8 )
		) fwpic (
		.clock  (clock ), 
		.reset  (reset ), 
		`RV_ADDR_LINE_EN_CONNECT(, bfm2dut_)
		);

endmodule


