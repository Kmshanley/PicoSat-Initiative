################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ov5640/ov5640.c 

OBJS += \
./Drivers/ov5640/ov5640.o 

C_DEPS += \
./Drivers/ov5640/ov5640.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ov5640/%.o Drivers/ov5640/%.su: ../Drivers/ov5640/%.c Drivers/ov5640/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H7A3xxQ -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/shanleyk/Code/picoSat_cameraTest/Drivers/ov5640" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ov5640

clean-Drivers-2f-ov5640:
	-$(RM) ./Drivers/ov5640/ov5640.d ./Drivers/ov5640/ov5640.o ./Drivers/ov5640/ov5640.su

.PHONY: clean-Drivers-2f-ov5640

