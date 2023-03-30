################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/TCA8418RTRW_Driver/src/TCA8418RTRW.c 

OBJS += \
./Drivers/TCA8418RTRW_Driver/src/TCA8418RTRW.o 

C_DEPS += \
./Drivers/TCA8418RTRW_Driver/src/TCA8418RTRW.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/TCA8418RTRW_Driver/src/%.o Drivers/TCA8418RTRW_Driver/src/%.su: ../Drivers/TCA8418RTRW_Driver/src/%.c Drivers/TCA8418RTRW_Driver/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/AtakanErtekin/Desktop/WorkSpace/STM_WorkSpace/0013_TCAKeypadTest/Drivers/TCA8418RTRW_Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-TCA8418RTRW_Driver-2f-src

clean-Drivers-2f-TCA8418RTRW_Driver-2f-src:
	-$(RM) ./Drivers/TCA8418RTRW_Driver/src/TCA8418RTRW.d ./Drivers/TCA8418RTRW_Driver/src/TCA8418RTRW.o ./Drivers/TCA8418RTRW_Driver/src/TCA8418RTRW.su

.PHONY: clean-Drivers-2f-TCA8418RTRW_Driver-2f-src

