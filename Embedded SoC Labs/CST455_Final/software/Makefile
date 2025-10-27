TARGET = main

ALT_DEVICE_FAMILY ?= soc_cv_av
SOCEDS_ROOT ?= $(SOCEDS_DEST_ROOT)
HWLIBS_ROOT = $(SOCEDS_ROOT)/ip/altera/hps/altera_hps/hwlib
CROSS_COMPILE = arm-linux-gnueabihf-
CFLAGS = -g -Wall -D$(ALT_DEVICE_FAMILY) -I$(HWLIBS_ROOT)/include/$(ALT_DEVICE_FAMILY) -I$(HWLIBS_ROOT)/include/ -I$(HWLIBS_ROOT)/include/$(ALT_DEVICE_FAMILY)
LDFLAGS = -g -Wall -lm -lpthread
CC = $(CROSS_COMPILE)gcc
ARCH = arm
OBJS = main.o\
		taskFunctions.o

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS)	$^ -o $@
	
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -std=c99
	
.PHONY: clean
clean:
	rm -f $(TARGET) *.a *.o *~