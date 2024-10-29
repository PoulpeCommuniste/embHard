	model u0 (
		.clk_clk                                (<connected-to-clk_clk>),                                //                             clk.clk
		.lcd_controller_0_conduit_end_wr_n_o    (<connected-to-lcd_controller_0_conduit_end_wr_n_o>),    //    lcd_controller_0_conduit_end.wr_n_o
		.lcd_controller_0_conduit_end_data_o    (<connected-to-lcd_controller_0_conduit_end_data_o>),    //                                .data_o
		.lcd_controller_0_conduit_end_dc_n_o    (<connected-to-lcd_controller_0_conduit_end_dc_n_o>),    //                                .dc_n_o
		.lcd_controller_0_conduit_end_rd_n_o    (<connected-to-lcd_controller_0_conduit_end_rd_n_o>),    //                                .rd_n_o
		.lcd_controller_0_conduit_end_im0_0     (<connected-to-lcd_controller_0_conduit_end_im0_0>),     //                                .im0_0
		.leds_external_connection_export_export (<connected-to-leds_external_connection_export_export>), // leds_external_connection_export.export
		.reset_reset_n                          (<connected-to-reset_reset_n>),                          //                           reset.reset_n
		.sdram_controller_wire_addr             (<connected-to-sdram_controller_wire_addr>),             //           sdram_controller_wire.addr
		.sdram_controller_wire_ba               (<connected-to-sdram_controller_wire_ba>),               //                                .ba
		.sdram_controller_wire_cas_n            (<connected-to-sdram_controller_wire_cas_n>),            //                                .cas_n
		.sdram_controller_wire_cke              (<connected-to-sdram_controller_wire_cke>),              //                                .cke
		.sdram_controller_wire_cs_n             (<connected-to-sdram_controller_wire_cs_n>),             //                                .cs_n
		.sdram_controller_wire_dq               (<connected-to-sdram_controller_wire_dq>),               //                                .dq
		.sdram_controller_wire_dqm              (<connected-to-sdram_controller_wire_dqm>),              //                                .dqm
		.sdram_controller_wire_ras_n            (<connected-to-sdram_controller_wire_ras_n>),            //                                .ras_n
		.sdram_controller_wire_we_n             (<connected-to-sdram_controller_wire_we_n>),             //                                .we_n
		.sys_sdram_pll_0_sdram_clk_clk          (<connected-to-sys_sdram_pll_0_sdram_clk_clk>)           //       sys_sdram_pll_0_sdram_clk.clk
	);

