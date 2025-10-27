`timescale 1ns / 1ps

module testbench ();

	reg [1:0] address;
	reg chipselect;
	reg clk;
	reg reset_n;
	reg write;
	reg [31:0] writedata;
	wire [6:0] segs0;
	wire [6:0] segs1;
	
	integer i = 0;

SevenSegDecoder T1 (clk, reset_n, address, write, writedata, chipselect, segs0, segs1);

	always
		#10 clk <= ~clk;

	initial 
		begin
			clk <= 1'b0;
			writedata <= 32'h00000010;
			address <= 2'b0;
			chipselect <= 1'b0;
			reset_n <= 1'b0;
			write <= 1'b0;
			#15 reset_n <= 1'b1;
			writedata <= 32'h00000001;
			#10 chipselect <= 1'b1;
			#10 write <= 1'b1;
			#10 writedata = 32'b0;
			
			for(i = 0; i < 23; i = i + 1)
			begin
				#20 writedata <= writedata + 32'b0100001;
			end
			
			#20 writedata <= 32'h3FF;
			
			#20 writedata <= 32'b0111101001;
			
			#20 reset_n <= 1'b0;
			
		end
	
endmodule 