
TARGET = main
LD_SCRIPT = ../linker/stm32f103c8t6_ls.ld
MCU_SPEC = cortex-m3
STARTUP = ../startup/stm32f103c8t6_startup.c

CC = arm-none-eabi-gcc
OC = arm-none-eabi-objcopy
SF = st-flash

CFLAGS = -mcpu=$(MCU_SPEC) -Wall -mthumb -g  
LDFLAGS = -T $(LD_SCRIPT) $(STARTUP) -Wall -nostartfiles -nostdlib --specs nano.specs -lc -lgcc -Wl,--gc-sections 


FLASHADDR = 0x08000000




$(TARGET).elf: $(TARGET).c
	$(CC) $(TARGET).c $(CFLAGS) -o $(TARGET).elf $(LDFLAGS)

$(TARGET).bin: $(TARGET).elf
	$(OC) -O binary $(TARGET).elf $(TARGET).bin

flash: $(TARGET).bin
	$(SF) --reset write $(TARGET).bin $(FLASHADDR)

clean:
	rm -f $(TARGET).bin $(TARGET).elf

all: $(TARGET).bin

.PHONY: all flash clean
