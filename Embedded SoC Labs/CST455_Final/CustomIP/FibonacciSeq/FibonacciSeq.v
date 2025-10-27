//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 455
//   Author: Cameron Robinson
//   Lab: Final
//   Project: CST 455 Final
//   File Name: FibonacciSeq.v
//   List of other files used: None
//-----------------------------------------------------------------------------    
//   Custom IP with muli-reg interface for calculating Fibonacci sequences.
//   Registers:
//			reg1: Input reg to hold value to calculate seq to
//			reg2: Control reg to begin seq (when reg2[0] == 1)
//			reg3: Status reg to indicate state of module
//			reg4: Result reg to store final value of sequence
//-----------------------------------------------------------------------------    
//   Date:12/5/2023
//   Version: 1.0
//   Revision:
//   12/5/2023 Initial and final version
//-----------------------------------------------------------------------------

module FibonacciSeq(
	input [1:0] address,
	input chipselect,
	input clk,
	input read,
	input reset_n,
	input write,
	input [31:0] writedata,
	output reg [31:0] readdata
);

reg [31:0] reg1;		//Input reg
reg [31:0] reg2;		//Control reg
reg [31:0] reg3;		//Status reg
reg [31:0] reg4;		//Result reg
reg calcFlag;			//Flag for calculating sequence
reg [31:0] curVal;	//Reg to hold current value of seq
reg [31:0] prevVal;  //Reg to hold previous value of seq

always @(posedge clk or negedge reset_n)
begin
	if(reset_n == 1'b0)
	begin
		reg1 <= 32'b0;
		reg2 <= 32'b0;
		reg3 <= 32'b0;
		reg4 <= 32'b0;
		curVal <= 32'b1;
		prevVal <= 32'b0;
	end
	else if(calcFlag)//Calc seq
	begin
		if((curVal + prevVal) <= reg1)//If next val in seq is <= input -> continue seq
		begin
			curVal <= curVal + prevVal;
			prevVal <= curVal;
			calcFlag <= 1'b1;
			reg3 <= 32'b0;
			reg1 <= reg1;
			reg2 <= reg2;
			reg4 <= 32'b0;
		end
		else //If next val is larger than input -> stop seq (treating input as upper limit rather than goal)
		begin
			calcFlag <= 1'b0;
			reg3 <= 32'b1;
			reg1 <= reg1;
			reg2 <= reg2;
			reg4 <= curVal;
			curVal <= 1'b1;
			prevVal <= 1'b0;
		end
	end
	else if(reg2[0] == 1'b1)//Start seq
	begin
		calcFlag <= 1'b1;
		reg2 <= 32'b0;
		reg1 <=reg1;
		reg3 <= reg3;
		reg4 <= reg4;
	end
	else if(chipselect && write)//Write to reg
	begin
		case(address)
			0: reg1 <= writedata;
			1: reg2 <= writedata;
			2: reg3 <= writedata;
			3: reg4 <= writedata;
		endcase
	end
	else
	begin
		curVal <= curVal;
		prevVal <= prevVal;
		reg1 <= reg1;
		reg2 <= reg2;
		reg3 <= reg3;
		reg4 <= reg4;
	end
end

always @(posedge clk or negedge reset_n)
begin
	if(reset_n == 1'b0)
	begin
		readdata <= 32'b0;
	end
	else if (chipselect && read)//Read from reg
	begin
		case(address)
			0: readdata <= reg1;
			1: readdata <= reg2;
			2: readdata <= reg3;
			3: readdata <= reg4;
		endcase
	end
	else
	begin
		readdata <= 32'b0;
	end
end

endmodule