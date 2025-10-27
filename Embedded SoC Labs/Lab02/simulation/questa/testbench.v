`timescale 1ns / 1ps

module testbench ();

wire [3:0] out1;
wire [3:0] out2;
wire [6:0] hex0;
wire [6:0] hex1;
wire [6:0] hex2;
wire [6:0] hex4;

//wire [3:0] msb;
//wire [3:0] lsb;

reg [3:0] num1;
reg [3:0] num2;

integer i;
integer j;


Four_Bit_Adder T1 (num1, num2, out1, out2);
Hex_to_7Seg T2 (num1, hex4);
Hex_to_7Seg T3 (num2, hex2);
Hex_to_7Seg T4 (out2, hex1);
Hex_to_7Seg T5 (out1, hex0);

	initial 
		//num1 <= 0;
		//num2 <= 0;
		begin
			for(i = 0; i < 16; i = i+1)
			begin
				for(j = 0; j < 16; j = j+1)
				begin
					#5 num1 <= i;
					num2 <= j;
				end
			end
		end
	
endmodule 