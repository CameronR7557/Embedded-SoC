onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label NUM1 -radix hexadecimal /testbench/num1
add wave -noupdate -label NUM2 -radix hexadecimal /testbench/num2
add wave -noupdate -divider Outputs
add wave -noupdate -label LSbits -radix hexadecimal /testbench/out1
add wave -noupdate -label MSbits -radix hexadecimal /testbench/out2
add wave -noupdate -divider SevenSegDiaplays
add wave -noupdate -label HEX0 -radix binary /testbench/hex0
add wave -noupdate -label HEX1 -radix binary /testbench/hex1
add wave -noupdate -label HEX2 -radix binary /testbench/hex2
add wave -noupdate -label HEX4 -radix binary /testbench/hex4
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {10000 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 80
configure wave -valuecolwidth 40
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ns} {180 ns}