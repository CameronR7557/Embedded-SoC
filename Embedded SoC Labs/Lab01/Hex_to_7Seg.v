//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 455
//   Author: Cameron Robinson
//   Lab: 1
//   Project: Hex to 7-Seg Decoder
//   File Name: Hex_to_7Seg.v
//   List of other files used: Hex_to_7Seg.v
//-----------------------------------------------------------------------------    
//   Converts a 4-bit Hex number to seven-segment values.
//	  If COM = 0, the output is for a common annode seven segment display, 
//   else if COM = 1 it will output for common cathode.
//-----------------------------------------------------------------------------    
//   Date: 10/05/2023
//   Version: 1.0
//   Revision:
//   10/5/2023 Initial and Final Version
//-----------------------------------------------------------------------------

module Hex_to_7Seg
	#(parameter COM = 1'b0)(
	input [3:0] num,
	output reg [6:0] Seg
);

	always @(num)
		begin
			if(!COM)				//Common anode
				begin
					casez(num)
						0:
							begin
								Seg <= 7'b1000000;
							end
						1:
							begin
								Seg <= 7'b1111001;
							end
						2:
							begin
								Seg <= 7'b0100100;
							end
						3:
							begin
								Seg <= 7'b0110000;
							end
						4:
							begin
								Seg <= 7'b0011001;
							end
						5:
							begin
								Seg <= 7'b0010010;
							end
						6:
							begin
								Seg <= 7'b0000010;
							end
						7:
							begin
								Seg <= 7'b1111000;
							end
						8:
							begin
								Seg <= 7'b0000000;
							end
						9:
							begin
								Seg <= 7'b0010000;
							end
						10:
							begin
								Seg <= 7'b0001000;
							end
						11:
							begin
								Seg <= 7'b0000011;
							end
						12:
							begin
								Seg <= 7'b1000110;
							end
						13:
							begin
								Seg <= 7'b0100001;
							end
						14:
							begin
								Seg <= 7'b0000110;
							end
						15:
							begin
								Seg <= 7'b0001110;
							end
						default:
							begin
								Seg <= 7'b1111111;
							end
					endcase
				end
			else if(COM)					//Common cathode
				begin
					casez(num)
						0:
							begin
								Seg <= ~7'b1000000;
							end
						1:
							begin
								Seg <= ~7'b1111001;
							end
						2:
							begin
								Seg <= ~7'b0100100;
							end
						3:
							begin
								Seg <= ~7'b0110000;
							end
						4:
							begin
								Seg <= ~7'b0011001;
							end
						5:
							begin
								Seg <= ~7'b0010010;
							end
						6:
							begin
								Seg <= ~7'b0000010;
							end
						7:
							begin
								Seg <= ~7'b1111000;
							end
						8:
							begin
								Seg <= ~7'b0000000;
							end
						9:
							begin
								Seg <= ~7'b0010000;
							end
						10:
							begin
								Seg <= ~7'b0001000;
							end
						11:
							begin
								Seg <= ~7'b0000011;
							end
						12:
							begin
								Seg <= ~7'b1000110;
							end
						13:
							begin
								Seg <= ~7'b0100001;
							end
						14:
							begin
								Seg <= ~7'b0000110;
							end
						15:
							begin
								Seg <= ~7'b0001110;
							end
						default:
							begin
								Seg <= ~7'b1111111;
							end
					endcase
				end
			end
endmodule