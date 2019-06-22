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
../font.c \
../i2c.c \
../lcd.c \
../main.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
font.o \
i2c.o \
lcd.o \
main.o

OBJS_AS_ARGS +=  \
font.o \
i2c.o \
lcd.o \
main.o

C_DEPS +=  \
font.d \
i2c.d \
lcd.d \
main.d

C_DEPS_AS_ARGS +=  \
font.d \
i2c.d \
lcd.d \
main.d

OUTPUT_FILE_PATH +=uart_oled.elf

OUTPUT_FILE_PATH_AS_ARGS +=uart_oled.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./font.o: .././font.c
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.3.3
	$(QUOTE)D:\winavr\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\7.0\Packs\Atmel\ATmega_DFP\1.3.300\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega328p  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./i2c.o: .././i2c.c
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.3.3
	$(QUOTE)D:\winavr\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\7.0\Packs\Atmel\ATmega_DFP\1.3.300\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega328p  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./lcd.o: .././lcd.c
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.3.3
	$(QUOTE)D:\winavr\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\7.0\Packs\Atmel\ATmega_DFP\1.3.300\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega328p  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./main.o: .././main.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 4.3.3
	$(QUOTE)D:\winavr\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\7.0\Packs\Atmel\ATmega_DFP\1.3.300\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=atmega328p  -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
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
	$(QUOTE)D:\winavr\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="uart_oled.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections  -mmcu=atmega328p   
	@echo Finished building target: $@
	"D:\winavr\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "uart_oled.elf" "uart_oled.hex"
	"D:\winavr\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "uart_oled.elf" "uart_oled.eep" || exit 0
	"D:\winavr\bin\avr-objdump.exe" -h -S "uart_oled.elf" > "uart_oled.lss"
	"D:\winavr\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "uart_oled.elf" "uart_oled.srec"
	"D:\winavr\bin\avr-size.exe" "uart_oled.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "uart_oled.elf" "uart_oled.a" "uart_oled.hex" "uart_oled.lss" "uart_oled.eep" "uart_oled.map" "uart_oled.srec" "uart_oled.usersignatures"
	