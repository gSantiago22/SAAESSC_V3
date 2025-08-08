################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/acquisition_handler.c \
../Core/Src/adc_handler.c \
../Core/Src/comunication_handler.c \
../Core/Src/config.c \
../Core/Src/dac_handler.c \
../Core/Src/gpio_handler.c \
../Core/Src/main.c \
../Core/Src/signal_generator_handler.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/test_routines_handler.c \
../Core/Src/timer_acquisition_handler.c 

OBJS += \
./Core/Src/acquisition_handler.o \
./Core/Src/adc_handler.o \
./Core/Src/comunication_handler.o \
./Core/Src/config.o \
./Core/Src/dac_handler.o \
./Core/Src/gpio_handler.o \
./Core/Src/main.o \
./Core/Src/signal_generator_handler.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/test_routines_handler.o \
./Core/Src/timer_acquisition_handler.o 

C_DEPS += \
./Core/Src/acquisition_handler.d \
./Core/Src/adc_handler.d \
./Core/Src/comunication_handler.d \
./Core/Src/config.d \
./Core/Src/dac_handler.d \
./Core/Src/gpio_handler.d \
./Core/Src/main.d \
./Core/Src/signal_generator_handler.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/test_routines_handler.d \
./Core/Src/timer_acquisition_handler.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xE -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/acquisition_handler.cyclo ./Core/Src/acquisition_handler.d ./Core/Src/acquisition_handler.o ./Core/Src/acquisition_handler.su ./Core/Src/adc_handler.cyclo ./Core/Src/adc_handler.d ./Core/Src/adc_handler.o ./Core/Src/adc_handler.su ./Core/Src/comunication_handler.cyclo ./Core/Src/comunication_handler.d ./Core/Src/comunication_handler.o ./Core/Src/comunication_handler.su ./Core/Src/config.cyclo ./Core/Src/config.d ./Core/Src/config.o ./Core/Src/config.su ./Core/Src/dac_handler.cyclo ./Core/Src/dac_handler.d ./Core/Src/dac_handler.o ./Core/Src/dac_handler.su ./Core/Src/gpio_handler.cyclo ./Core/Src/gpio_handler.d ./Core/Src/gpio_handler.o ./Core/Src/gpio_handler.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/signal_generator_handler.cyclo ./Core/Src/signal_generator_handler.d ./Core/Src/signal_generator_handler.o ./Core/Src/signal_generator_handler.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su ./Core/Src/test_routines_handler.cyclo ./Core/Src/test_routines_handler.d ./Core/Src/test_routines_handler.o ./Core/Src/test_routines_handler.su ./Core/Src/timer_acquisition_handler.cyclo ./Core/Src/timer_acquisition_handler.d ./Core/Src/timer_acquisition_handler.o ./Core/Src/timer_acquisition_handler.su

.PHONY: clean-Core-2f-Src

