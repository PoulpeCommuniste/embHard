	newmodel u0 (
		.clk_clk                              (<connected-to-clk_clk>),                              //                           clk.clk
		.dma_controller_0_conduit_end_d_c_n   (<connected-to-dma_controller_0_conduit_end_d_c_n>),   //  dma_controller_0_conduit_end.d_c_n
		.dma_controller_0_conduit_end_wr_n    (<connected-to-dma_controller_0_conduit_end_wr_n>),    //                              .wr_n
		.dma_controller_0_conduit_end_data    (<connected-to-dma_controller_0_conduit_end_data>),    //                              .data
		.gpio_controller_0_conduit_end_export (<connected-to-gpio_controller_0_conduit_end_export>), // gpio_controller_0_conduit_end.export
		.reset_reset_n                        (<connected-to-reset_reset_n>),                        //                         reset.reset_n
		.sdram_controller_wire_addr           (<connected-to-sdram_controller_wire_addr>),           //         sdram_controller_wire.addr
		.sdram_controller_wire_ba             (<connected-to-sdram_controller_wire_ba>),             //                              .ba
		.sdram_controller_wire_cas_n          (<connected-to-sdram_controller_wire_cas_n>),          //                              .cas_n
		.sdram_controller_wire_cke            (<connected-to-sdram_controller_wire_cke>),            //                              .cke
		.sdram_controller_wire_cs_n           (<connected-to-sdram_controller_wire_cs_n>),           //                              .cs_n
		.sdram_controller_wire_dq             (<connected-to-sdram_controller_wire_dq>),             //                              .dq
		.sdram_controller_wire_dqm            (<connected-to-sdram_controller_wire_dqm>),            //                              .dqm
		.sdram_controller_wire_ras_n          (<connected-to-sdram_controller_wire_ras_n>),          //                              .ras_n
		.sdram_controller_wire_we_n           (<connected-to-sdram_controller_wire_we_n>),           //                              .we_n
		.sys_sdram_pll_0_sdram_clk_clk        (<connected-to-sys_sdram_pll_0_sdram_clk_clk>)         //     sys_sdram_pll_0_sdram_clk.clk
	);

