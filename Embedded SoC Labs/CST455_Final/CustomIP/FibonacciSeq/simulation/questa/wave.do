onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label RST_N -radix binary /testbench/T1/reset_n
add wave -noupdate -label CLK -radix binary /testbench/T1/clk
add wave -noupdate -label ADDR -radix binary /testbench/T1/address
add wave -noupdate -label CS -radix binary /testbench/T1/chipselect
add wave -noupdate -label RD -radix binary /testbench/T1/read
add wave -noupdate -label WR -radix binary /testbench/T1/write
add wave -noupdate -label WR_DATA -radix decimal /testbench/T1/writedata
add wave -noupdate -divider Outputs
add wave -noupdate -label RD_DATA -radix decimal /testbench/T1/readdata
add wave -noupdate -divider Registers
add wave -noupdate -label  INPUT -radix decimal /testbench/T1/reg1
add wave -noupdate -label CONTROL -radix decimal /testbench/T1/reg2
add wave -noupdate -label STATUS -radix decimal /testbench/T1/reg3
add wave -noupdate -label RESULT -radix decimal /testbench/T1/reg4
add wave -noupdate -label PREV -radix decimal /testbench/T1/prevVal
add wave -noupdate -label CURRENT -radix decimal /testbench/T1/curVal
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
WaveRestoreZoom {0 ns} {800 ns}