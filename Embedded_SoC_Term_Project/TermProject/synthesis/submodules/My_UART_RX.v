//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 455
//   Author: Cameron Robinson
//   Project: Term Project
//   File Name: My_UART_RX.v
//   List of other files used: UART_Rx.v, LoadReg.v
//-----------------------------------------------------------------------------    
//   UART receiver that stores data bits in a load register.
//-----------------------------------------------------------------------------    
//   Date: 12/3/2023
//   Version: 1.0
//   Revision:
// 	12/3/2023: Initial and final version
//-----------------------------------------------------------------------------

module My_UART_RX(
	input clk,
	input reset_n,
	input [1:0] address,
	input read,
	input chipselect,
	input RX_in,
	output [31:0] readdata
);

wire ld;					//load wire b/w UART and load reg
wire [8:0] dataRX;	//RX data bus b/w UART and load reg

UART_Rx U1(clk, reset_n, RX_in, dataRX, ld);
LoadReg U2(clk, reset_n, address, read, chipselect, dataRX, ld, readdata);

endmodule