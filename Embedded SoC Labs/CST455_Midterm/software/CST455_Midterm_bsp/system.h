/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'CST455_Midterm' in SOPC Builder design 'CST455_Midterm'
 * SOPC Builder design path: c:/Users/robin/OneDrive/Desktop/CST455/cst455-labs/CST455_Midterm/CST455_Midterm.sopcinfo
 *
 * Generated: Sun Oct 29 11:49:11 PDT 2023
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x08000820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1c
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x04000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x1c
#define ALT_CPU_NAME "CST455_Midterm"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x04000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x08000820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x1c
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x04000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x1c
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x04000000


/*
 * DEBUG configuration
 *
 */

#define ALT_MODULE_CLASS_DEBUG altera_avalon_jtag_uart
#define DEBUG_BASE 0x80010b0
#define DEBUG_IRQ 1
#define DEBUG_IRQ_INTERRUPT_CONTROLLER_ID 0
#define DEBUG_NAME "/dev/DEBUG"
#define DEBUG_READ_DEPTH 64
#define DEBUG_READ_THRESHOLD 8
#define DEBUG_SPAN 8
#define DEBUG_TYPE "altera_avalon_jtag_uart"
#define DEBUG_WRITE_DEPTH 64
#define DEBUG_WRITE_THRESHOLD 8


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __LEDS
#define __PUSHBUTTONS
#define __SEVENSEGDECODER
#define __SWITCHES


/*
 * LEDs_0 configuration
 *
 */

#define ALT_MODULE_CLASS_LEDs_0 LEDs
#define LEDS_0_BASE 0x80010a0
#define LEDS_0_IRQ -1
#define LEDS_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LEDS_0_NAME "/dev/LEDs_0"
#define LEDS_0_SPAN 16
#define LEDS_0_TYPE "LEDs"


/*
 * Pushbuttons_0 configuration
 *
 */

#define ALT_MODULE_CLASS_Pushbuttons_0 Pushbuttons
#define PUSHBUTTONS_0_BASE 0x8001080
#define PUSHBUTTONS_0_IRQ -1
#define PUSHBUTTONS_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define PUSHBUTTONS_0_NAME "/dev/Pushbuttons_0"
#define PUSHBUTTONS_0_SPAN 16
#define PUSHBUTTONS_0_TYPE "Pushbuttons"


/*
 * SDRAM configuration
 *
 */

#define ALT_MODULE_CLASS_SDRAM altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x4000000
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/SDRAM"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 7.8125
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 67108864
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.4
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 15.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 15.0
#define SDRAM_T_WR 14.0


/*
 * SevenSegDecoder_0 configuration
 *
 */

#define ALT_MODULE_CLASS_SevenSegDecoder_0 SevenSegDecoder
#define SEVENSEGDECODER_0_BASE 0x8001020
#define SEVENSEGDECODER_0_IRQ -1
#define SEVENSEGDECODER_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEVENSEGDECODER_0_NAME "/dev/SevenSegDecoder_0"
#define SEVENSEGDECODER_0_SPAN 16
#define SEVENSEGDECODER_0_TYPE "SevenSegDecoder"


/*
 * SevenSegDecoder_1 configuration
 *
 */

#define ALT_MODULE_CLASS_SevenSegDecoder_1 SevenSegDecoder
#define SEVENSEGDECODER_1_BASE 0x8001070
#define SEVENSEGDECODER_1_IRQ -1
#define SEVENSEGDECODER_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEVENSEGDECODER_1_NAME "/dev/SevenSegDecoder_1"
#define SEVENSEGDECODER_1_SPAN 16
#define SEVENSEGDECODER_1_TYPE "SevenSegDecoder"


/*
 * SevenSegDecoder_2 configuration
 *
 */

#define ALT_MODULE_CLASS_SevenSegDecoder_2 SevenSegDecoder
#define SEVENSEGDECODER_2_BASE 0x8001060
#define SEVENSEGDECODER_2_IRQ -1
#define SEVENSEGDECODER_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEVENSEGDECODER_2_NAME "/dev/SevenSegDecoder_2"
#define SEVENSEGDECODER_2_SPAN 16
#define SEVENSEGDECODER_2_TYPE "SevenSegDecoder"


