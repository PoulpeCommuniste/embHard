
module model (
	clk_clk,
	leds_external_connection_export_export,
	reset_reset_n,
	sdram_controller_wire_addr,
	sdram_controller_wire_ba,
	sdram_controller_wire_cas_n,
	sdram_controller_wire_cke,
	sdram_controller_wire_cs_n,
	sdram_controller_wire_dq,
	sdram_controller_wire_dqm,
	sdram_controller_wire_ras_n,
	sdram_controller_wire_we_n,
	sys_sdram_pll_0_sdram_clk_clk,
	lcd_controller_0_conduit_end_writeresponsevalid_n,
	lcd_controller_0_conduit_end_data,
	lcd_controller_0_conduit_end_dc,
	lcd_controller_0_conduit_end_rd,
	lcd_controller_0_conduit_end_new_signal);	

	input		clk_clk;
	inout	[31:0]	leds_external_connection_export_export;
	input		reset_reset_n;
	output	[11:0]	sdram_controller_wire_addr;
	output	[1:0]	sdram_controller_wire_ba;
	output		sdram_controller_wire_cas_n;
	output		sdram_controller_wire_cke;
	output		sdram_controller_wire_cs_n;
	inout	[15:0]	sdram_controller_wire_dq;
	output	[1:0]	sdram_controller_wire_dqm;
	output		sdram_controller_wire_ras_n;
	output		sdram_controller_wire_we_n;
	output		sys_sdram_pll_0_sdram_clk_clk;
	output		lcd_controller_0_conduit_end_writeresponsevalid_n;
	output	[15:0]	lcd_controller_0_conduit_end_data;
	output		lcd_controller_0_conduit_end_dc;
	output		lcd_controller_0_conduit_end_rd;
	input		lcd_controller_0_conduit_end_new_signal;
endmodule
