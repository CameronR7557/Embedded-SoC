transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+C:/Users/robin/OneDrive/Desktop/CST455/cst455-labs/CST455_Final/CustomIP/FibonacciSeq {C:/Users/robin/OneDrive/Desktop/CST455/cst455-labs/CST455_Final/CustomIP/FibonacciSeq/FibonacciSeq.v}