/*
 * SevenSegDecoder_3 configuration
 *
 */

#define ALT_MODULE_CLASS_SevenSegDecoder_3 SevenSegDecoder
#define SEVENSEGDECODER_3_BASE 0x8001030
#define SEVENSEGDECODER_3_IRQ -1
#define SEVENSEGDECODER_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEVENSEGDECODER_3_NAME "/dev/SevenSegDecoder_3"
#define SEVENSEGDECODER_3_SPAN 16
#define SEVENSEGDECODER_3_TYPE "SevenSegDecoder"


/*
 * SevenSegDecoder_4 configuration
 *
 */

#define ALT_MODULE_CLASS_SevenSegDecoder_4 SevenSegDecoder
#define SEVENSEGDECODER_4_BASE 0x8001050
#define SEVENSEGDECODER_4_IRQ -1
#define SEVENSEGDECODER_4_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEVENSEGDECODER_4_NAME "/dev/SevenSegDecoder_4"
#define SEVENSEGDECODER_4_SPAN 16
#define SEVENSEGDECODER_4_TYPE "SevenSegDecoder"


/*
 * SevenSegDecoder_5 configuration
 *
 */

#define ALT_MODULE_CLASS_SevenSegDecoder_5 SevenSegDecoder
#define SEVENSEGDECODER_5_BASE 0x8001040
#define SEVENSEGDECODER_5_IRQ -1
#define SEVENSEGDECODER_5_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEVENSEGDECODER_5_NAME "/dev/SevenSegDecoder_5"
#define SEVENSEGDECODER_5_SPAN 16
#define SEVENSEGDECODER_5_TYPE "SevenSegDecoder"


/*
 * Switches_0 configuration
 *
 */

#define ALT_MODULE_CLASS_Switches_0 Switches
#define SWITCHES_0_BASE 0x8001090
#define SWITCHES_0_IRQ -1
#define SWITCHES_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SWITCHES_0_NAME "/dev/Switches_0"
#define SWITCHES_0_SPAN 16
#define SWITCHES_0_TYPE "Switches"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone V"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/DEBUG"
#define ALT_STDERR_BASE 0x80010b0
#define ALT_STDERR_DEV DEBUG
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/DEBUG"
#define ALT_STDIN_BASE 0x80010b0
#define ALT_STDIN_DEV DEBUG
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/DEBUG"
#define ALT_STDOUT_BASE 0x80010b0
#define ALT_STDOUT_DEV DEBUG
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "CST455_Midterm"
#define ALT_SYS_CLK_TICKS_PER_SEC SYS_CLK_TICKS_PER_SEC
#define ALT_TIMESTAMP_CLK_TIMER_DEVICE_TYPE NONE_TIMER_DEVICE_TYPE


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK SYS_CLK
#define ALT_TIMESTAMP_CLK none


/*
 * sys_clk configuration
 *
 */

#define ALT_MODULE_CLASS_sys_clk altera_avalon_timer
#define SYS_CLK_ALWAYS_RUN 0
#define SYS_CLK_BASE 0x8001000
#define SYS_CLK_COUNTER_SIZE 32
#define SYS_CLK_FIXED_PERIOD 0
#define SYS_CLK_FREQ 50000000
#define SYS_CLK_IRQ 0
#define SYS_CLK_IRQ_INTERRUPT_CONTROLLER_ID 0
#define SYS_CLK_LOAD_VALUE 49999
#define SYS_CLK_MULT 0.001
#define SYS_CLK_NAME "/dev/sys_clk"
#define SYS_CLK_PERIOD 1
#define SYS_CLK_PERIOD_UNITS "ms"
#define SYS_CLK_RESET_OUTPUT 0
#define SYS_CLK_SNAPSHOT 1
#define SYS_CLK_SPAN 32
#define SYS_CLK_TICKS_PER_SEC 1000
#define SYS_CLK_TIMEOUT_PULSE_OUTPUT 0
#define SYS_CLK_TIMER_DEVICE_TYPE 1
#define SYS_CLK_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
