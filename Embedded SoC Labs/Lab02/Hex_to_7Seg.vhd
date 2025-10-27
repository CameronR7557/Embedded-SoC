-------------------------------------------------------------------------------    
--   University: Oregon Institute of Technology – CSET Department
--   Class: CST 455
--   Author: Cameron Robinson
--   Lab: 2
--   Project: VHDL Intro Lab
--   File Name: Hex_to_7Seg.vhd
--   List of other files used: 
-------------------------------------------------------------------------------    
--   Decodes a hexidecimal value into values for a common annode 7-segment display.
-------------------------------------------------------------------------------    
--   Date: 10/11/2023
--   Version: 1.0
--   Revision: 10/12/2023 Initial and final version
-------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;

entity Hex_to_7Seg is
	port(
			num	:	in std_logic_vector (3 downto 0);
			seg	:	out std_logic_vector (6 downto 0)
	);
end Hex_to_7Seg;

architecture decoder of Hex_to_7Seg is
begin
	process(num)
	begin
		case num is
			when "0000" => seg <= "1000000";
			when "0001" => seg <= "1111001";
			when "0010" => seg <= "0100100";
			when "0011" => seg <= "0110000";
			when "0100" => seg <= "0011001";
			when "0101" => seg <= "0010010";
			when "0110" => seg <= "0000010";
			when "0111" => seg <= "1111000";
			when "1000" => seg <= "0000000";
			when "1001" => seg <= "0010000";
			when "1010" => seg <= "0001000";
			when "1011" => seg <= "0000011";
			when "1100" => seg <= "1000110";
			when "1101" => seg <= "0100001";
			when "1110" => seg <= "0000110";
			when "1111" => seg <= "0001110";
			when others => seg <= "1111111";
		end case;
	end process;
end decoder;