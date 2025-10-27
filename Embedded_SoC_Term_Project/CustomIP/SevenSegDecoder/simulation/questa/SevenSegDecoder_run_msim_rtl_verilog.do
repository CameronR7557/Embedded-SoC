transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/robin/OneDrive/Desktop/CST455/cst455-labs/Term_Project/CustomIP/SevenSegDecoder {C:/Users/robin/OneDrive/Desktop/CST455/cst455-labs/Term_Project/CustomIP/SevenSegDecoder/SevenSegDecoder.v}

