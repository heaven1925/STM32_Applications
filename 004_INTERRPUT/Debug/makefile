################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
004_INTERRPUT.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
004_INTERRPUT.list \

OBJCOPY_BIN += \
004_INTERRPUT.bin \


# All Target
all: 004_INTERRPUT.elf secondary-outputs

# Tool invocations
004_INTERRPUT.elf: $(OBJS) $(USER_OBJS) C:\Users\atakan\Desktop\WorkSpace\004_INTERRPUT\STM32F407VGTX_FLASH.ld
	arm-none-eabi-gcc -o "004_INTERRPUT.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\atakan\Desktop\WorkSpace\004_INTERRPUT\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="004_INTERRPUT.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

004_INTERRPUT.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "004_INTERRPUT.list"
	@echo 'Finished building: $@'
	@echo ' '

004_INTERRPUT.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "004_INTERRPUT.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
