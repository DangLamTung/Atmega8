################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../lcd.c \
../main.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
lcd.o \
main.o

OBJS_AS_ARGS +=  \
lcd.o \
main.o

C_DEPS +=  \
lcd.d \
main.d

C_DEPS_AS_ARGS +=  \
lcd.d \
main.d

OUTPUT_FILE_PATH +=I2Catmega8.elf

OUTPUT_FILE_PATH_AS_ARGS +=I2Catmega8.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./lcd.o: .././lcd.c
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.3.3
	$(QUOTE)D:\winavr\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\7.0\Packs\Atmel\ATmega_DFP\1.3.300\include" -I".."  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega8  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./main.o: .././main.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.3.3
	$(QUOTE)D:\winavr\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\7.0\Packs\Atmel\ATmega_DFP\1.3.300\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega8  -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 4.3.3
	$(QUOTE)D:\winavr\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="I2Catmega8.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,-L"C:\Users\PC\Documents\Atmel Studio\7.0\I2Catmega8\I2Catmega8"  -Wl,--gc-sections  -mmcu=atmega8   
	@echo Finished building target: $@
	"D:\winavr\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "I2Catmega8.elf" "I2Catmega8.hex"
	"D:\winavr\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "I2Catmega8.elf" "I2Catmega8.eep" || exit 0
	"D:\winavr\bin\avr-objdump.exe" -h -S "I2Catmega8.elf" > "I2Catmega8.lss"
	"D:\winavr\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "I2Catmega8.elf" "I2Catmega8.srec"
	"D:\winavr\bin\avr-size.exe" "I2Catmega8.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "I2Catmega8.elf" "I2Catmega8.a" "I2Catmega8.hex" "I2Catmega8.lss" "I2Catmega8.eep" "I2Catmega8.map" "I2Catmega8.srec" "I2Catmega8.usersignatures"
	