############################################################
# Project
############################################################
PROJECT = F4
TARGET  = cortex-m4


############################################################
# Compiler Options
############################################################
OPTIMIZATION = s
STANDARD     = c11


############################################################
# Directories
############################################################
BUILD_DIR     = ./build
DRIVERS_DIR   = ./drivers
INCLUDE_DIR   = ./include ./drivers/cmsis/include ./drivers/stm32f4xx/include ./drivers/stm32f4xx_hal/include
LIBRARIES_DIR = ./lib
SOURCE_DIR    = ./src


############################################################
# Tools
############################################################
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
LD = arm-none-eabi-gcc
GDB = arm-none-eabi-gdb
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
REMOVE  = rm -rvf


############################################################
# Source Files
############################################################
GCC_SOURCES  = $(shell find $(DRIVERS_DIR) -type f -name '*.c')
GCC_SOURCES += $(shell find $(SOURCE_DIR) -type f -name '*.c')

AS_SOURCES   = $(shell find $(DRIVERS_DIR) -type f -name '*.S')
AS_SOURCES  += $(shell find $(SOURCE_DIR) -type f -name '*.S')

OBJECTS = $(GCC_SOURCES:.c=.o) $(AS_SOURCES:.S=.o)


############################################################
# Tool Flags
############################################################
GCC_FLAGS  = -g -std=$(STANDARD) -mcpu=$(TARGET) -march=armv7e-m -mthumb -O$(OPTIMIZATION) -mfpu=fpv4-sp-d16 -mfloat-abi=hard -lstm32f3 -Tstm32f3.ld -ffunction-sections -fdata-sections -Wall -Wstrict-prototypes
GCC_FLAGS += $(patsubst %,-I%,$(INCLUDE_DIR)) -I.

LD_FLAGS  = -mcpu=$(TARGET) -march=armv7e-m -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard  --specs=nosys.specs -Lld -Tstm32_flash.ld
LD_FLAGS += $(patsubst %,-I%,$(INCLUDE_DIR)) -I.


############################################################
# Targets: Actions
############################################################
.SUFFIXES: .c .eep .h .hex .o .elf .s .S
.PHONY: all disasm hex upload clean

all: $(BUILD_DIR)/$(PROJECT).elf

clean:
	@echo
	@echo "\033[01;32mCLEAN\033[00m *.o *.s *.out *.hex *.eep\033[01;37m"
	@echo "find . \( -type f -name '*.o' -o -name '*.s' -o -name '*.out' -o -name '*.hex' \) -exec $(REMOVE) {} \;\033[01;35m"
	@find . \( -type f -name '*.o' -o -name '*.s' -o -name '*.out' -o -name '*.hex' \) -exec $(REMOVE) {} \;


############################################################
# Targets: Output
############################################################
$(BUILD_DIR)/$(PROJECT).elf: $(OBJECTS)
	@echo
	@echo "\033[01;32mLD\033[00m $@\033[01;37m"
	@echo "$(LD) -o $@ $(OBJECTS) $(LD_FLAGS)\033[01;35m"
	@$(LD) -o $@ $(OBJECTS) $(LD_FLAGS)

%.o: %.c
	@echo
	@echo "\033[01;32mCC\033[00m $<\033[01;37m"
	@echo "$(CC) $(GCC_FLAGS) -c $< -o $@\033[01;35m"
	@$(CC) $(GCC_FLAGS) -c $< -o $@
	

%.o: %.S
	@echo
	@echo "\033[01;32mAS\033[00m $<\033[01;37m"
	@echo "$(CC) $(AS_FLAGS) -c $< -o $@\033[01;35m"
	@$(CC) $(AS_FLAGS) -c $< -o $@
