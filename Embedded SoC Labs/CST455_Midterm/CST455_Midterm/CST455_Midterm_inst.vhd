	component CST455_Midterm is
		port (
			clk_clk            : in    std_logic                     := 'X';             -- clk
			hex0_export        : out   std_logic_vector(6 downto 0);                     -- export
			hex1_export        : out   std_logic_vector(6 downto 0);                     -- export
			hex2_export        : out   std_logic_vector(6 downto 0);                     -- export
			hex3_export        : out   std_logic_vector(6 downto 0);                     -- export
			hex4_export        : out   std_logic_vector(6 downto 0);                     -- export
			hex5_export        : out   std_logic_vector(6 downto 0);                     -- export
			leds_export        : out   std_logic_vector(9 downto 0);                     -- export
			pushbuttons_export : in    std_logic_vector(3 downto 0)  := (others => 'X'); -- export
			sdram_clk_clk      : out   std_logic;                                        -- clk
			sdram_wire_addr    : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba      : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n   : out   std_logic;                                        -- cas_n
			sdram_wire_cke     : out   std_logic;                                        -- cke
			sdram_wire_cs_n    : out   std_logic;                                        -- cs_n
			sdram_wire_dq      : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm     : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_wire_ras_n   : out   std_logic;                                        -- ras_n
			sdram_wire_we_n    : out   std_logic;                                        -- we_n
			sw_export          : in    std_logic_vector(9 downto 0)  := (others => 'X')  -- export
		);
	end component CST455_Midterm;

	u0 : component CST455_Midterm
		port map (
			clk_clk            => CONNECTED_TO_clk_clk,            --         clk.clk
			hex0_export        => CONNECTED_TO_hex0_export,        --        hex0.export
			hex1_export        => CONNECTED_TO_hex1_export,        --        hex1.export
			hex2_export        => CONNECTED_TO_hex2_export,        --        hex2.export
			hex3_export        => CONNECTED_TO_hex3_export,        --        hex3.export
			hex4_export        => CONNECTED_TO_hex4_export,        --        hex4.export
			hex5_export        => CONNECTED_TO_hex5_export,        --        hex5.export
			leds_export        => CONNECTED_TO_leds_export,        --        leds.export
			pushbuttons_export => CONNECTED_TO_pushbuttons_export, -- pushbuttons.export
			sdram_clk_clk      => CONNECTED_TO_sdram_clk_clk,      --   sdram_clk.clk
			sdram_wire_addr    => CONNECTED_TO_sdram_wire_addr,    --  sdram_wire.addr
			sdram_wire_ba      => CONNECTED_TO_sdram_wire_ba,      --            .ba
			sdram_wire_cas_n   => CONNECTED_TO_sdram_wire_cas_n,   --            .cas_n
			sdram_wire_cke     => CONNECTED_TO_sdram_wire_cke,     --            .cke
			sdram_wire_cs_n    => CONNECTED_TO_sdram_wire_cs_n,    --            .cs_n
			sdram_wire_dq      => CONNECTED_TO_sdram_wire_dq,      --            .dq
			sdram_wire_dqm     => CONNECTED_TO_sdram_wire_dqm,     --            .dqm
			sdram_wire_ras_n   => CONNECTED_TO_sdram_wire_ras_n,   --            .ras_n
			sdram_wire_we_n    => CONNECTED_TO_sdram_wire_we_n,    --            .we_n
			sw_export          => CONNECTED_TO_sw_export           --          sw.export
		);

