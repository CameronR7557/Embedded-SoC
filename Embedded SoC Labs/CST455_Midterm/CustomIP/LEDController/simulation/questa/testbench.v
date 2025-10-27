`timescale 1ns / 1ps

module testbench ();

	reg [1:0] address;
	reg chipselect;
	reg clk;
	reg read;
	reg reset_n;
	reg write;
	reg [31:0] writedata;
	wire [9:0] led_out;
	wire [31:0] readdata;

LEDController T1 (address, chipselect, clk, read, reset_n, write, writedata, led_out, readdata);

	always
		#10 clk <= ~clk;

	initial 
		begin
			clk <= 1'b0;
			writedata <= 32'h00000000;
			address <= 2'b0;
			chipselect <= 1'b0;
			read <= 1'b0;
			reset_n <= 1'b0;
			write <= 1'b0;
			#15 reset_n <= 1;
			#5 writedata <= 32'h000002aa;
			#5 chipselect <= 1'b1;
			#7 write <= 1'b1;
			#20 writedata <= 32'h00000000;
			chipselect <= 1'b0;
			write <= 1'b0;
			#40 writedata <= 32'h00000155;
			#5 chipselect <= 1'b1;
			#7 write <= 1'b1;
			#20 writedata <= 32'h000003FF;
			#30 chipselect <= 1'b0;
			write <= 1'b0;
			
			#10 reset_n <= 0;
			#10 reset_n <= 1;
			#10 writedata <= 32'h0000035a;
			#5 write <= 1'b1;
			chipselect <= 1'b1;
			#30 write <= 1'b0;
			chipselect <= 1'b0;
			#20 read <= 1'b1;
		   chipselect <= 1'b1;
			#40 reset_n <= 1'b0;
			chipselect <= 1'b0;
			read <= 1'b0;
		end
	
endmodule 