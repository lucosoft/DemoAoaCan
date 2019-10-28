################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: demo_aoa_can.axf

# Tool invocations
demo_aoa_can.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"D:\Td2WorkspaceTest\DemoAoaCan\Lib_CMSISv2p00_LPC17xx\Debug" -L"D:\Td2WorkspaceTest\DemoAoaCan\Lib_Board\Debug" -L"D:\Td2WorkspaceTest\DemoAoaCan\nxpUSBlib" -L"D:\Td2WorkspaceTest\DemoAoaCan\Lib_FatFs_SD\Debug" -L"D:\Td2WorkspaceTest\DemoAoaCan\Lib_MCU\Debug" -L"D:\Td2WorkspaceTest\DemoAoaCan\Lib_AOA\Debug" -Xlinker --gc-sections -Xlinker -Map=demo_aoa_can.map -mcpu=cortex-m3 -mthumb -T "demo_aoa_can_Debug.ld" -o "demo_aoa_can.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) demo_aoa_can.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size demo_aoa_can.axf; # arm-none-eabi-objdump -h -S demo_aoa_can.axf >demo_aoa_can.lss
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
