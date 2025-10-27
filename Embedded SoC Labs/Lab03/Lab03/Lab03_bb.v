
module Lab03 (
	clk_clk,
	hex0_export,
	hex1_export,
	hex2_export,
	switches_export);	

	input		clk_clk;
	output	[6:0]	hex0_export;
	output	[6:0]	hex1_export;
	output	[6:0]	hex2_export;
	input	[9:0]	switches_export;
endmodule
