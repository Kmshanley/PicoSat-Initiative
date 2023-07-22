################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/TMP117/TMP117.c 

OBJS += \
./Drivers/TMP117/TMP117.o 

C_DEPS += \
./Drivers/TMP117/TMP117.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/TMP117/%.o Drivers/TMP117/%.su Drivers/TMP117/%.cyclo: ../Drivers/TMP117/%.c Drivers/TMP117/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I"D:/Code/devBoardTest/Drivers/INA236" -I"D:/Code/devBoardTest/Drivers/PCA9543" -I"D:/Code/devBoardTest/Drivers/TMP117" -I"D:/Code/devBoardTest/Drivers/APS6408" -I"D:/Code/devBoardTest/Drivers/W25Nxx" -I"D:/Code/devBoardTest/Drivers/MAX17262" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-TMP117

clean-Drivers-2f-TMP117:
	-$(RM) ./Drivers/TMP117/TMP117.cyclo ./Drivers/TMP117/TMP117.d ./Drivers/TMP117/TMP117.o ./Drivers/TMP117/TMP117.su

.PHONY: clean-Drivers-2f-TMP117

