//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 455
//   Author: Cameron Robinson
//   Lab: Midterm
//   Project: CST 455 Midterm
//   File Name: LEDController.v
//   List of other files used: None
//-----------------------------------------------------------------------------    
//   Custom IP for reading and writing LED0-9
//-----------------------------------------------------------------------------    
//   Date:10/28/2023
//   Version: 1.0
//   Revision:
//   10/28/2023 Initial and final version
//-----------------------------------------------------------------------------

module LEDController(
	input [1:0] address,
	input chipselect,
	input clk,
	input read,
	input reset_n,
	input write,
	input [31:0] writedata,
	output [9:0] led_out,
	output reg [31:0] readdata
);

reg [9:0] data;		//Reg to store LED values

always @(posedge clk or negedge reset_n)
begin
	if(reset_n == 1'b0)
	begin
		data <= 10'b0;
		readdata <= 32'b0;
	end
	else if(chipselect && write && (address == 2'b0))
	begin
		data <= writedata[9:0];
		readdata <= 32'b0;
	end
	else if (chipselect && read && (address == 2'b0))
	begin
		readdata <= data;
		data <= data;
	end
	else
	begin
		readdata <= 32'b0;
		data <= data;
	end
end

	assign led_out = data;

endmodule