################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/W25Nxx/W25Nxx.c 

OBJS += \
./Drivers/W25Nxx/W25Nxx.o 

C_DEPS += \
./Drivers/W25Nxx/W25Nxx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/W25Nxx/%.o Drivers/W25Nxx/%.su Drivers/W25Nxx/%.cyclo: ../Drivers/W25Nxx/%.c Drivers/W25Nxx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"D:/Code/devBoardTest/Drivers/INA236" -I"D:/Code/devBoardTest/Drivers/PCA9543" -I"D:/Code/devBoardTest/Drivers/TMP117" -I"D:/Code/devBoardTest/Drivers/APS6408" -I"D:/Code/devBoardTest/Drivers/W25Nxx" -I"D:/Code/devBoardTest/Drivers/MAX17262" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-W25Nxx

clean-Drivers-2f-W25Nxx:
	-$(RM) ./Drivers/W25Nxx/W25Nxx.cyclo ./Drivers/W25Nxx/W25Nxx.d ./Drivers/W25Nxx/W25Nxx.o ./Drivers/W25Nxx/W25Nxx.su

.PHONY: clean-Drivers-2f-W25Nxx

