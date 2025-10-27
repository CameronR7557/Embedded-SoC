//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 455
//   Author: Cameron Robinson
//   Lab: Final
//   Project: CST 455 Final
//   File Name: SevenSegDecoder.v
//   List of other files used: None
//-----------------------------------------------------------------------------    
//   Custom IP for reading and writing hex values to two seven-segment displays.
//   Also decodes value 16 - 22 to values that turn on a single segment.
//-----------------------------------------------------------------------------    
//   Date:12/10/2023
//   Version: 1.0
//   Revision:
//   10/28/2023 Initial version
//   12/7/2023 Added Avalon wrapper and 2nd display decoder
//	  12/9/2023 Added decoding to single segments
//-----------------------------------------------------------------------------

module SevenSegDecoder(
	input clk,
	input reset_n,
	input [1:0] address,
	input write,
	input [31:0] writedata,
	input chipselect,
	output reg [6:0] segs0,
	output reg [6:0] segs1
);
	reg [4:0] data1;		//Reg to store input number
	reg [4:0] data2;		//Reg to store 2nd input number
	
	always @(posedge clk or negedge reset_n)
	begin
		if(reset_n == 1'b0)
		begin
			//readdata <= 32'b0;
			data1 <= 5'h1F;
			data2 <= 5'h1F;
		end
		else if(chipselect && write && address == 2'b0)
		begin
			data1 <= writedata[4:0];
			data2 <= writedata[9:5];
		end
		else
		begin
			data1 <= data1;
			data2 <= data2;
		end
	end
	
	always @(data1)		//decode to 7-seg
	begin
		case(data1)
			0:
				begin
					segs0 <= 7'b1000000;
				end
			1:
				begin
					segs0 <= 7'b1111001;
				end
			2:
				begin
					segs0 <= 7'b0100100;
				end
			3:
				begin
					segs0 <= 7'b0110000;
				end
			4:
				begin
					segs0 <= 7'b0011001;
				end
			5:
				begin
					segs0 <= 7'b0010010;
				end
			6:
				begin
					segs0 <= 7'b0000010;
				end
			7:
				begin
					segs0 <= 7'b1111000;
				end
			8:
				begin
					segs0 <= 7'b0000000;
				end
			9:
				begin
					segs0 <= 7'b0010000;
				end
			10:
				begin
					segs0 <= 7'b0001000;
				end
			11:
				begin
					segs0 <= 7'b0000011;
				end
			12:
				begin
					segs0 <= 7'b1000110;
				end
			13:
				begin
					segs0 <= 7'b0100001;
				end
			14:
				begin
					segs0 <= 7'b0000110;
				end
			15:
				begin
					segs0 <= 7'b0001110;
				end
			16:
				begin
					segs0 <= 7'b1111110;
				end
			17:
				begin
					segs0 <= 7'b1111101;
				end
			18:
				begin
					segs0 <= 7'b1111011;
				end
			19:
				begin
					segs0 <= 7'b1110111;
				end
			20:
				begin
					segs0 <= 7'b1101111;
				end
			21:
				begin
					segs0 <= 7'b1011111;
				end
			22:
				begin
					segs0 <= 7'b0111111;
				end
			default:
				begin
					segs0 <= 7'b1111111;
				end
		endcase
	end
	
	always @(data2)		//decode to 7-seg
	begin
		case(data2)
			0:
				begin
					segs1 <= 7'b1000000;
				end
			1:
				begin
					segs1 <= 7'b1111001;
				end
			2:
				begin
					segs1 <= 7'b0100100;
				end
			3:
				begin
					segs1 <= 7'b0110000;
				end
			4:
				begin
					segs1 <= 7'b0011001;
				end
			5:
				begin
					segs1 <= 7'b0010010;
				end
			6:
				begin
					segs1 <= 7'b0000010;
				end
			7:
				begin
					segs1 <= 7'b1111000;
				end
			8:
				begin
					segs1 <= 7'b0000000;
				end
			9:
				begin
					segs1 <= 7'b0010000;
				end
			10:
				begin
					segs1 <= 7'b0001000;
				end
			11:
				begin
					segs1 <= 7'b0000011;
				end
			12:
				begin
					segs1 <= 7'b1000110;
				end
			13:
				begin
					segs1 <= 7'b0100001;
				end
			14:
				begin
					segs1 <= 7'b0000110;
				end
			15:
				begin
					segs1 <= 7'b0001110;
				end
			16:
				begin
					segs1 <= 7'b1111110;
				end
			17:
				begin
					segs1 <= 7'b1111101;
				end
			18:
				begin
					segs1 <= 7'b1111011;
				end
			19:
				begin
					segs1 <= 7'b1110111;
				end
			20:
				begin
					segs1 <= 7'b1101111;
				end
			21:
				begin
					segs1 <= 7'b1011111;
				end
			22:
				begin
					segs1 <= 7'b0111111;
				end
			default:
				begin
					segs1 <= 7'b1111111;
				end
		endcase
	end

endmodule
