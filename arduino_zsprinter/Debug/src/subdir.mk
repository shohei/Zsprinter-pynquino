################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/heater.cpp \
../src/arduino_zsprinter.cpp
# ../src/SeeedOLED.cpp \

OBJS += \
./src/heater.o \
./src/arduino_zsprinter.o 
# ./src/SeeedOLED.o \

C_DEPS += \
./src/heater.d \
./src/arduino_zsprinter.d 
# ./src/SeeedOLED.d \


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O1 -g3 -c -fmessage-length=0 -MT"$@" -L../../bsp_iop_arduino/iop_arduino_mb/lib -I../../bsp_iop_arduino/iop_arduino_mb/include -mlittle-endian -mcpu=v10.0 -mxl-soft-mul -Wl,--no-relax -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-g++ -Wall -O1 -g3 -c -fmessage-length=0 -MT"$@" -L../../bsp_iop_arduino/iop_arduino_mb/lib -I../../bsp_iop_arduino/iop_arduino_mb/include -mlittle-endian -mcpu=v10.0 -mxl-soft-mul -Wl,--no-relax -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


