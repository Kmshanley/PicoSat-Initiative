################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/JPEG/jpeg_utils.c 

OBJS += \
./Utilities/JPEG/jpeg_utils.o 

C_DEPS += \
./Utilities/JPEG/jpeg_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/JPEG/%.o Utilities/JPEG/%.su: ../Utilities/JPEG/%.c Utilities/JPEG/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H7A3xxQ -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Utilities/JPEG -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Code/picoSat_cameraTest/Drivers/stm32-ov5640-main" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utilities-2f-JPEG

clean-Utilities-2f-JPEG:
	-$(RM) ./Utilities/JPEG/jpeg_utils.d ./Utilities/JPEG/jpeg_utils.o ./Utilities/JPEG/jpeg_utils.su

.PHONY: clean-Utilities-2f-JPEG

