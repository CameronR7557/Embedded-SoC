`timescale 1ns / 1ps

module testbench ();

	reg clk;
	reg reset_n;
	reg [1:0] address;
	reg read;
	reg write;
	reg chipselect;
	reg [31:0] writedata;
	wire [31:0] readdata;

My_CRC T1 (clk, reset_n, address, read, write, chipselect, writedata, readdata);

	always
		#5 clk <= ~clk;

	initial 
		begin
			clk<= 1'b0;
			reset_n <= 1'b0;
			address <= 2'b0;
			read <= 1'b0;
			write <= 1'b0;
			chipselect <= 1'b0;
			writedata <= 32'b0;
			#10 reset_n <= 1'b1;
			#10 read <= 1'b1;
			#7 read <= 1'b0;
			write <= 1'b1;
			chipselect <= 1'b1;
			writedata <= 32'h0e1b2c54;
			#10 writedata <= 32'h05438245;
			#10 writedata <= 32'h05340543;
			#10 writedata <= 32'h05240534;
			
			#10 writedata <= 32'hf60515f5;
			#10 writedata <= 32'h24f40515;
			#10 writedata <= 32'h0534f305;
			#10 writedata <= 32'he90563ef;
			#10 writedata <= 32'hdab1e091;
			#10 writedata <= 32'h6d4c76e2;
			#10 writedata <= 32'h860e1b54;
			#10 writedata <= 32'h00ebd51b;
			#10 write <= 1'b0;
			read <= 1'b1;
		   #600
			reset_n <= 1'b0;
			
//			#10 writedata <= 32'h34052405;
//			#10 writedata <= 32'hf51505f6;
//			#10 writedata <= 32'h1505f424;
//			#10 writedata <= 32'h05f33405;
//			#10 writedata <= 32'hef6305e9;
//			#10 writedata <= 32'h91e0b1da;
//			#10 writedata <= 32'he2764c6d;
//			#10 writedata <= 32'h541b0e86;
//			#10 writedata <= 32'h001bd5eb;
			
		end
	
endmodule 