-------------------------------------------------------------------------------    
--   University: Oregon Institute of Technology – CSET Department
--   Class: CST 455
--   Author: Cameron Robinson
--   Lab: 2
--   Project: VHDL Intro Lab
--   File Name: Four_Bit_Adder.vhd
--   List of other files used: 
-------------------------------------------------------------------------------    
--   Adds two 4-bit values and outputs the sum.
-------------------------------------------------------------------------------    
--   Date: 10/11/2023
--   Version: 1.0
--   Revision: 10/12/2023 Initial and final version
-------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;--May not need

entity Four_Bit_Adder is
	port(			 
			num1	:	in std_logic_vector(3 downto 0);
			num2	:	in std_logic_vector(3 downto 0);
			out1	:	out std_logic_vector(3 downto 0);
			out2	:	out std_logic_vector(3 downto 0)
	);
end Four_Bit_Adder;

architecture adder of Four_Bit_Adder is
begin
	process(num1, num2)
		variable a : unsigned(4 downto 0);
		variable b : unsigned(4 downto 0);
		variable sum : unsigned(7 downto 0);
	begin
		a := unsigned(('0' & num1));
		b := unsigned(('0' & num2));
		sum := ("000" & (a + b));
		out1 <= std_logic_vector(sum(3 downto 0));
		out2 <= std_logic_vector(sum(7 downto 4));
	end process;
end adder;