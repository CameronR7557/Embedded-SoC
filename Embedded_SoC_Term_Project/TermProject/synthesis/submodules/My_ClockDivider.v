//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 231 and CST 455
//   Author: Cameron Robinson
//   Project: Term Project
//   File Name: My_ClockDivider.v
//   List of other files used: none
//-----------------------------------------------------------------------------    
//   Description of the Code (1 - 5 lines)
//   The clock divider takes in a clock signal and a reset signal and outputs a divided clock signal.
//	  Allows writing to the module to set how much to divide the clock
//   (i.e., div = 12500 will divide the clock by 25000. For a 50MHz clock, this will divide it to 2kHz ).
//-----------------------------------------------------------------------------    
//   Date: 01/19/2022
//   Version: 1.0
//   Revision:
// 01/19/2022 Initial version
// 02/09/2022 Changed the count value to be able to hold higher values
// 11/9/2023  Wrapped in an Avalon Slave. Changed parameter into a writable reg.
//-----------------------------------------------------------------------------

module My_ClockDivider
(
	input clk,
	input reset_n,
	input chipselect,
	input [1:0] address,
	input write,
	input [31:0] writedata,
	output reg clk_out
);

	reg [24:0] count; 								//Register to count input clock edges
	reg [24:0] div = 25'd6;						   //Register to divide clock
	
	always @(posedge clk or negedge reset_n)
		begin
			if(~reset_n)
				begin
					count <= 25'b0;
					div <= div;
				end
			else if(chipselect && write && (address == 2'b00))
				begin
					count <= 25'b0;
					div <= writedata[24:0];
				end
			else if(count < div - 1)
				begin
					count <= count + 1'b1;
					div <= div;
				end
			else
				begin
					count <= 25'b0;
					div <= div;
				end
		end
		
		
	
	always @(posedge clk or negedge reset_n)
		begin
			if(~reset_n)
				begin
					clk_out <= 1'b0;
				end
			else if(count == div - 1)
				begin
					clk_out <= ~clk_out;
				end
			else
				begin
					clk_out <= clk_out;
				end
		end
		
		
endmodule 