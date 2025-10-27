//-----------------------------------------------------------------------------    
//   University: Oregon Institute of Technology – CSET Department
//   Class: CST 455
//   Author: Cameron Robinson
//   Project: Term Project
//   File Name: My_CRC.v
//   List of other files used: none
//-----------------------------------------------------------------------------    
//   LD19 2D LiDAR CRC wrapped in an Avalon slave.
//-----------------------------------------------------------------------------    
//   Date: 12/3/2023
//   Version: 1.0
//   Revision:
// 	12/3/2023: Initial and final version
//-----------------------------------------------------------------------------

module My_CRC(
	input clk,
	input reset_n,
	input [1:0] address,
	input read,
	input write,
	input chipselect,
	input [31:0] writedata,
	output reg [31:0] readdata
);

reg [7:0] CrcTable [255:0];	//Array to hold crc lookup table
reg [7:0] crc;						//Reg to hold calculated crc
reg [375:0] data;					//Reg to hold LiDAR data packet (47 bytes)
reg [3:0] count;					//Count reg for receiving data
reg [5:0] crcCount;				//Count reg for calculating crc
reg [1:0] status;					//CRC status reg: 0 - not ready, 1 - calculating, 2 - Data ready

initial
begin
	CrcTable[0] = 8'h0;
	CrcTable[1] = 8'h4d;
	CrcTable[2] = 8'h9a;
	CrcTable[3] = 8'hd7;
	CrcTable[4] = 8'h79;
	CrcTable[5] = 8'h34;
	CrcTable[6] = 8'he3;
	CrcTable[7] = 8'hae;
	CrcTable[8] = 8'hf2;
	CrcTable[9] = 8'hbf;
	CrcTable[10] = 8'h68;
	CrcTable[11] = 8'h25;
	CrcTable[12] = 8'h8b;
	CrcTable[13] = 8'hc6;
	CrcTable[14] = 8'h11;
	CrcTable[15] = 8'h5c;
	CrcTable[16] = 8'ha9;
	CrcTable[17] = 8'he4;
	CrcTable[18] = 8'h33;
	CrcTable[19] = 8'h7e;
	CrcTable[20] = 8'hd0;
	CrcTable[21] = 8'h9d;
	CrcTable[22] = 8'h4a;
	CrcTable[23] = 8'h7;
	CrcTable[24] = 8'h5b;
	CrcTable[25] = 8'h16;
	CrcTable[26] = 8'hc1;
	CrcTable[27] = 8'h8c;
	CrcTable[28] = 8'h22;
	CrcTable[29] = 8'h6f;
	CrcTable[30] = 8'hb8;
	CrcTable[31] = 8'hf5;
	CrcTable[32] = 8'h1f;
	CrcTable[33] = 8'h52;
	CrcTable[34] = 8'h85;
	CrcTable[35] = 8'hc8;
	CrcTable[36] = 8'h66;
	CrcTable[37] = 8'h2b;
	CrcTable[38] = 8'hfc;
	CrcTable[39] = 8'hb1;
	CrcTable[40] = 8'hed;
	CrcTable[41] = 8'ha0;
	CrcTable[42] = 8'h77;
	CrcTable[43] = 8'h3a;
	CrcTable[44] = 8'h94;
	CrcTable[45] = 8'hd9;
	CrcTable[46] = 8'he;
	CrcTable[47] = 8'h43;
	CrcTable[48] = 8'hb6;
	CrcTable[49] = 8'hfb;
	CrcTable[50] = 8'h2c;
	CrcTable[51] = 8'h61;
	CrcTable[52] = 8'hcf;
	CrcTable[53] = 8'h82;
	CrcTable[54] = 8'h55;
	CrcTable[55] = 8'h18;
	CrcTable[56] = 8'h44;
	CrcTable[57] = 8'h9;
	CrcTable[58] = 8'hde;
	CrcTable[59] = 8'h93;
	CrcTable[60] = 8'h3d;
	CrcTable[61] = 8'h70;
	CrcTable[62] = 8'ha7;
	CrcTable[63] = 8'hea;
	CrcTable[64] = 8'h3e;
	CrcTable[65] = 8'h73;
	CrcTable[66] = 8'ha4;
	CrcTable[67] = 8'he9;
	CrcTable[68] = 8'h47;
	CrcTable[69] = 8'ha;
	CrcTable[70] = 8'hdd;
	CrcTable[71] = 8'h90;
	CrcTable[72] = 8'hcc;
	CrcTable[73] = 8'h81;
	CrcTable[74] = 8'h56;
	CrcTable[75] = 8'h1b;
	CrcTable[76] = 8'hb5;
	CrcTable[77] = 8'hf8;
	CrcTable[78] = 8'h2f;
	CrcTable[79] = 8'h62;
	CrcTable[80] = 8'h97;
	CrcTable[81] = 8'hda;
	CrcTable[82] = 8'hd;
	CrcTable[83] = 8'h40;
	CrcTable[84] = 8'hee;
	CrcTable[85] = 8'ha3;
	CrcTable[86] = 8'h74;
	CrcTable[87] = 8'h39;
	CrcTable[88] = 8'h65;
	CrcTable[89] = 8'h28;
	CrcTable[90] = 8'hff;
	CrcTable[91] = 8'hb2;
	CrcTable[92] = 8'h1c;
	CrcTable[93] = 8'h51;
	CrcTable[94] = 8'h86;
	CrcTable[95] = 8'hcb;
	CrcTable[96] = 8'h21;
	CrcTable[97] = 8'h6c;
	CrcTable[98] = 8'hbb;
	CrcTable[99] = 8'hf6;
	CrcTable[100] = 8'h58;
	CrcTable[101] = 8'h15;
	CrcTable[102] = 8'hc2;
	CrcTable[103] = 8'h8f;
	CrcTable[104] = 8'hd3;
	CrcTable[105] = 8'h9e;
	CrcTable[106] = 8'h49;
	CrcTable[107] = 8'h4;
	CrcTable[108] = 8'haa;
	CrcTable[109] = 8'he7;
	CrcTable[110] = 8'h30;
	CrcTable[111] = 8'h7d;
	CrcTable[112] = 8'h88;
	CrcTable[113] = 8'hc5;
	CrcTable[114] = 8'h12;
	CrcTable[115] = 8'h5f;
	CrcTable[116] = 8'hf1;
	CrcTable[117] = 8'hbc;
	CrcTable[118] = 8'h6b;
	CrcTable[119] = 8'h26;
	CrcTable[120] = 8'h7a;
	CrcTable[121] = 8'h37;
	CrcTable[122] = 8'he0;
	CrcTable[123] = 8'had;
	CrcTable[124] = 8'h3;
	CrcTable[125] = 8'h4e;
	CrcTable[126] = 8'h99;
	CrcTable[127] = 8'hd4;
	CrcTable[128] = 8'h7c;
	CrcTable[129] = 8'h31;
	CrcTable[130] = 8'he6;
	CrcTable[131] = 8'hab;
	CrcTable[132] = 8'h5;
	CrcTable[133] = 8'h48;
	CrcTable[134] = 8'h9f;
	CrcTable[135] = 8'hd2;
	CrcTable[136] = 8'h8e;
	CrcTable[137] = 8'hc3;
	CrcTable[138] = 8'h14;
	CrcTable[139] = 8'h59;
	CrcTable[140] = 8'hf7;
	CrcTable[141] = 8'hba;
	CrcTable[142] = 8'h6d;
	CrcTable[143] = 8'h20;
	CrcTable[144] = 8'hd5;
	CrcTable[145] = 8'h98;
	CrcTable[146] = 8'h4f;
	CrcTable[147] = 8'h2;
	CrcTable[148] = 8'hac;
	CrcTable[149] = 8'he1;
	CrcTable[150] = 8'h36;
	CrcTable[151] = 8'h7b;
	CrcTable[152] = 8'h27;
	CrcTable[153] = 8'h6a;
	CrcTable[154] = 8'hbd;
	CrcTable[155] = 8'hf0;
	CrcTable[156] = 8'h5e;
	CrcTable[157] = 8'h13;
	CrcTable[158] = 8'hc4;
	CrcTable[159] = 8'h89;
	CrcTable[160] = 8'h63;
	CrcTable[161] = 8'h2e;
	CrcTable[162] = 8'hf9;
	CrcTable[163] = 8'hb4;
	CrcTable[164] = 8'h1a;
	CrcTable[165] = 8'h57;
	CrcTable[166] = 8'h80;
	CrcTable[167] = 8'hcd;
	CrcTable[168] = 8'h91;
	CrcTable[169] = 8'hdc;
	CrcTable[170] = 8'hb;
	CrcTable[171] = 8'h46;
	CrcTable[172] = 8'he8;
	CrcTable[173] = 8'ha5;
	CrcTable[174] = 8'h72;
	CrcTable[175] = 8'h3f;
	CrcTable[176] = 8'hca;
	CrcTable[177] = 8'h87;
	CrcTable[178] = 8'h50;
	CrcTable[179] = 8'h1d;
	CrcTable[180] = 8'hb3;
	CrcTable[181] = 8'hfe;
	CrcTable[182] = 8'h29;
	CrcTable[183] = 8'h64;
	CrcTable[184] = 8'h38;
	CrcTable[185] = 8'h75;
	CrcTable[186] = 8'ha2;
	CrcTable[187] = 8'hef;
	CrcTable[188] = 8'h41;
	CrcTable[189] = 8'hc;
	CrcTable[190] = 8'hdb;
	CrcTable[191] = 8'h96;
	CrcTable[192] = 8'h42;
	CrcTable[193] = 8'hf;
	CrcTable[194] = 8'hd8;
	CrcTable[195] = 8'h95;
	CrcTable[196] = 8'h3b;
	CrcTable[197] = 8'h76;
	CrcTable[198] = 8'ha1;
	CrcTable[199] = 8'hec;
	CrcTable[200] = 8'hb0;
	CrcTable[201] = 8'hfd;
	CrcTable[202] = 8'h2a;
	CrcTable[203] = 8'h67;
	CrcTable[204] = 8'hc9;
	CrcTable[205] = 8'h84;
	CrcTable[206] = 8'h53;
	CrcTable[207] = 8'h1e;
	CrcTable[208] = 8'heb;
	CrcTable[209] = 8'ha6;
	CrcTable[210] = 8'h71;
	CrcTable[211] = 8'h3c;
	CrcTable[212] = 8'h92;
	CrcTable[213] = 8'hdf;
	CrcTable[214] = 8'h8;
	CrcTable[215] = 8'h45;
	CrcTable[216] = 8'h19;
	CrcTable[217] = 8'h54;
	CrcTable[218] = 8'h83;
	CrcTable[219] = 8'hce;
	CrcTable[220] = 8'h60;
	CrcTable[221] = 8'h2d;
	CrcTable[222] = 8'hfa;
	CrcTable[223] = 8'hb7;
	CrcTable[224] = 8'h5d;
	CrcTable[225] = 8'h10;
	CrcTable[226] = 8'hc7;
	CrcTable[227] = 8'h8a;
	CrcTable[228] = 8'h24;
	CrcTable[229] = 8'h69;
	CrcTable[230] = 8'hbe;
	CrcTable[231] = 8'hf3;
	CrcTable[232] = 8'haf;
	CrcTable[233] = 8'he2;
	CrcTable[234] = 8'h35;
	CrcTable[235] = 8'h78;
	CrcTable[236] = 8'hd6;
	CrcTable[237] = 8'h9b;
	CrcTable[238] = 8'h4c;
	CrcTable[239] = 8'h1;
	CrcTable[240] = 8'hf4;
	CrcTable[241] = 8'hb9;
	CrcTable[242] = 8'h6e;
	CrcTable[243] = 8'h23;
	CrcTable[244] = 8'h8d;
	CrcTable[245] = 8'hc0;
	CrcTable[246] = 8'h17;
	CrcTable[247] = 8'h5a;
	CrcTable[248] = 8'h6;
	CrcTable[249] = 8'h4b;
	CrcTable[250] = 8'h9c;
	CrcTable[251] = 8'hd1;
	CrcTable[252] = 8'h7f;
	CrcTable[253] = 8'h32;
	CrcTable[254] = 8'he5;
	CrcTable[255] = 8'ha8;
