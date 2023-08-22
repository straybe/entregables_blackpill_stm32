################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../at24c_xxx/src/at24c_xxx.c 

OBJS += \
./at24c_xxx/src/at24c_xxx.o 

C_DEPS += \
./at24c_xxx/src/at24c_xxx.d 


# Each subdirectory must supply rules for building sources it contributes
at24c_xxx/src/%.o at24c_xxx/src/%.su: ../at24c_xxx/src/%.c at24c_xxx/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Daniel Meneses/Documents/Curso ARM/Programas/Practicas/p2_prev/rgb_pwm/inc" -I"C:/Users/Daniel Meneses/Documents/Curso ARM/Programas/Practicas/p2_prev/at24c_xxx/inc" -I"C:/Users/Daniel Meneses/Documents/Curso ARM/Programas/Practicas/p2_prev/xprintf/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-at24c_xxx-2f-src

clean-at24c_xxx-2f-src:
	-$(RM) ./at24c_xxx/src/at24c_xxx.d ./at24c_xxx/src/at24c_xxx.o ./at24c_xxx/src/at24c_xxx.su

.PHONY: clean-at24c_xxx-2f-src

