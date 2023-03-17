################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/admin.c \
../Core/Src/buzzer_player.c \
../Core/Src/callback.c \
../Core/Src/elevator_state.c \
../Core/Src/floor.c \
../Core/Src/led_utils.c \
../Core/Src/main.c \
../Core/Src/message_sender.c \
../Core/Src/queue.c \
../Core/Src/segment_utils.c \
../Core/Src/stm32f3xx_hal_msp.c \
../Core/Src/stm32f3xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f3xx.c 

OBJS += \
./Core/Src/admin.o \
./Core/Src/buzzer_player.o \
./Core/Src/callback.o \
./Core/Src/elevator_state.o \
./Core/Src/floor.o \
./Core/Src/led_utils.o \
./Core/Src/main.o \
./Core/Src/message_sender.o \
./Core/Src/queue.o \
./Core/Src/segment_utils.o \
./Core/Src/stm32f3xx_hal_msp.o \
./Core/Src/stm32f3xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f3xx.o 

C_DEPS += \
./Core/Src/admin.d \
./Core/Src/buzzer_player.d \
./Core/Src/callback.d \
./Core/Src/elevator_state.d \
./Core/Src/floor.d \
./Core/Src/led_utils.d \
./Core/Src/main.d \
./Core/Src/message_sender.d \
./Core/Src/queue.d \
./Core/Src/segment_utils.d \
./Core/Src/stm32f3xx_hal_msp.d \
./Core/Src/stm32f3xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f3xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F303xC -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/admin.d ./Core/Src/admin.o ./Core/Src/admin.su ./Core/Src/buzzer_player.d ./Core/Src/buzzer_player.o ./Core/Src/buzzer_player.su ./Core/Src/callback.d ./Core/Src/callback.o ./Core/Src/callback.su ./Core/Src/elevator_state.d ./Core/Src/elevator_state.o ./Core/Src/elevator_state.su ./Core/Src/floor.d ./Core/Src/floor.o ./Core/Src/floor.su ./Core/Src/led_utils.d ./Core/Src/led_utils.o ./Core/Src/led_utils.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/message_sender.d ./Core/Src/message_sender.o ./Core/Src/message_sender.su ./Core/Src/queue.d ./Core/Src/queue.o ./Core/Src/queue.su ./Core/Src/segment_utils.d ./Core/Src/segment_utils.o ./Core/Src/segment_utils.su ./Core/Src/stm32f3xx_hal_msp.d ./Core/Src/stm32f3xx_hal_msp.o ./Core/Src/stm32f3xx_hal_msp.su ./Core/Src/stm32f3xx_it.d ./Core/Src/stm32f3xx_it.o ./Core/Src/stm32f3xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f3xx.d ./Core/Src/system_stm32f3xx.o ./Core/Src/system_stm32f3xx.su

.PHONY: clean-Core-2f-Src

