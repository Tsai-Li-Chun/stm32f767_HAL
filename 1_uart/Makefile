# ------------------------------------------------
#	Generic Makefile (based on gcc)
#	Author	：Tsai,Li-chun
#	OS		：Ubuntu20.04 TLS
#	Brief	：modify from STM32cubeMX
# ------------------------------------------------

######################################
#	target
######################################
TARGET = 1_uart

######################################
#	building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -O0

#######################################
#	Build file paths
#######################################
BUILD_DIR = build

######################################
#	source code
######################################
# STM32F7 HAL-Driver C sources
C_SOURCES_tmp = \
../STM32F767_Library/STM32F7xx_HAL_Driver/Src
C_SOURCES =  \
$(C_SOURCES_tmp)/stm32f7xx_hal.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_cortex.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_exti.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_pwr.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_pwr_ex.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_tim.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_tim_ex.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_rcc.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_rcc_ex.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_flash.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_flash_ex.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_gpio.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_dma.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_dma_ex.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_i2c.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_i2c_ex.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_uart.c \
$(C_SOURCES_tmp)/stm32f7xx_hal_uart_ex.c \
# User C sources
C_SOURCES +=  \
User/Src/system_stm32f7xx.c \
User/Src/stm32f7xx_hal_msp.c \
User/Src/stm32f7xx_it.c \
User/Src/main.c \
User/Src/gpio.c \
User/Src/tim.c \
User/Src/uart.c \
User/Src/AF_printf.c \
User/Src/dma.c

# ASM sources
ASM_SOURCES =  \
../STM32F767_Library/startup_stm32f767xx.s

#######################################
#	binaries command
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

# cpu
CPU = -mcpu=cortex-m7

# fpu
FPU = -mfpu=fpv5-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# AS includes
AS_INCLUDES = 

#######################################
#	C defines
#######################################
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F767xx

#######################################
#	C includes
#######################################
C_INCLUDES_tmp = \
../STM32F767_Library
C_INCLUDES_tmp1 = \
$(C_INCLUDES_tmp)/STM32F7xx_HAL_Driver
C_INCLUDES_tmp2 = \
$(C_INCLUDES_tmp)/STM32F7xx_StartUp
C_INCLUDES =  \
-IUser/Inc \
-I$(C_INCLUDES_tmp)/CMSIS \
-I$(C_INCLUDES_tmp1)/Inc \
-I$(C_INCLUDES_tmp1)/Inc/Legacy \
-I$(C_INCLUDES_tmp2)/Include

#######################################
#	compile gcc flags
#######################################
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
CFLAGS  = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# ld & flags
#######################################
# link script
LDSCRIPT = \
../STM32F767_Library/STM32F767IGTx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections


#######################################
# default action: build all
######################################
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	@$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		


######################################
#	System OS
#	OS = "ubuntu" or "windows"
######################################
OS = ubuntu
ifeq ($(OS), ubuntu)
	download_cmd = /opt/stm32flash/./stm32flash -w $(BUILD_DIR)/$(TARGET).bin -v -g 0x0 /dev/ttyUSB0
endif
ifeq ($(OS), windows)
	download_cmd = STM32_Programmer_CLI -c port=SWD -w $(BUILD_DIR)/.\$(TARGET).bin 0x8000000
endif
# st-info --probe
# st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000
#######################################
# .PHONY
#######################################
clean:
	-rm -fR $(BUILD_DIR)
flash:
	st-flash write $(BUILD_DIR)/$(TARGET).bin 0x8000000
	st-flash reset
info:
	st-info --probe
.PHONY:all clean flash info

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
