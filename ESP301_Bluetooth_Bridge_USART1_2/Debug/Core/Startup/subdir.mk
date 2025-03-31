################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f411ceux.s 

OBJS += \
./Core/Startup/startup_stm32f411ceux.o 

S_DEPS += \
./Core/Startup/startup_stm32f411ceux.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/efo_s.EFO-FARIAS-2/STM32CubeIDE/Wokspace_1.18.0/ESP301_Bluetooth_Bridge_USART1_2/Drivers/STM32F4xx_HAL_Driver/Inc" -IC:/Users/efo_s.EFO-FARIAS-2/STM32CubeIDE/Wokspace_1.18.0/ESP301_Bluetooth_Bridge_USART1_2/Drivers/CMSIS/Device/ST/STM32F4xx/Include -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f411ceux.d ./Core/Startup/startup_stm32f411ceux.o

.PHONY: clean-Core-2f-Startup

