################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xprintf/src/edx_xprintf.c \
../xprintf/src/xprintf.c 

OBJS += \
./xprintf/src/edx_xprintf.o \
./xprintf/src/xprintf.o 

C_DEPS += \
./xprintf/src/edx_xprintf.d \
./xprintf/src/xprintf.d 


# Each subdirectory must supply rules for building sources it contributes
xprintf/src/%.o xprintf/src/%.su xprintf/src/%.cyclo: ../xprintf/src/%.c xprintf/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Programming/Microcontroladores/p2_prev/rgb_pwm/inc" -I"D:/Programming/Microcontroladores/p2_prev/at24c_xxx/inc" -I"D:/Programming/Microcontroladores/p2_prev/xprintf/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-xprintf-2f-src

clean-xprintf-2f-src:
	-$(RM) ./xprintf/src/edx_xprintf.cyclo ./xprintf/src/edx_xprintf.d ./xprintf/src/edx_xprintf.o ./xprintf/src/edx_xprintf.su ./xprintf/src/xprintf.cyclo ./xprintf/src/xprintf.d ./xprintf/src/xprintf.o ./xprintf/src/xprintf.su

.PHONY: clean-xprintf-2f-src

