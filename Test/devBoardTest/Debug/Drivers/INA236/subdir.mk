################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/INA236/INA236.c 

OBJS += \
./Drivers/INA236/INA236.o 

C_DEPS += \
./Drivers/INA236/INA236.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/INA236/%.o Drivers/INA236/%.su: ../Drivers/INA236/%.c Drivers/INA236/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/zhengj2/Desktop/picosat github/PicoSat-Initiative/Test/devBoardTest/Drivers/INA236" -I"C:/Users/zhengj2/Desktop/picosat github/PicoSat-Initiative/Test/devBoardTest/Drivers/PCA9543" -I"C:/Users/zhengj2/Desktop/picosat github/PicoSat-Initiative/Test/devBoardTest/Drivers/TMP117" -I"C:/Users/zhengj2/Desktop/picosat github/PicoSat-Initiative/Test/devBoardTest/Drivers/APS6408" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-INA236

clean-Drivers-2f-INA236:
	-$(RM) ./Drivers/INA236/INA236.d ./Drivers/INA236/INA236.o ./Drivers/INA236/INA236.su

.PHONY: clean-Drivers-2f-INA236

