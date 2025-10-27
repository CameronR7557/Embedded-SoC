module UART_RX_HWAcc(
	input clk,
	input reset_n,
	input [1:0] address,
	input read,
	input chipselect,
	input RX_in,
	output reg [31:0] readdata
);

wire ld;
wire [8:0] dataRX;

My_UART_RX U1(clk, reset_n, RX_in, dataRX, ld);
LoadReg U2(clk, reset_n, address, read, chipselect, dataRX, ld, readdata);

endmodule