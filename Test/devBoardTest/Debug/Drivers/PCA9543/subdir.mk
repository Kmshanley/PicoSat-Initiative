################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/PCA9543/PCA9543.c 

OBJS += \
./Drivers/PCA9543/PCA9543.o 

C_DEPS += \
./Drivers/PCA9543/PCA9543.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/PCA9543/%.o Drivers/PCA9543/%.su: ../Drivers/PCA9543/%.c Drivers/PCA9543/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"D:/Code/devBoardTest/Drivers/INA236" -I"D:/Code/devBoardTest/Drivers/PCA9543" -I"D:/Code/devBoardTest/Drivers/TMP117" -I"D:/Code/devBoardTest/Drivers/APS6408" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-PCA9543

clean-Drivers-2f-PCA9543:
	-$(RM) ./Drivers/PCA9543/PCA9543.d ./Drivers/PCA9543/PCA9543.o ./Drivers/PCA9543/PCA9543.su

.PHONY: clean-Drivers-2f-PCA9543

