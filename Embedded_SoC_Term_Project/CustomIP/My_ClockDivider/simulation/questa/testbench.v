`timescale 1ns / 1ps

module testbench ();
	reg clk;
	reg reset_n;
	reg [1:0] address;
	reg write;
	reg chipselect;
	reg [31:0] writedata;
	wire clk_out;

My_ClockDivider T1 (clk, reset_n, chipselect, address, write, writedata, clk_out);

	always
		#5 clk <= ~clk;

	initial 
		begin
			clk<= 1'b0;
			reset_n <= 1'b0;
			address <= 2'b0;
			write <= 1'b0;
			chipselect <= 1'b0;
			writedata <= 32'b0;
			#20 reset_n <= 1'b1;
			#240 write <= 1'b1;
			writedata <= 32'b10;
			#10 chipselect <= 1'b1;
			#20 chipselect <= 1'b0;
			write <= 1'b0;
			#80 reset_n <= 1'b0;
		end
	
endmodule 