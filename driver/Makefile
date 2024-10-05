TARGET = main

# Toolchain definition
CC = arm-none-eabi-gcc
CO = arm-none-eabi-objcopy  
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
SIZE = arm-none-eabi-size  
SF = st-flash

# Define the linker script location and chip architecture
CPU = cortex-m3
LD_SCRIPT = ../linker/stm32f103c8t6_ls.ld

# Define the include and startup location
INCLUDES = -I./Inc
STARTUP = ../startup/stm32f103c8t6_startup.s

# Define the source and obj location
SRC_DIR = ./Src
OBJ_DIR = ./obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Create the object directory if not exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Define C flags and Linker Flags
CFLAGS = -g -Wall -mcpu=$(CPU) $(INCLUDES) -mthumb -O0 
LDFLAGS = -T$(LD_SCRIPT) -mcpu=$(CPU) -mthumb -Wall -nostartfiles $(STARTUP)

# Define address for flash
FLASHADDR = 0x08000000

# Build rules
all: $(TARGET).bin

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET).elf $(LDFLAGS)
	$(SIZE) $(TARGET).elf

$(TARGET).bin: $(TARGET).elf
	$(CO) -O binary $(TARGET).elf $(TARGET).bin

flash: $(TARGET).bin
	$(SF) --reset write $(TARGET).bin $(FLASHADDR)

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET).bin $(TARGET).elf
	rm -rf $(OBJ_DIR)

.PHONY: all flash clean
