################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/board.c \
../src/btn.c \
../src/canpt.c \
../src/eadebug.c \
../src/eeprom.c \
../src/rfpt.c \
../src/rgb.c \
../src/time.c \
../src/xbee.c 

OBJS += \
./src/board.o \
./src/btn.o \
./src/canpt.o \
./src/eadebug.o \
./src/eeprom.o \
./src/rfpt.o \
./src/rgb.o \
./src/time.o \
./src/xbee.o 

C_DEPS += \
./src/board.d \
./src/btn.d \
./src/canpt.d \
./src/eadebug.d \
./src/eeprom.d \
./src/rfpt.d \
./src/rgb.d \
./src/time.d \
./src/xbee.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -D__REDLIB__ -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_CMSISv2p00_LPC17xx\inc" -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_lwip\src\include" -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_lwip\port" -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_lwip\src\include\ipv4" -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_Board\inc" -I"D:\Td2WorkspaceTest\DemoAoaCan\Lib_MCU\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


