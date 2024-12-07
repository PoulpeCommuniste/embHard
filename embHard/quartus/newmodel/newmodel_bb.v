
module newmodel (
	clk_clk,
	dma_controller_0_conduit_end_d_c_n,
	dma_controller_0_conduit_end_wr_n,
	dma_controller_0_conduit_end_data,
	gpio_controller_0_conduit_end_export,
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
	sys_sdram_pll_0_sdram_clk_clk);	

	input		clk_clk;
	output		dma_controller_0_conduit_end_d_c_n;
	output		dma_controller_0_conduit_end_wr_n;
	output	[15:0]	dma_controller_0_conduit_end_data;
	inout	[31:0]	gpio_controller_0_conduit_end_export;
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
endmodule
