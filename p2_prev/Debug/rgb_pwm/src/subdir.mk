################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rgb_pwm/src/rgb_pwm.c 

OBJS += \
./rgb_pwm/src/rgb_pwm.o 

C_DEPS += \
./rgb_pwm/src/rgb_pwm.d 


# Each subdirectory must supply rules for building sources it contributes
rgb_pwm/src/%.o rgb_pwm/src/%.su rgb_pwm/src/%.cyclo: ../rgb_pwm/src/%.c rgb_pwm/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Programming/Microcontroladores/p2_prev/rgb_pwm/inc" -I"D:/Programming/Microcontroladores/p2_prev/at24c_xxx/inc" -I"D:/Programming/Microcontroladores/p2_prev/xprintf/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-rgb_pwm-2f-src

clean-rgb_pwm-2f-src:
	-$(RM) ./rgb_pwm/src/rgb_pwm.cyclo ./rgb_pwm/src/rgb_pwm.d ./rgb_pwm/src/rgb_pwm.o ./rgb_pwm/src/rgb_pwm.su

.PHONY: clean-rgb_pwm-2f-src

