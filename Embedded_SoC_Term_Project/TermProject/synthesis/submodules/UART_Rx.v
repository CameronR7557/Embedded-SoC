//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 455
//   Author: Cameron Robinson
//   Project: Term Project
//   File Name: UART_RX.v
//   List of other files used: none
//-----------------------------------------------------------------------------    
//   Recieves data with the format of 1 start bit, 8 data bits, and 1 stop bit
//-----------------------------------------------------------------------------    
//   Date: 11/28/2023
//   Version: 1.2
//   Revision:
//   11/28/2023 Initial version
//   12/3/2023  Added load signal removed Avalon Slave wrapper
//-----------------------------------------------------------------------------

module UART_Rx(
	input clk,
	input reset_n,
	input RX_in,
	output [8:0] RX_data,
	output reg load
);
	
	//----------------------------------------------------
	// Signal Declarations: reg
	//----------------------------------------------------
	reg [1:0] state;						//reg to hold current state
	reg [4:0] count;						//reg to count between bit samples
	reg [3:0] count_data;				//reg to count the number of data bits read
	reg [7:0] data;						//reg to hold the read data bits
	reg error;								//reg that goes high if parity is wrong or stop bit is not read
	 
	parameter Idle = 2'b00, Shift = 2'b01, Stop = 2'b10;
	
	always @(posedge clk or negedge reset_n)
		begin
			if(~reset_n)
				begin
					count <= 5'b0;
					count_data <= 4'b0;
					data <= 8'bz;
					state <= Idle;
					error <= 1'b0;
					load <= 1'b0;
				end
			else
				begin
					case(state)
						Idle :
							begin
								error <= 1'b0;
								load <= 1'b0;
								if(~RX_in)
									begin
										if(count == 9)	//Changed from 8 to 9 for 18x clk
											begin
												state <= Shift;
												count <= 5'b0;
												count_data <= 4'b0;
												data <= 8'bz;
											end
										else
											begin
												state <= Idle;
												count <= count + 1'b1;
											end
									end
								else
									begin
										state <= Idle;
										count <= 5'b0;
									end
									
							end
						Shift :
							begin
								load <= 1'b0;
								if(count_data < 8)
									begin
										if(count == 17)//Changed to 17 for an 18x clk since it divides better 
											begin
												count <= 5'b0;
												count_data <= count_data + 1'b1;
												data <= {RX_in, data[7:1]};			//Data comes LSB first
												state <= Shift;
											end
										else
											begin
												data <= data;
												state <= Shift;
												count <= count + 1'b1;
											end
									end
								else
									begin
										state <= Stop;
										count_data <= 4'b0;
										count <= 5'b0;
									end
							end
						Stop :
							begin
								if(count == 17)//Changed to 17 for an 18x clk since it divides better
									begin
										count <= 5'b0;
										state <= Idle;
										load <= 1'b1;
										if(RX_in != 1'b1)
											begin
												error <= 1'b1;
											end
									end
								else
									begin
										state <= Stop;
										count <= count + 1'b1;
										load <= 1'b0;
									end
							end
						default :
							begin
								count <= 5'b0;
								count_data <= 4'b0;
								data <= 8'bz;
								state <= Idle;
								error <= 1'b0;
								load <= 1'b0;
							end
					endcase
				end
		end
		
		assign RX_data = {error, data};
	
endmodule 