`timescale 1ns / 1ps

module testbench ();

	reg [1:0] address;
	reg chipselect;
	reg clk;
	reg read;
	reg reset_n;
	reg write;
	reg [31:0] writedata;
	wire [31:0] readdata;

FibonacciSeq T1 (address, chipselect, clk, read, reset_n, write, writedata, readdata);

	always
		#5 clk <= ~clk;

	initial 
		begin
			clk <= 1'b0;
			writedata <= 32'b0;
			address <= 2'b0;
			chipselect <= 1'b0;
			read <= 1'b0;
			reset_n <= 1'b0;
			write <= 1'b0;
			
			#10 reset_n <= 1;
			writedata <= 32'd21;
			address <= 2'b0;
			chipselect <= 1'b1;
			write <= 1'b1;
			
			#20 address <= 2'b01;
			writedata <= 32'b1;
			chipselect <= 1'b1;
			write <= 1'b1;
			
			#20 address <= 2'b10;
			writedata <= 32'b0;
			chipselect <= 1'b1;
			write <= 1'b0;
			read <= 1'b1;
			#20 address <= 2'b11;
			#100 address <= 2'b10;
			
			#50
			writedata <= 32'd80;
			address <= 2'b0;
			chipselect <= 1'b1;
			write <= 1'b1;
			read <= 1'b0;
			
			#20 address <= 2'b01;
			writedata <= 32'b1;
			chipselect <= 1'b1;
			write <= 1'b1;
			
			#20 address <= 2'b10;
			writedata <= 32'b0;
			chipselect <= 1'b1;
			write <= 1'b0;
			read <= 1'b1;
			#20 address <= 2'b11;
			#100 address <= 2'b10;
			
			#50
			writedata <= 32'd145;
			address <= 2'b0;
			chipselect <= 1'b1;
			write <= 1'b1;
			read <= 1'b0;
			
			#20 address <= 2'b01;
			writedata <= 32'b1;
			chipselect <= 1'b1;
			write <= 1'b1;
			
			#20 address <= 2'b10;
			writedata <= 32'b0;
			chipselect <= 1'b1;
			write <= 1'b0;
			read <= 1'b1;
			#20 address <= 2'b11;
			#100 address <= 2'b10;
			
			#100 reset_n <= 1'b0;
		end
	
endmodule 