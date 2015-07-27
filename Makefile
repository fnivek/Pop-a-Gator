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
REMOVE  = rm


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

LD_FLAGS  = -mcpu=$(TARGET) -march=armv7e-m -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard  --specs=nosys.specs -Lld
LD_FLAGS += $(patsubst %,-I%,$(INCLUDE_DIR)) -I.


############################################################
# Verbosity
############################################################
ifeq ($V, 1)
	VERBOSE =
else
	VERBOSE = @
endif


############################################################
# Targets: Actions
############################################################
.SUFFIXES: .c .eep .h .hex .o .elf .s .S
.PHONY: all disasm hex upload clean

all: flash ram

flash: $(BUILD_DIR)/$(PROJECT)_flash.elf

ram: $(BUILD_DIR)/$(PROJECT)_ram.elf

clean:
	$(VERBOSE) find . \( -type f -name '*.o' -o -name '*.s' -o -name '*.out' -o -name '*.hex' \) -exec $(REMOVE) {} \;


############################################################
# Targets: Output
############################################################
$(BUILD_DIR)/$(PROJECT)_flash.elf: $(OBJECTS)
	@echo ld $@
	$(VERBOSE) $(LD) -o $@ $(OBJECTS) $(LD_FLAGS) -Tstm32f4_flash.ld

$(BUILD_DIR)/$(PROJECT)_ram.elf: $(OBJECTS)
	@echo ld $@
	$(VERBOSE) $(LD) -o $@ $(OBJECTS) $(LD_FLAGS) -Tstm32f4_ram.ld

%.o: %.c
	@echo cc $<
	$(VERBOSE) $(CC) $(GCC_FLAGS) -c $< -o $@
	

%.o: %.S
	@echo cc $<
	$(VERBOSE) $(CC) $(AS_FLAGS) -c $< -o $@
