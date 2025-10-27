transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vcom -93 -work work {C:/Users/robin/OneDrive/Desktop/CST455/cst455-labs/Lab02/Hex_to_7Seg.vhd}
vcom -93 -work work {C:/Users/robin/OneDrive/Desktop/CST455/cst455-labs/Lab02/Four_Bit_Adder.vhd}
vcom -93 -work work {C:/Users/robin/OneDrive/Desktop/CST455/cst455-labs/Lab02/Lab02.vhd}

