	component model is
		port (
			clk_clk                                           : in    std_logic                     := 'X';             -- clk
			leds_external_connection_export_export            : inout std_logic_vector(31 downto 0) := (others => 'X'); -- export
			reset_reset_n                                     : in    std_logic                     := 'X';             -- reset_n
			sdram_controller_wire_addr                        : out   std_logic_vector(11 downto 0);                    -- addr
			sdram_controller_wire_ba                          : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_controller_wire_cas_n                       : out   std_logic;                                        -- cas_n
			sdram_controller_wire_cke                         : out   std_logic;                                        -- cke
			sdram_controller_wire_cs_n                        : out   std_logic;                                        -- cs_n
			sdram_controller_wire_dq                          : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_controller_wire_dqm                         : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_controller_wire_ras_n                       : out   std_logic;                                        -- ras_n
			sdram_controller_wire_we_n                        : out   std_logic;                                        -- we_n
			sys_sdram_pll_0_sdram_clk_clk                     : out   std_logic;                                        -- clk
			lcd_controller_0_conduit_end_writeresponsevalid_n : out   std_logic;                                        -- writeresponsevalid_n
			lcd_controller_0_conduit_end_data                 : out   std_logic_vector(15 downto 0);                    -- data
			lcd_controller_0_conduit_end_dc                   : out   std_logic;                                        -- dc
			lcd_controller_0_conduit_end_rd                   : out   std_logic;                                        -- rd
			lcd_controller_0_conduit_end_new_signal           : in    std_logic                     := 'X'              -- new_signal
		);
	end component model;

	u0 : component model
		port map (
			clk_clk                                           => CONNECTED_TO_clk_clk,                                           --                             clk.clk
			leds_external_connection_export_export            => CONNECTED_TO_leds_external_connection_export_export,            -- leds_external_connection_export.export
			reset_reset_n                                     => CONNECTED_TO_reset_reset_n,                                     --                           reset.reset_n
			sdram_controller_wire_addr                        => CONNECTED_TO_sdram_controller_wire_addr,                        --           sdram_controller_wire.addr
			sdram_controller_wire_ba                          => CONNECTED_TO_sdram_controller_wire_ba,                          --                                .ba
			sdram_controller_wire_cas_n                       => CONNECTED_TO_sdram_controller_wire_cas_n,                       --                                .cas_n
			sdram_controller_wire_cke                         => CONNECTED_TO_sdram_controller_wire_cke,                         --                                .cke
			sdram_controller_wire_cs_n                        => CONNECTED_TO_sdram_controller_wire_cs_n,                        --                                .cs_n
			sdram_controller_wire_dq                          => CONNECTED_TO_sdram_controller_wire_dq,                          --                                .dq
			sdram_controller_wire_dqm                         => CONNECTED_TO_sdram_controller_wire_dqm,                         --                                .dqm
			sdram_controller_wire_ras_n                       => CONNECTED_TO_sdram_controller_wire_ras_n,                       --                                .ras_n
			sdram_controller_wire_we_n                        => CONNECTED_TO_sdram_controller_wire_we_n,                        --                                .we_n
			sys_sdram_pll_0_sdram_clk_clk                     => CONNECTED_TO_sys_sdram_pll_0_sdram_clk_clk,                     --       sys_sdram_pll_0_sdram_clk.clk
			lcd_controller_0_conduit_end_writeresponsevalid_n => CONNECTED_TO_lcd_controller_0_conduit_end_writeresponsevalid_n, --    lcd_controller_0_conduit_end.writeresponsevalid_n
			lcd_controller_0_conduit_end_data                 => CONNECTED_TO_lcd_controller_0_conduit_end_data,                 --                                .data
			lcd_controller_0_conduit_end_dc                   => CONNECTED_TO_lcd_controller_0_conduit_end_dc,                   --                                .dc
			lcd_controller_0_conduit_end_rd                   => CONNECTED_TO_lcd_controller_0_conduit_end_rd,                   --                                .rd
			lcd_controller_0_conduit_end_new_signal           => CONNECTED_TO_lcd_controller_0_conduit_end_new_signal            --                                .new_signal
		);

