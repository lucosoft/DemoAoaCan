################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AndroidAccessoryCommands.c \
../src/ConfigDescriptor.c \
../src/DeviceDescriptor.c 

OBJS += \
./src/AndroidAccessoryCommands.o \
./src/ConfigDescriptor.o \
./src/DeviceDescriptor.o 

C_DEPS += \
./src/AndroidAccessoryCommands.d \
./src/ConfigDescriptor.d \
./src/DeviceDescriptor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -DUSB_HOST_ONLY -D__LPC17XX__ -D__CODE_RED -D__REDLIB__ -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_CMSISv2p00_LPC17xx\inc" -I"D:\Td2WorkspaceTest\DemoAoaCan\nxpUSBlib\Drivers\USB" -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_Board\inc" -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_AOA\inc" -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_MCU\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


