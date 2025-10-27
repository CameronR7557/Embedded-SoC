quit -sim

vlib work;

vlog ../../*.v

vlog *.v

vsim work.testbench -Lf 220model -Lf altera_mf_ver -Lf verilog -L work -voptargs="+acc"

do wave.do

run 800 ns