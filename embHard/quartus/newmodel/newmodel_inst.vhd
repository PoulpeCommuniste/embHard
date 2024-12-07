	component newmodel is
		port (
			clk_clk                              : in    std_logic                     := 'X';             -- clk
			dma_controller_0_conduit_end_d_c_n   : out   std_logic;                                        -- d_c_n
			dma_controller_0_conduit_end_wr_n    : out   std_logic;                                        -- wr_n
			dma_controller_0_conduit_end_data    : out   std_logic_vector(15 downto 0);                    -- data
			gpio_controller_0_conduit_end_export : inout std_logic_vector(31 downto 0) := (others => 'X'); -- export
			reset_reset_n                        : in    std_logic                     := 'X';             -- reset_n
			sdram_controller_wire_addr           : out   std_logic_vector(11 downto 0);                    -- addr
			sdram_controller_wire_ba             : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_controller_wire_cas_n          : out   std_logic;                                        -- cas_n
			sdram_controller_wire_cke            : out   std_logic;                                        -- cke
			sdram_controller_wire_cs_n           : out   std_logic;                                        -- cs_n
			sdram_controller_wire_dq             : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_controller_wire_dqm            : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_controller_wire_ras_n          : out   std_logic;                                        -- ras_n
			sdram_controller_wire_we_n           : out   std_logic;                                        -- we_n
			sys_sdram_pll_0_sdram_clk_clk        : out   std_logic                                         -- clk
		);
	end component newmodel;

	u0 : component newmodel
		port map (
			clk_clk                              => CONNECTED_TO_clk_clk,                              --                           clk.clk
			dma_controller_0_conduit_end_d_c_n   => CONNECTED_TO_dma_controller_0_conduit_end_d_c_n,   --  dma_controller_0_conduit_end.d_c_n
			dma_controller_0_conduit_end_wr_n    => CONNECTED_TO_dma_controller_0_conduit_end_wr_n,    --                              .wr_n
			dma_controller_0_conduit_end_data    => CONNECTED_TO_dma_controller_0_conduit_end_data,    --                              .data
			gpio_controller_0_conduit_end_export => CONNECTED_TO_gpio_controller_0_conduit_end_export, -- gpio_controller_0_conduit_end.export
			reset_reset_n                        => CONNECTED_TO_reset_reset_n,                        --                         reset.reset_n
			sdram_controller_wire_addr           => CONNECTED_TO_sdram_controller_wire_addr,           --         sdram_controller_wire.addr
			sdram_controller_wire_ba             => CONNECTED_TO_sdram_controller_wire_ba,             --                              .ba
			sdram_controller_wire_cas_n          => CONNECTED_TO_sdram_controller_wire_cas_n,          --                              .cas_n
			sdram_controller_wire_cke            => CONNECTED_TO_sdram_controller_wire_cke,            --                              .cke
			sdram_controller_wire_cs_n           => CONNECTED_TO_sdram_controller_wire_cs_n,           --                              .cs_n
			sdram_controller_wire_dq             => CONNECTED_TO_sdram_controller_wire_dq,             --                              .dq
			sdram_controller_wire_dqm            => CONNECTED_TO_sdram_controller_wire_dqm,            --                              .dqm
			sdram_controller_wire_ras_n          => CONNECTED_TO_sdram_controller_wire_ras_n,          --                              .ras_n
			sdram_controller_wire_we_n           => CONNECTED_TO_sdram_controller_wire_we_n,           --                              .we_n
			sys_sdram_pll_0_sdram_clk_clk        => CONNECTED_TO_sys_sdram_pll_0_sdram_clk_clk         --     sys_sdram_pll_0_sdram_clk.clk
		);

