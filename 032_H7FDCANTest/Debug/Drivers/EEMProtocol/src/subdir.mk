################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/EEMProtocol/src/EEMProtocol.c 

OBJS += \
./Drivers/EEMProtocol/src/EEMProtocol.o 

C_DEPS += \
./Drivers/EEMProtocol/src/EEMProtocol.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/EEMProtocol/src/%.o Drivers/EEMProtocol/src/%.su: ../Drivers/EEMProtocol/src/%.c Drivers/EEMProtocol/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/AtakanErtekin/Desktop/WorkSpace/STM_WorkSpace/0012_H7FDCANTest/Drivers/EEMProtocol/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-EEMProtocol-2f-src

clean-Drivers-2f-EEMProtocol-2f-src:
	-$(RM) ./Drivers/EEMProtocol/src/EEMProtocol.d ./Drivers/EEMProtocol/src/EEMProtocol.o ./Drivers/EEMProtocol/src/EEMProtocol.su

.PHONY: clean-Drivers-2f-EEMProtocol-2f-src

