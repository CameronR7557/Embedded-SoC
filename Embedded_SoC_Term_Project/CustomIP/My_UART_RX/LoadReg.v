//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 455
//   Author: Cameron Robinson
//   Project: Term Project
//   File Name: LoadReg.v
//   List of other files used: none
//-----------------------------------------------------------------------------    
//   Load register wrapped in avalon slave. Tracks whether data has been read or not.
//-----------------------------------------------------------------------------    
//   Date: 12/3/2023
//   Version: 1.0
//   Revision:
// 	12/3/2023: Initial and final version
//-----------------------------------------------------------------------------

module LoadReg(
	input clk,
	input reset_n,
	input [1:0] address,
	input read,
	input chipselect,
	input [8:0] RX_data,
	input load,
	output reg [31:0] readdata
);
	reg readFlag;		//register to track if the data has been read
	reg [8:0] data;   //register to store loaded data

	always @(posedge clk or negedge reset_n)
		begin
			if(~reset_n)
			begin
				readdata <= 32'b0;
				readFlag <= 1'b0;
				data <= 9'b0;
			end
			else if(load)
			begin
				readdata <= 32'b0;
				data <= RX_data;
				readFlag <= 1'b1;
			end
			else if(chipselect && read && (address == 2'b00))
			begin
				readdata <= {22'b0, data[8], readFlag, data[7:0]};
				data <= data;
				readFlag <= 0;
			end
			else
			begin
				readdata <= 32'b0;
				data <= data;
				readFlag <= readFlag;
			end
		end

endmodule