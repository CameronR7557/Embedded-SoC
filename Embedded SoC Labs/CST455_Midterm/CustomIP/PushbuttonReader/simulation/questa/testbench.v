`timescale 1ns / 1ps

module testbench ();

	reg [1:0] address;
	reg chipselect;
	reg clk;
	reg reset_n;
	reg read;
	reg [3:0] pushbuttons;
	wire [31:0] readdata;
	
	integer i = 0;

PushbuttonReader T1 (address, chipselect, clk, reset_n, read, pushbuttons, readdata);

	always
		#10 clk <= ~clk;

	initial 
		begin
			clk <= 1'b0;
			address <= 2'b0;
			chipselect <= 1'b0;
			reset_n <= 1'b0;
			pushbuttons <= 4'b0;
			read <= 1'b0;
			#15 reset_n <= 1;
			#15 chipselect = 1'b1;
			read <= 1'b1;
			
			for(i = 0; i < 16; i = i + 1)
			begin
				#20 pushbuttons <= pushbuttons + 1;
			end
			
			#20 chipselect <= 1'b0;
			read <= 1'b0;
			pushbuttons <= 4'b1010;
			#20 pushbuttons <= 4'b0101;
			#20 reset_n <= 0;
		end
	
endmodule 