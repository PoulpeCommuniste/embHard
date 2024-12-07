
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
	lcd_dma_ctrl_0_conduit_end_lcd_d_c_n,
	lcd_dma_ctrl_0_conduit_end_lcd_wr_n,
	lcd_dma_ctrl_0_conduit_end_lcd_data,
	sram_clk_clk);	

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
	output		lcd_dma_ctrl_0_conduit_end_lcd_d_c_n;
	output		lcd_dma_ctrl_0_conduit_end_lcd_wr_n;
	output	[15:0]	lcd_dma_ctrl_0_conduit_end_lcd_data;
	output		sram_clk_clk;
endmodule
