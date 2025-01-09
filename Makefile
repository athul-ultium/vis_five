
CC=riscv64-linux-gnu-gcc
CC=riscv64-unknown-linux-gnu-gcc
CC=riscv64-unknown-elf-gcc
AS=riscv64-linux-gnu-as
AS=riscv64-unknown-elf-as
OBJ_COPY=riscv64-linux-gnu-objcopy

CFLAGS = -Wall -g -O1
CFLAGS+=-march=rv64gc -mabi=lp64d
LD_FLAGS =  -nostartfiles -T config/link.ld 

SRC_DIR = src
INCL_DIR += -Iinc 
#		    -IthreadX_inc
BDIR = build

include build_env.mak


ifeq ($(BUILT_THREADX_OS),1)
	CFLAGS+= -DThreadOS
	INCL_DIR += -IthreadX_inc
	ADD_LIB = -l$(LIB)
endif

OBJ = $(SRC:.c=.o)

TARGET = $(BDIR)/firmware.elf
TARGET_BIN = $(BDIR)/firmware.bin
TARGET_IMG = $(BDIR)/firmware.img

all: clean $(OBJ) $(TARGET) $(TARGET_BIN) $(TARGET_IMG) flash

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) $(INCL_DIR) $(ADD_LIB) -c $< -o $@

startup/Start.o: startup/Start.s
	$(AS)  $< -c -o $@

#startup/tx_initialize_low_level.o: startup/tx_initialize_low_level.S
#	$(AS)  $< -c -o $@

$(TARGET): startup/Start.o $(OBJ)
	mkdir -p $(BDIR)
	$(CC) $(CFLAGS) $(LD_FLAGS) $^ -o $@ -I$(INCL_DIR)

$(TARGET_BIN):$(TARGET)
	$(OBJ_COPY) $< -O binary $@

$(TARGET_IMG):$(TARGET_BIN)
	../blog-code/2-baremetal-visionfive/tools/vf2-imager/vf2-imager -i $< -o $@

flash:
	../blog-code/2-baremetal-visionfive/tools/vf2/vf2 $(TARGET_IMG)

clean:
	rm -rf $(OBJ)
	rm -rf $(BDIR)
	rm -rf startup/Start.o
