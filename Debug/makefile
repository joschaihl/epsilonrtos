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
ifneq ($(strip $(MI_DEPS)),)
-include $(MI_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(M_DEPS)),)
-include $(M_DEPS)
endif
ifneq ($(strip $(I_DEPS)),)
-include $(I_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
epsilonRTOS.lss \

FLASH_IMAGE += \
epsilonRTOS.hex \

EEPROM_IMAGE += \
epsilonRTOS.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: epsilonRTOS.elf secondary-outputs

# Tool invocations
epsilonRTOS.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,epsilonRTOS.map -mmcu=attiny45 -o "epsilonRTOS.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

epsilonRTOS.lss: epsilonRTOS.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S epsilonRTOS.elf  >"epsilonRTOS.lss"
	@echo 'Finished building: $@'
	@echo ' '

epsilonRTOS.hex: epsilonRTOS.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex epsilonRTOS.elf  "epsilonRTOS.hex"
	@echo 'Finished building: $@'
	@echo ' '

epsilonRTOS.eep: epsilonRTOS.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex epsilonRTOS.elf  "epsilonRTOS.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: epsilonRTOS.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny45 epsilonRTOS.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(MI_DEPS)$(OBJS)$(C_DEPS)$(ELFS)$(FLASH_IMAGE)$(EEPROM_IMAGE)$(LSS)$(S_DEPS)$(I_DEPS)$(S_UPPER_DEPS)$(ASM_DEPS)$(M_DEPS)$(SIZEDUMMY) epsilonRTOS.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
