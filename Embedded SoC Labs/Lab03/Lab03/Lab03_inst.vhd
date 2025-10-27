	component Lab03 is
		port (
			clk_clk         : in  std_logic                    := 'X';             -- clk
			hex0_export     : out std_logic_vector(6 downto 0);                    -- export
			hex1_export     : out std_logic_vector(6 downto 0);                    -- export
			hex2_export     : out std_logic_vector(6 downto 0);                    -- export
			switches_export : in  std_logic_vector(9 downto 0) := (others => 'X')  -- export
		);
	end component Lab03;

	u0 : component Lab03
		port map (
			clk_clk         => CONNECTED_TO_clk_clk,         --      clk.clk
			hex0_export     => CONNECTED_TO_hex0_export,     --     hex0.export
			hex1_export     => CONNECTED_TO_hex1_export,     --     hex1.export
			hex2_export     => CONNECTED_TO_hex2_export,     --     hex2.export
			switches_export => CONNECTED_TO_switches_export  -- switches.export
		);

