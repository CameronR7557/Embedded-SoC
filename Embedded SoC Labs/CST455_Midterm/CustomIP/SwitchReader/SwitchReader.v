//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 455
//   Author: Cameron Robinson
//   Lab: Midterm
//   Project: CST 455 Midterm
//   File Name: SwitchReader.v
//   List of other files used: None
//-----------------------------------------------------------------------------    
//   Custom IP for reading SW0-9
//-----------------------------------------------------------------------------    
//   Date:10/28/2023
//   Version: 1.0
//   Revision:
//   10/28/2023 Initial and final version
//-----------------------------------------------------------------------------
module SwitchReader(
	input [1:0] address,
	input chipselect,
	input clk,
	input reset_n,
	input read,
	input [9:0] switch,
	output reg [31:0] readdata
);

always @(posedge clk or negedge reset_n)
begin
	if(reset_n == 1'b0)
	begin
		readdata <= 32'b0;
	end
	else if (read && chipselect && (address == 2'b0))
	begin
		readdata <= switch;
	end
	else
	begin
		readdata <= 32'b0;
	end
end

endmodule