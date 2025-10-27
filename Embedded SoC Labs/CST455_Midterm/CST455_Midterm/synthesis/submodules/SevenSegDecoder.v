module SevenSegDecoder(
	input clk,
	input reset_n,
	input [1:0] address,
	input write,
	input [31:0] writedata,
	input chipselect,
	output reg [31:0] readdata,
	output reg [6:0] segs
);
	reg [4:0] data;
	
	always @(posedge clk or negedge reset_n)
	begin
		if(reset_n == 1'b0)
		begin
			readdata <= 32'b0;
			data <= 5'h10;
		end
		else if(chipselect && write && address == 2'b0)
		begin
			data <= writedata[4:0];
			readdata <= 32'b0;
		end
		else
		begin
			data <= data;
			readdata <= readdata;
		end
	end
	
	always @(data)
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
					segs <= 7'b0001000;
				end
			11:
				begin
					segs <= 7'b0000011;
				end
			12:
				begin
					segs <= 7'b1000110;
				end
			13:
				begin
					segs <= 7'b0100001;
				end
			14:
				begin
					segs <= 7'b0000110;
				end
			15:
				begin
					segs <= 7'b0001110;
				end
			default:
				begin
					segs <= 7'b1111111;
				end
		endcase
	end

endmodule