end

always @(posedge clk or negedge reset_n)
begin
	if(reset_n == 1'b0)
	begin
		crcCount <= 6'b0;
		crc <= 8'b0;
		data <= 376'b0;
		count <= 4'b0;
		status <= 2'b0;
	end
	else if(count == 4'hc)
	begin
		//calc CRC using data
		if(crcCount >= 6'h2E)//Only calc CRC with first 46 bytes
		begin
			crcCount <= 6'b0;
			data <= data;
			crc <= crc;
			status <= 2'b10;
			count <= 4'b0;
		end
		else
		begin
			crc <= CrcTable[((data[7:0] ^ crc) & 8'hff)];
			data <= {8'b0, data[375:8]};
			crcCount <= crcCount + 1'b1;
			status <= 2'b01;
			count <= count;
		end
	end
	else if(chipselect && write && (address == 2'b0))
	begin
		crcCount <= 6'b0;
		count <= count + 1'b1;
		crc <= 8'b0;
		status <= 2'b0;
		if(count == 4'hb)
			begin
				data <= {writedata[23:0], data[375:24]};//47 bytes in total, 4 bytes at a time. Only want 3 bytes on last.
			end
		else
			begin
				data <= {writedata, data[375:32]};//Once finished: data[7:0] = 0x54, data[15:8] = 0x2C, ...
			end
	end
	else
	begin
		data <= data;
		crcCount <= 6'b0;
		count <= count;
		status <= status;
		crc <= crc;
	end
end

always @(posedge clk or negedge reset_n)
begin
	if(reset_n == 1'b0)
	begin
		readdata <= 32'b0;
	end
	else if (chipselect && read && (address == 2'b0))
	begin
		readdata <= {22'b0, status, crc};
	end
	else
	begin
		readdata <= 32'b0;
	end
end


endmodule