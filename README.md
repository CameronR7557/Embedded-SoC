Labs and term project from an SoC class I took. 
The board used in all of the projects was an Altera DE1-SoC. Some labs used the FPGA alone, others used the FPGA + NIOS II soft-core processor and FreeRTOS, and some used the FPGA + ARM hard-core processor and an embedded Linux OS. 
Nearly every project folder has an RTL and Questa folder with the RTL diagrams and Questa simulation results like those shown here:

Questa Simulation for a Fibonacci Sequence:

<img width="1400" height="600" alt="FibonacciSeq_Sim" src="https://github.com/user-attachments/assets/410e57b9-678b-4e6b-8783-3fd591f3df8e" />

LED Controll HW Accelerator RTL:

<img width="1023" height="343" alt="image" src="https://github.com/user-attachments/assets/515751f4-ba9d-4cc1-8ee7-aa1b8b5645de" />

For my term project, I created custom HW accelerators and SW running on the hard-core processor w/ embedded Linux. The project read in a constant stream of data from a 2D LiDAR through UART, checked the data with a CRC, and sent it to the processor which displayed the data on an LCD.
More details on the project can be found in the proposal and final report PDFs.

Project test setup:

<img width="701" height="386" alt="image" src="https://github.com/user-attachments/assets/bad529ef-8496-4525-b600-df25df1b9b60" />

Example LCD display:

<img width="401" height="405" alt="image" src="https://github.com/user-attachments/assets/b0cf22fe-f932-4c1e-b17c-1f889fbbfb7c" />

Top-level custom UART RX HW accelerator:

<img width="934" height="338" alt="image" src="https://github.com/user-attachments/assets/020c8667-16a6-42b8-b9b7-d76d534abc81" />


