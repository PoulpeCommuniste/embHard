
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity DMA_LCD_ctrl is
	GENERIC(SIZEOFINT16 : integer := 16;
			SIZEOFINT32 : integer := 32;
			SIZEOFAVALONADD : integer := 3
	);
	port (
		clk_i               : in    std_logic                    ;
		reset_i             : in    std_logic                    ;
		-- master interface
 		master_address_o	  : out  std_logic_vector(SIZEOFINT32-1 downto 0);
		master_read_o	  : out std_logic;
		master_readdata_i	  : in std_logic_vector(SIZEOFINT16-1 downto 0) ;
		master_waitrequest_i : in std_logic;
		-- IRQ generation
		end_of_transaction_irq_o : out std_logic;
		-- slave interface 
		avalon_address_i    : in    std_logic_vector(SIZEOFAVALONADD-1 downto 0) ;
		avalon_cs_i         : in    std_logic                   ;
		avalon_wr_i         : in    std_logic                    ;
		avalon_write_data_i : in    std_logic_vector(SIZEOFINT32-1 downto 0);
		avalon_rd_i         : in    std_logic                    ;
		avalon_read_data_o  : out    std_logic_vector(SIZEOFINT32-1 downto 0);
		avalon_waitrequest_o: out    std_logic ;
		-- LCD interface
		LCD_data_o          : out std_logic_vector(SIZEOFINT16-1 downto 0) ;
		LCD_WR_n_o	  : out    std_logic ;
		LCD_D_C_n_o	  : out    std_logic
	);
end entity DMA_LCD_ctrl;

architecture rtl of DMA_LCD_ctrl is
-- your signals
	-- avalon slave sig output
	signal avalon_waitrequest_s: std_logic;
    -- 8080 sig output
	signal LCD_data_s : std_logic_vector(SIZEOFINT16-1 downto 0) ;
	signal LCD_WR_n_s: std_logic;
	signal LCD_D_C_n_s: std_logic;
	--LCD sig
	-- State of the state machine
	type state_t is (idle,S1, S2);
	type DMA_state_t is (DMA_idle,DMA_S1,DMA_WRITE,DMA_ACK_END_TRANSFERT,DMA_GOT_ACK);
	signal DMA_Current_state : DMA_state_t := DMA_idle;
	signal DMA_New_state : DMA_state_t := DMA_idle ;
	signal Current_state : state_t := idle;
	signal New_state : state_t:=idle ;
	signal Data_s : std_logic_vector (SIZEOFINT16-1 DOWNTO 0);
	signal DC_n_s : std_logic;
	-- offset DMA reading
	signal offset : integer := 0;
	-- Register DMA
	signal writeaddress_reg_s  : std_logic_vector(SIZEOFINT32-1 downto 0);
	signal lenght_reg_s  : std_logic_vector(SIZEOFINT32-1 downto 0);
	signal control_reg_s  : std_logic_vector(SIZEOFINT32-1 downto 0);
	-- Buffer DMA
	signal current_writeaddress_reg_s  : std_logic_vector(SIZEOFINT32-1 downto 0);
	-- Register DMA address
	constant WRITECOMMAND_ADDR   : std_logic_vector(SIZEOFAVALONADD-1 downto 0)  := "000";
	constant WRITEDATA_ADDR   : std_logic_vector(SIZEOFAVALONADD-1 downto 0)  := "001";
	constant WRITEADDRESS_ADDR   : std_logic_vector(SIZEOFAVALONADD-1 downto 0)  := "010";
	constant LENGTH_ADDR   : std_logic_vector(SIZEOFAVALONADD-1 downto 0)  := "011";
	constant CONTROL_ADDR   : std_logic_vector(SIZEOFAVALONADD-1 downto 0)  := "110";

begin
-------- register model (a proposal) -----------
-- 000 write command to LCD
-- 001 write data to LCD
-- 010 write pointer of the image to copy
-- 011 write size of the image to copy
-- 100 control register 
--	bit 0 => start transfer 
--	bit 1 => reserved 
--	bit 2 => IRQ ack 


