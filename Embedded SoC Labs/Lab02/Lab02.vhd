-------------------------------------------------------------------------------    
--   University: Oregon Institute of Technology – CSET Department
--   Class: CST 455
--   Author: Cameron Robinson
--   Lab: 2
--   Project: VHDL Intro Lab
--   File Name: Lab02.vhd
--   List of other files used: Hex_to_7Seg.vhd, Four_Bit_Adder.vhd
-------------------------------------------------------------------------------    
--   Numbers are entered through SW[7-4] and SW[3-0] as hexidecimal values.
--   These values are displayed on HEX4 and HEX2. The values are also added together
--   and the result is displayed on HEX0 and HEX1.
-------------------------------------------------------------------------------    
--   Date: 10/11/2023
--   Version: 1.0
--   Revision: 10/12/2023 Initial and final version
-------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use work.all;

entity Lab02 is
	port (
			in1	: in std_logic_vector (3 downto 0);
			in2	: in std_logic_vector (3 downto 0);
			HEX0	: out std_logic_vector (6 downto 0);
			HEX1	: out std_logic_vector (6 downto 0);
			HEX2	: out std_logic_vector (6 downto 0);
			HEX4	: out std_logic_vector (6 downto 0)
	);
end Lab02;

architecture struct of Lab02 is
	component Four_Bit_Adder is
		port(
				num1		: in std_logic_vector(3 downto 0);
				num2		: in std_logic_vector(3 downto 0);
				out1	: out std_logic_vector(3 downto 0);
				out2	: out std_logic_vector(3 downto 0)
		);
	end component;
	
	component Hex_to_7Seg is
		port(
				num	: in std_logic_vector (3 downto 0);
				seg	: out std_logic_vector (6 downto 0)
		);
	end component;

	--------------------------------------------------
	--				   Signal Declarations              --
	--------------------------------------------------
	
	signal lsb_wires : std_logic_vector (3 downto 0); --Wires to carry least significant bits of sum
	signal msb_wires : std_logic_vector (3 downto 0); --Wires to carry most significant bits of sum
	
begin

	U1: Four_Bit_Adder port map(num1=>in1, num2=>in2, out1=>lsb_wires, out2=>msb_wires);
	U2: Hex_to_7Seg port map(num=>in1, seg=>HEX4);
	U3: Hex_to_7Seg port map(num=>in2, seg=>HEX2);
	U4: Hex_to_7Seg port map(num=>lsb_wires, seg=>HEX0);
	U5: Hex_to_7Seg port map(num=>msb_wires, seg=>HEX1);
	
end struct;