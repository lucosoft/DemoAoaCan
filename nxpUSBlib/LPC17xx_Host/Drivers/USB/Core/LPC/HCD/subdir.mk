################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/USB/Core/LPC/HCD/HCD.c 

OBJS += \
./Drivers/USB/Core/LPC/HCD/HCD.o 

C_DEPS += \
./Drivers/USB/Core/LPC/HCD/HCD.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/USB/Core/LPC/HCD/%.o: ../Drivers/USB/Core/LPC/HCD/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__LPC17XX__ -DUSB_HOST_ONLY -D__REDLIB__ -D__CODE_RED -I"/home/laboratorio/VirtualBox VMs/Compartida AltiumLpc_XP/Interfaz CAN/Firmware/Ubuntu/Version Ultima Aux/DemoAoaCan/Lib_CMSISv2p00_LPC17xx/inc" -I"/home/laboratorio/VirtualBox VMs/Compartida AltiumLpc_XP/Interfaz CAN/Firmware/Ubuntu/Version Ultima Aux/DemoAoaCan/Lib_MCU/inc" -Og -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -std=gnu99 -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


