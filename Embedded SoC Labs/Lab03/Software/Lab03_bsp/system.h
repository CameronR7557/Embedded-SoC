/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'Lab03' in SOPC Builder design 'Lab03'
 * SOPC Builder design path: c:/Users/robin/OneDrive/Desktop/CST455/cst455-labs/Lab03/Lab03.sopcinfo
 *
 * Generated: Wed Oct 18 13:12:17 PDT 2023
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
#define ALT_CPU_BREAK_ADDR 0x00002820
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0xe
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00001020
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
#define ALT_CPU_INST_ADDR_WIDTH 0xe
#define ALT_CPU_NAME "Lab03"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00001000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00002820
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0xe
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00001020
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
#define NIOS2_INST_ADDR_WIDTH 0xe
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00001000


/*
 * DEBUG configuration
 *
 */

#define ALT_MODULE_CLASS_DEBUG altera_avalon_jtag_uart
#define DEBUG_BASE 0x3070
#define DEBUG_IRQ 0
#define DEBUG_IRQ_INTERRUPT_CONTROLLER_ID 0
#define DEBUG_NAME "/dev/DEBUG"
#define DEBUG_READ_DEPTH 64
#define DEBUG_READ_THRESHOLD 8
#define DEBUG_SPAN 8
#define DEBUG_TYPE "altera_avalon_jtag_uart"
#define DEBUG_WRITE_DEPTH 64
#define DEBUG_WRITE_THRESHOLD 8


/*
 * DISPLAY0 configuration
 *
 */

#define ALT_MODULE_CLASS_DISPLAY0 altera_avalon_pio
#define DISPLAY0_BASE 0x3040
#define DISPLAY0_BIT_CLEARING_EDGE_REGISTER 0
#define DISPLAY0_BIT_MODIFYING_OUTPUT_REGISTER 1
#define DISPLAY0_CAPTURE 0
#define DISPLAY0_DATA_WIDTH 7
#define DISPLAY0_DO_TEST_BENCH_WIRING 0
#define DISPLAY0_DRIVEN_SIM_VALUE 0
#define DISPLAY0_EDGE_TYPE "NONE"
#define DISPLAY0_FREQ 50000000
#define DISPLAY0_HAS_IN 0
#define DISPLAY0_HAS_OUT 1
#define DISPLAY0_HAS_TRI 0
#define DISPLAY0_IRQ -1
#define DISPLAY0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DISPLAY0_IRQ_TYPE "NONE"
#define DISPLAY0_NAME "/dev/DISPLAY0"
#define DISPLAY0_RESET_VALUE 127
#define DISPLAY0_SPAN 32
#define DISPLAY0_TYPE "altera_avalon_pio"


/*
 * DISPLAY1 configuration
 *
 */

#define ALT_MODULE_CLASS_DISPLAY1 altera_avalon_pio
#define DISPLAY1_BASE 0x3020
#define DISPLAY1_BIT_CLEARING_EDGE_REGISTER 0
#define DISPLAY1_BIT_MODIFYING_OUTPUT_REGISTER 1
#define DISPLAY1_CAPTURE 0
#define DISPLAY1_DATA_WIDTH 7
#define DISPLAY1_DO_TEST_BENCH_WIRING 0
#define DISPLAY1_DRIVEN_SIM_VALUE 0
#define DISPLAY1_EDGE_TYPE "NONE"
#define DISPLAY1_FREQ 50000000
#define DISPLAY1_HAS_IN 0
#define DISPLAY1_HAS_OUT 1
#define DISPLAY1_HAS_TRI 0
#define DISPLAY1_IRQ -1
#define DISPLAY1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DISPLAY1_IRQ_TYPE "NONE"
#define DISPLAY1_NAME "/dev/DISPLAY1"
#define DISPLAY1_RESET_VALUE 127
#define DISPLAY1_SPAN 32
#define DISPLAY1_TYPE "altera_avalon_pio"


/*
 * DISPLAY2 configuration
 *
 */

