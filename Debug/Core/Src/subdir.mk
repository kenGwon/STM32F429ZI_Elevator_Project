################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/I2C_lcd.c \
../Core/Src/button.c \
../Core/Src/callback_management.c \
../Core/Src/dotmatrix.c \
../Core/Src/elevator_loopmonitor.c \
../Core/Src/elevator_os.c \
../Core/Src/fnd.c \
../Core/Src/freertos.c \
../Core/Src/main.c \
../Core/Src/stepmotor.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_hal_timebase_tim.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/timer_management.c 

OBJS += \
./Core/Src/I2C_lcd.o \
./Core/Src/button.o \
./Core/Src/callback_management.o \
./Core/Src/dotmatrix.o \
./Core/Src/elevator_loopmonitor.o \
./Core/Src/elevator_os.o \
./Core/Src/fnd.o \
./Core/Src/freertos.o \
./Core/Src/main.o \
./Core/Src/stepmotor.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_hal_timebase_tim.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/timer_management.o 

C_DEPS += \
./Core/Src/I2C_lcd.d \
./Core/Src/button.d \
./Core/Src/callback_management.d \
./Core/Src/dotmatrix.d \
./Core/Src/elevator_loopmonitor.d \
./Core/Src/elevator_os.d \
./Core/Src/fnd.d \
./Core/Src/freertos.d \
./Core/Src/main.d \
./Core/Src/stepmotor.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_hal_timebase_tim.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/timer_management.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/I2C_lcd.cyclo ./Core/Src/I2C_lcd.d ./Core/Src/I2C_lcd.o ./Core/Src/I2C_lcd.su ./Core/Src/button.cyclo ./Core/Src/button.d ./Core/Src/button.o ./Core/Src/button.su ./Core/Src/callback_management.cyclo ./Core/Src/callback_management.d ./Core/Src/callback_management.o ./Core/Src/callback_management.su ./Core/Src/dotmatrix.cyclo ./Core/Src/dotmatrix.d ./Core/Src/dotmatrix.o ./Core/Src/dotmatrix.su ./Core/Src/elevator_loopmonitor.cyclo ./Core/Src/elevator_loopmonitor.d ./Core/Src/elevator_loopmonitor.o ./Core/Src/elevator_loopmonitor.su ./Core/Src/elevator_os.cyclo ./Core/Src/elevator_os.d ./Core/Src/elevator_os.o ./Core/Src/elevator_os.su ./Core/Src/fnd.cyclo ./Core/Src/fnd.d ./Core/Src/fnd.o ./Core/Src/fnd.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stepmotor.cyclo ./Core/Src/stepmotor.d ./Core/Src/stepmotor.o ./Core/Src/stepmotor.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_hal_timebase_tim.cyclo ./Core/Src/stm32f4xx_hal_timebase_tim.d ./Core/Src/stm32f4xx_hal_timebase_tim.o ./Core/Src/stm32f4xx_hal_timebase_tim.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/timer_management.cyclo ./Core/Src/timer_management.d ./Core/Src/timer_management.o ./Core/Src/timer_management.su

.PHONY: clean-Core-2f-Src

