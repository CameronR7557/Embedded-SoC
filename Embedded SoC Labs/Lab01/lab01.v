//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 455
//   Author: Cameron Robinson
//   Lab: 1
//   Project: Hex to 7-Seg Decoder
//   File Name: lab01.v
//   List of other files used: Hex_to_7Seg.v
//-----------------------------------------------------------------------------    
//   Values from switches are decoded and displayed on HEX0 7-Segment display.
//-----------------------------------------------------------------------------    
//   Date:10/5/2023
//   Version: 1.0
//   Revision:
// 10/5/2023 Initial and final version
//-----------------------------------------------------------------------------
module lab01(
	input 		     [3:0]		SW,
	output		     [6:0]		HEX0
);

	Hex_to_7Seg D1(SW[3:0], HEX0[6:0]);


endmodule