#define ALT_MODULE_CLASS_DISPLAY2 altera_avalon_pio
#define DISPLAY2_BASE 0x3000
#define DISPLAY2_BIT_CLEARING_EDGE_REGISTER 0
#define DISPLAY2_BIT_MODIFYING_OUTPUT_REGISTER 1
#define DISPLAY2_CAPTURE 0
#define DISPLAY2_DATA_WIDTH 7
#define DISPLAY2_DO_TEST_BENCH_WIRING 0
#define DISPLAY2_DRIVEN_SIM_VALUE 0
#define DISPLAY2_EDGE_TYPE "NONE"
#define DISPLAY2_FREQ 50000000
#define DISPLAY2_HAS_IN 0
#define DISPLAY2_HAS_OUT 1
#define DISPLAY2_HAS_TRI 0
#define DISPLAY2_IRQ -1
#define DISPLAY2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DISPLAY2_IRQ_TYPE "NONE"
#define DISPLAY2_NAME "/dev/DISPLAY2"
#define DISPLAY2_RESET_VALUE 127
#define DISPLAY2_SPAN 32
#define DISPLAY2_TYPE "altera_avalon_pio"


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_NIOS2_GEN2


/*
 * SRAM configuration
 *
 */

#define ALT_MODULE_CLASS_SRAM altera_avalon_onchip_memory2
#define SRAM_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define SRAM_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define SRAM_BASE 0x1000
#define SRAM_CONTENTS_INFO ""
#define SRAM_DUAL_PORT 0
#define SRAM_GUI_RAM_BLOCK_TYPE "AUTO"
#define SRAM_INIT_CONTENTS_FILE "Lab03_SRAM"
#define SRAM_INIT_MEM_CONTENT 1
#define SRAM_INSTANCE_ID "NONE"
#define SRAM_IRQ -1
#define SRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SRAM_NAME "/dev/SRAM"
#define SRAM_NON_DEFAULT_INIT_FILE_ENABLED 0
#define SRAM_RAM_BLOCK_TYPE "AUTO"
#define SRAM_READ_DURING_WRITE_MODE "DONT_CARE"
#define SRAM_SINGLE_CLOCK_OP 0
#define SRAM_SIZE_MULTIPLE 1
#define SRAM_SIZE_VALUE 4096
#define SRAM_SPAN 4096
#define SRAM_TYPE "altera_avalon_onchip_memory2"
#define SRAM_WRITABLE 1


/*
 * SW configuration
 *
 */

#define ALT_MODULE_CLASS_SW altera_avalon_pio
#define SW_BASE 0x3060
#define SW_BIT_CLEARING_EDGE_REGISTER 0
#define SW_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SW_CAPTURE 1
#define SW_DATA_WIDTH 10
#define SW_DO_TEST_BENCH_WIRING 1
#define SW_DRIVEN_SIM_VALUE 0
#define SW_EDGE_TYPE "ANY"
#define SW_FREQ 50000000
#define SW_HAS_IN 1
#define SW_HAS_OUT 0
#define SW_HAS_TRI 0
#define SW_IRQ -1
#define SW_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SW_IRQ_TYPE "NONE"
#define SW_NAME "/dev/SW"
#define SW_RESET_VALUE 0
#define SW_SPAN 16
#define SW_TYPE "altera_avalon_pio"


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
#define ALT_STDERR_BASE 0x3070
#define ALT_STDERR_DEV DEBUG
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/DEBUG"
#define ALT_STDIN_BASE 0x3070
#define ALT_STDIN_DEV DEBUG
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/DEBUG"
#define ALT_STDOUT_BASE 0x3070
#define ALT_STDOUT_DEV DEBUG
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "Lab03"
#define ALT_SYS_CLK_TICKS_PER_SEC NONE_TICKS_PER_SEC
#define ALT_TIMESTAMP_CLK_TIMER_DEVICE_TYPE NONE_TIMER_DEVICE_TYPE


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none

#endif /* __SYSTEM_H_ */
