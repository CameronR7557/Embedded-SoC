`timescale 1ns / 1ps

module testbench ();

	reg [1:0] address;
	reg chipselect;
	reg clk;
	reg reset_n;
	reg read;
	reg [9:0] switch;
	wire [31:0] readdata;

SwitchReader T1 (address, chipselect, clk, reset_n, read, switch, readdata);

	always
		#10 clk <= ~clk;

	initial 
		begin
			clk <= 1'b0;
			address <= 2'b0;
			chipselect <= 1'b0;
			read <= 1'b0;
			reset_n <= 1'b0;
			switch <= 10'b0;
			#15 reset_n <= 1;
			#10 chipselect = 1'b1;
			read <= 1'b1;
			#20 switch <= 10'h2aa;
			#40 chipselect <= 1'b0;
			read <= 1'b0;
			#20 switch <= 10'h155;
			#20 chipselect <= 1'b1;
			read <= 1'b1;
			#40 switch <= 10'h3ff;
			#20 switch <= 10'h001;
			#60 reset_n <= 0;
		end
	
endmodule 