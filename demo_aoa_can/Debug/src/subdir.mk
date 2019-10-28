################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AndroidAccessoryHost.c \
../src/GPIO.c \
../src/cr_startup_lpc17.c \
../src/main.c \
../src/pwm.c \
../src/timer.c 

OBJS += \
./src/AndroidAccessoryHost.o \
./src/GPIO.o \
./src/cr_startup_lpc17.o \
./src/main.o \
./src/pwm.o \
./src/timer.o 

C_DEPS += \
./src/AndroidAccessoryHost.d \
./src/GPIO.d \
./src/cr_startup_lpc17.d \
./src/main.d \
./src/pwm.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__LPC17XX__ -DUSB_HOST_ONLY -D__USE_CMSIS=CMSISv2p00_LPC17xx -D__CODE_RED -D__REDLIB__ -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_CMSISv2p00_LPC17xx\inc" -I"D:\Td2WorkspaceTest\DemoAoaCan\nxpUSBlib\Drivers\USB" -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_Board\inc" -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_AOA\inc" -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_MCU\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


