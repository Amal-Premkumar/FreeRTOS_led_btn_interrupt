################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/led_btn_interrupt.c \
../src/system_stm32f4xx.c 

OBJS += \
./src/led_btn_interrupt.o \
./src/system_stm32f4xx.o 

C_DEPS += \
./src/led_btn_interrupt.d \
./src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o src/%.su src/%.cyclo: ../src/%.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F40_41xxx -DSTM32F407xx -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I"C:/Users/Amal/RTOS_workspace/FreeRTOS/CMSIS/device" -I"C:/Users/Amal/RTOS_workspace/FreeRTOS/CMSIS/core" -I"C:/Users/Amal/RTOS_workspace/FreeRTOS/STM32_FreeRTOS_StdPeriph_Driver/inc" -I"C:/Users/Amal/RTOS_workspace/FreeRTOS/config" -I"C:/Users/Amal/RTOS_workspace/FreeRTOS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/Amal/RTOS_workspace/FreeRTOS/inc" -I"C:/Users/Amal/RTOS_workspace/FreeRTOS/ThirdParty/FreeRTOS/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src

clean-src:
	-$(RM) ./src/led_btn_interrupt.cyclo ./src/led_btn_interrupt.d ./src/led_btn_interrupt.o ./src/led_btn_interrupt.su ./src/system_stm32f4xx.cyclo ./src/system_stm32f4xx.d ./src/system_stm32f4xx.o ./src/system_stm32f4xx.su

.PHONY: clean-src

