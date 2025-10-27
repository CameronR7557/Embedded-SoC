`timescale 1ns / 1ps

module testbench ();

wire [6:0] seg;

reg [3:0] num;

Hex_to_7Seg U1 (num, seg);

	initial 
		begin
			num <= 0;
			#10 num <= 1;
			#10 num <= 2;
			#10 num <= 3;
			#10 num <= 4;
			#10 num <= 5;
			#10 num <= 6;
			#10 num <= 7;
			#10 num <= 8;
			#10 num <= 9;
			#10 num <= 10;
			#10 num <= 11;
			#10 num <= 12;
			#10 num <= 13;
			#10 num <= 14;
			#10 num <= 15;
		end
	
endmodule 