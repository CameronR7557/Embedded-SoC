//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 455
//   Author: Cameron Robinson
//   Lab: Midterm
//   Project: CST 455 Term Project
//   File Name: SevenSegDecoder.v
//   List of other files used: None
//-----------------------------------------------------------------------------    
//   Custom IP for reading and writing hex values to seven-segment displays.
//	  This module decodes most letters, however, some like w, k, and m are not 
//   implemented. The unimoplemented value decode to 7'b1111111;
//-----------------------------------------------------------------------------    
//   Date:10/28/2023
//   Version: 1.0
//   Revision:
//   10/28/2023 Initial version
//	  11/9/2023 Added letters
//-----------------------------------------------------------------------------

module SevenSegDecoder(
	input clk,
	input reset_n,
	input [1:0] address,
	input write,
	input [31:0] writedata,
	input chipselect,
	output reg [6:0] segs
);
	reg [5:0] data;		//Reg to store input number
	
	always @(posedge clk or negedge reset_n)
	begin
		if(reset_n == 1'b0)
		begin
			data <= 6'h3F;
		end
		else if(chipselect && write && address == 2'b0)
		begin
			data <= writedata[5:0];
		end
		else
		begin
			data <= data;
		end
	end
	
	always @(data)		//decode to 7-seg
	begin
		case(data)
			0:
				begin
					segs <= 7'b1000000;
				end
			1:
				begin
					segs <= 7'b1111001;
				end
			2:
				begin
					segs <= 7'b0100100;
				end
			3:
				begin
					segs <= 7'b0110000;
				end
			4:
				begin
					segs <= 7'b0011001;
				end
			5:
				begin
					segs <= 7'b0010010;
				end
			6:
				begin
					segs <= 7'b0000010;
				end
			7:
				begin
					segs <= 7'b1111000;
				end
			8:
				begin
					segs <= 7'b0000000;
				end
			9:
				begin
					segs <= 7'b0010000;
				end
			10:
				begin
					segs <= 7'b0001000;//A
				end
			11:
				begin
					segs <= 7'b0000011;//b
				end
			12:
				begin
					segs <= 7'b1000110;//c
				end
			13:
				begin
					segs <= 7'b0100001;//d
				end
			14:
				begin
					segs <= 7'b0000110;//E
				end
			15:
				begin
					segs <= 7'b0001110;//F
				end
			16:
				begin
					segs <= 7'b0010000;//g
				end
			17:
				begin
					segs <= 7'b0001001;//H
				end
			18:
				begin
					segs <= 7'b1111001;//I
				end
			19:
				begin
					segs <= 7'b1110010;//j
				end
			20:
				begin
					segs <= 7'b1111111;//K
				end
			21:
				begin
					segs <= 7'b1000111;//L
				end
			22:
				begin
					segs <= 7'b1111111;//M
				end
			23:
				begin
					segs <= 7'b1001000;//N
				end
			24:
				begin
					segs <= 7'b0100011;//o
				end
			25:
				begin
					segs <= 7'b0001100;//P
				end
			26:
				begin
					segs <= 7'b0011000;//Q
				end
			27:
				begin
					segs <= 7'b0101111;//R
				end
			28:
				begin
					segs <= 7'b0010010;//S
				end
			29:
				begin
					segs <= 7'b0000111;//t
				end
			30:
				begin
					segs <= 7'b1000001;//U
				end
			31:
				begin
					segs <= 7'b1111111;//V
				end
			32:
				begin
					segs <= 7'b1111111;//W
				end
			33:
				begin
					segs <= 7'b1111111;//X
				end
			34:
				begin
					segs <= 7'b0011001;//Y
				end
			35:
				begin
					segs <= 7'b1111111;//Z
				end
			default:
				begin
					segs <= 7'b1111111;
				end
		endcase
	end

endmodule
