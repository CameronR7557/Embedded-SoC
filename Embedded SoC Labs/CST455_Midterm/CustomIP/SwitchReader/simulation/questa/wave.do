onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -label RST_N -radix binary /testbench/T1/reset_n
add wave -noupdate -label CLK -radix binary /testbench/T1/clk
add wave -noupdate -label ADDR -radix binary /testbench/T1/address
add wave -noupdate -label CS -radix binary /testbench/T1/chipselect
add wave -noupdate -label RD -radix binary /testbench/T1/read
add wave -noupdate -label SWs -radix binary /testbench/T1/switch
add wave -noupdate -divider Outputs
add wave -noupdate -label RD_DATA -radix hexadecimal /testbench/T1/readdata
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
WaveRestoreZoom {0 ns} {300 ns}