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
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
arduino_zsprinter.elf.size \


# All Target
all: arduino_zsprinter.elf secondary-outputs

# Tool invocations
arduino_zsprinter.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MicroBlaze g++ linker'
	mb-g++ -Wl,-T -Wl,../src/lscript.ld -I../../bsp_iop_arduino/iop_arduino_mb/include -L../../bsp_iop_arduino/iop_arduino_mb/lib -mlittle-endian -mcpu=v10.0 -mxl-soft-mul -Wl,--no-relax -o "arduino_zsprinter.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

arduino_zsprinter.elf.size: arduino_zsprinter.elf
	@echo 'Invoking: MicroBlaze Print Size'
	mb-size arduino_zsprinter.elf  |tee "arduino_zsprinter.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

arduino_zsprinter.bin: arduino_zsprinter.elf
	@echo 'Invoking: MicroBlaze Bin Gen'
	mb-objcopy -O binary arduino_zsprinter.elf arduino_zsprinter.bin
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-@echo 'dummy clean (because Xilinx SDK executes make clean all the time)'
	-@echo 'if you really clean, use make mrproper instead.'

mrproper:
	-$(RM) $(EXECUTABLES)$(OBJS)$(S_UPPER_DEPS)$(C_DEPS)$(ELFSIZE) arduino_zsprinter.elf arduino_zsprinter.bin
	-@echo ' '

reload:
	git stash
	git pull origin master
	make mrproper
	make 
	cp arduino_zsprinter.bin ~/pynq/lib/arduino

update:
	make mrproper && make && cp arduino_zsprinter.bin ~/pynq/lib/arduino

secondary-outputs: $(ELFSIZE) arduino_zsprinter.bin

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
