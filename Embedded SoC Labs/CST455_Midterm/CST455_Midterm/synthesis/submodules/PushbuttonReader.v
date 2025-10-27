module PushbuttonReader(
	input [1:0] address,
	input chipselect,
	input clk,
	input reset_n,
	input read,
	input [3:0] pushbuttons,
	output reg [31:0] readdata
);

always @(posedge clk or negedge reset_n)
begin
	if(reset_n == 1'b0)
	begin
		readdata <= 32'b0;
	end
	else if (read && chipselect && (address == 2'b0))
	begin
		readdata <= pushbuttons;
	end
	else
	begin
		readdata <= 32'b0;
	end
end

endmodule