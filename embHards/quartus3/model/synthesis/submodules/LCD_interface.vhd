library ieee ;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

ENTITY LCD_interface IS
GENERIC(
Size_data : integer := 15;
Size_IMO : integer := 4
);
PORT(
-- Avalon interfaces signals
Clk_i : IN std_logic;
nReset_i : IN std_logic;
Address_i : IN std_logic;
Data_i : IN std_logic_vector (Size_data-1 DOWNTO 0);
Av_write_i : IN std_logic;
Av_chipselect_i : IN std_logic;
--
Wait_request_o: OUT std_logic;

-- 8080 interface
Data_o : OUT std_logic_vector (Size_data-1 DOWNTO 0);
DC_n_o : OUT std_logic;
--CS_n_o : OUT std_logic; --  Active GPIO
WR_n_o : OUT std_logic
RD_n_o : OUT std_logic;
--Reset_n_o : OUT std_logic; -- Active by GPIO
IMO_o : OUT std_logic_vector (Size_IMO-1 DOWNTO 0);

);
End LCD_interface;
architecture comp OF LCD_interface IS
type state_t is (idle, S1, S2); -- State of the state machine
signal Current_state : state_t;
signal New_state : state_t;
signal Data_s : std_logic_vector (Size_data-1 DOWNTO 0);
signal DC_n_s : std_logic;

BEGIN

process(Clk_i)
begin
    if rising_edge(Clk_i) then
        if nReset_i = '0' then
            Data_s <= (others => '0');
            DC_n_s <= '0';
            New_state <= idle;
        else
        Data_s <= Data_i;
        DC_n_s <= Address_i;
            if Av_chipselect_i = '1' and Av_write_i = '1' then -- Write cycle
                case Current_state is
                    when idle =>
                        Wait_request_o <= '1';
                        WR_n_o <= '1';
                        if Av_write_i = '1' and Av_chipselect_i = '1' then
                            New_state <= S1;
                        end if;
                    when S1 =>
                        Wait_request_o <= '1';
                        WR_n_o <= '0';
                        New_state <= S2;
                    when S2 =>
                        Wait_request_o <= '0';
                        New_state <= idle;
                    when others => null;
                end case;
            end if;
        end if;
    end if;
end process;

-- Parallel Port Input value
Data_o<=Data_s;
DC_n_o<=DC_n_s;
IMO <= '1000'
RD_n <='1';
Current_state <= New_state;
end comp;
