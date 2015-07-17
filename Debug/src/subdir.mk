################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../src/halavr.o \
../src/kernel.o \
../src/timetest.o 

C_SRCS += \
../src/halavr.c \
../src/kernel.c \
../src/timetest.c \
../src/upgrade.c \
../src/usb.c 

S_UPPER_SRCS += \
../src/crt1.S \
../src/osccalASM.S 

OBJS += \
./src/crt1.o \
./src/halavr.o \
./src/kernel.o \
./src/osccalASM.o \
./src/timetest.o \
./src/upgrade.o \
./src/usb.o 

C_DEPS += \
./src/halavr.d \
./src/kernel.d \
./src/timetest.d \
./src/upgrade.d \
./src/usb.d 

S_UPPER_DEPS += \
./src/crt1.d \
./src/osccalASM.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Assembler'
	avr-gcc -x assembler-with-cpp -g2 -gstabs -mmcu=attiny45 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Werror -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -v -save-temps -fverbose-asm -mmcu=attiny45 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