-- your code
			--================= Avalon slave ==========================
	Write_Avalon : process(clk_i)
	begin
		if rising_edge(clk_i) then
			if reset_i = '1' then
				writeaddress_reg_s <= (others => '0');
				lenght_reg_s <= (others => '0');
				control_reg_s <= (others => '0');
			else
				if avalon_cs_i = '1' and avalon_wr_i = '1' then
					case avalon_address_i is
						when WRITECOMMAND_ADDR =>
							LCD_D_C_n_s <= '1';
						when WRITEDATA_ADDR =>
							LCD_D_C_n_s <= '0';
						when WRITEADDRESS_ADDR =>
							writeaddress_reg_s <= avalon_write_data_i;
						when LENGTH_ADDR =>
							lenght_reg_s <= avalon_write_data_i;
						when CONTROL_ADDR =>
							control_reg_s <= avalon_write_data_i;
						when others =>
							writeaddress_reg_s <= writeaddress_reg_s;
							lenght_reg_s <= lenght_reg_s;
							control_reg_s <= control_reg_s;
					end case;
				end if;
			end if;
		end if;

	end process;

	Read_Avalon : process(clk_i)
	begin
		if rising_edge(clk_i) then
			if reset_i = '0' then
				if avalon_cs_i = '1' and avalon_rd_i = '1' then
					case avalon_address_i is
						when WRITECOMMAND_ADDR =>
							avalon_read_data_o(0) <= LCD_D_C_n_s;
						when WRITEDATA_ADDR =>
							avalon_read_data_o(0) <= LCD_D_C_n_s;
						when WRITEADDRESS_ADDR =>
							avalon_read_data_o <= writeaddress_reg_s;
						when LENGTH_ADDR =>
							avalon_read_data_o <= lenght_reg_s;
						when CONTROL_ADDR =>
							avalon_read_data_o <= control_reg_s;
						when others =>
							avalon_read_data_o <= (others => '0');
					end case;
				end if;
			end if;
		end if;

	end process;
			--================= DMA process ==========================
	DMA_STATE_MACHINE: process(clk_i) -- c est douteux tout ça
	begin
		if rising_edge(clk_i) then
			if reset_i = '1' then -- resest output who doesn't set by a register or doesn't have a default value
				master_read_o <= '0';
				end_of_transaction_irq_o <= '0';
				DMA_New_state <= DMA_idle;
			else
				case DMA_Current_state is
					when DMA_idle =>
						if control_reg_s(0) = '1' then -- bit 0 => start transfer
							DMA_New_state <= DMA_S1;
						end if;
					when DMA_S1 =>
						LCD_D_C_n_s <= '1'; -- set the bit for a data
						master_address_o  <= current_writeaddress_reg_s; -- set the new address who will be read by the DMA
						master_read_o  <= '1';
						if master_waitrequest_i <= '0'then -- wait for the end of the read and write to the LCD
							DMA_New_state <= DMA_WRITE;
						end if;
						offset <= offset + SIZEOFINT16; -- count for the future address
						if to_unsigned(offset,SIZEOFINT32)  >  unsigned(lenght_reg_s) then -- watch if we read all the data
							DMA_New_state <= DMA_ACK_END_TRANSFERT;
						end if;
					when DMA_WRITE =>

						DMA_New_state <= DMA_S1;
					when DMA_ACK_END_TRANSFERT =>
						end_of_transaction_irq_o <= '1'; -- acknowledge the cpu of the end of the transfert
						if control_reg_s(2) = '1' then -- wait for the ack of the cpu and set all to 0 for the future transfert
							DMA_New_state <= DMA_GOT_ACK;
						end if;
					when DMA_GOT_ACK =>
						end_of_transaction_irq_o <= '0';
						offset <= 0;
						--control_reg_s <= (others => '0');
						DMA_New_state <= DMA_idle;
					when others =>
						DMA_New_state <= DMA_idle;
				end case;
			end if;
		end if;
	end process;
	current_writeaddress_reg_s <= std_logic_vector(unsigned(writeaddress_reg_s)+to_unsigned(offset,SIZEOFINT32)); -- set the new adrress with the offset
			--================= LCD process ==========================
	LCD_proc:process(clk_i)
		begin
			if rising_edge(clk_i) then
				if reset_i = '1' then
					LCD_data_s <= (others => '0');
					LCD_D_C_n_s <= '0';
					New_state <= idle;
				else
					if control_reg_s(0) = '0' then  -- LCD got the control
						case Current_state is
							when idle =>
								if DMA_Current_state = DMA_WRITE then -- wait for the end of the read and write to the LCD
									LCD_data_s	<= master_readdata_i;

								else
									LCD_data_s <= avalon_write_data_i(15 downto 0);
								end if;
								avalon_waitrequest_s <= '1';
								LCD_WR_n_s <= '1';

								if avalon_wr_i = '1' and avalon_cs_i = '1' then
									New_state <= S1;
								end if;
							when S1 =>
								avalon_waitrequest_s <= '1';
								LCD_WR_n_s <= '0';
								New_state <= S2;
							when S2 =>
								avalon_waitrequest_s <= '0';
								New_state <= idle;
							when others => null;
						end case;
					end if;
				end if;
			end if;
		end process;
	--change state machine
	Current_state <= New_state;
	DMA_Current_state <= DMA_New_state;
	-- slave interface output
	avalon_waitrequest_o <=avalon_waitrequest_s;
	-- 8080 output
	LCD_WR_n_o <= LCD_WR_n_s;
	LCD_data_o <= LCD_data_s;
	LCD_D_C_n_o <= LCD_D_C_n_s;
end architecture rtl; 
