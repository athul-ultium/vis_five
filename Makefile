CC=riscv64-linux-gnu-gcc
AS=riscv64-linux-gnu-as
OBJ_COPY=riscv64-linux-gnu-objcopy
CFLAGS = -Wall -g -O1
CFLAGS+=-march=rv64gc -mabi=lp64d 
LD_FLAGS =  -nostartfiles 
SRC_DIR = src
INCL_DIR += -Iinc

BDIR = build

SRC += $(SRC_DIR)/init_mem.c \
	   $(SRC_DIR)/main.c \
	   $(SRC_DIR)/gpio.c \
	   $(NULL)

OBJ = $(SRC:.c=.o)

TARGET = $(BDIR)/firmware.elf
TARGET_BIN = $(BDIR)/firmware.bin
TARGET_IMG = $(BDIR)/firmware.img

all: clean $(OBJ) $(TARGET) $(TARGET_BIN) $(TARGET_IMG)

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) $(INCL_DIR) -c $< -o $@

Start.o: startup/Start.s
	$(AS)  $< -c -o $@

$(TARGET): Start.o $(OBJ)
	mkdir -p $(BDIR)
	$(CC) $(CFLAGS)  $(LD_FLAGS) -T link.ld $^ -o $@ $(INCL_DIR) 

$(TARGET_BIN):$(TARGET)
	$(OBJ_COPY) $< -O binary $@

$(TARGET_IMG):$(TARGET_BIN)
	/home/employee/sifive/bare_metal/blog-code/2-baremetal-visionfive/tools/vf2-imager/vf2-imager -i $< -o $@

clean:
	rm -rf $(OBJ)
	rm -rf $(BDIR)
