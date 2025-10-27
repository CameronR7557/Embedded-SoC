`timescale 1ns / 1ps

module testbench ();

	reg clk;
	reg reset_n;
	reg [1:0] address;
	reg read;
	reg chipselect;
	reg [8:0] RX_data;
	reg load;
	wire [31:0] readdata;

LoadReg T1 (clk, reset_n, address, read, chipselect, RX_data, load, readdata);

	always
		#5 clk <= ~clk;

	initial 
		begin
			chipselect <= 1'b0;
			RX_data <= 8'b0;
			load <= 1'b0;
			read <= 1'b0;
			address <= 2'b00;
			clk<= 1'b0;
			reset_n <= 1'b0;
			#20 reset_n <= 1'b1;
			#20 RX_data <= 8'h54;
			chipselect <= 1'b1;
			#20 load <= 1'b1;
			#10 load <= 1'b0;
			#20 read <= 1'b1;
			#20 read <= 1'b0;
			
			#20 RX_data <= 8'h2C;
			chipselect <= 1'b1;
			#20 load <= 1'b1;
			#10 load <= 1'b0;
			#10 read <= 1'b1;
			#20 read <= 1'b0;
			#20 reset_n <= 1'b0;
			
			
			
			
			//UART:
//			#15 RX_in <= 1'b0;//Start  0x54 lsb first
//			#180 RX_in <= 1'b0;  
//			#180 RX_in <= 1'b0;
//			#180 RX_in <= 1'b1;
//			#180 RX_in <= 1'b0;
//			#180 RX_in <= 1'b1;	
//			#180 RX_in <= 1'b0;
//			#180 RX_in <= 1'b1;
//			#180 RX_in <= 1'b0;
//			#180 RX_in <= 1'b1;	//Stop
//			#180 RX_in <= 1'b0;	//Start 0x2c lsb first
//			#180 RX_in <= 1'b0;  
//			#180 RX_in <= 1'b0;
//			#180 RX_in <= 1'b1;
//			#180 RX_in <= 1'b1;
//			#180 RX_in <= 1'b0;	
//			#180 RX_in <= 1'b1;
//			#180 RX_in <= 1'b0;
//			#180 RX_in <= 1'b0;
//			#180 RX_in <= 1'b1;	//Stop
		end
	
endmodule 