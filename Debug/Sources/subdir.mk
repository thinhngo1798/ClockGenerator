################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Sources/ClockGenerator.cpp \
../Sources/delay.cpp \
../Sources/fonts.cpp \
../Sources/ftfl.cpp \
../Sources/hardware.cpp \
../Sources/i2c.cpp \
../Sources/indicator.cpp \
../Sources/jogStick.cpp \
../Sources/lcd.cpp \
../Sources/main.cpp \
../Sources/sevenSegment.cpp \
../Sources/spi.cpp \
../Sources/usbdmError.cpp 

OBJS += \
./Sources/ClockGenerator.o \
./Sources/delay.o \
./Sources/fonts.o \
./Sources/ftfl.o \
./Sources/hardware.o \
./Sources/i2c.o \
./Sources/indicator.o \
./Sources/jogStick.o \
./Sources/lcd.o \
./Sources/main.o \
./Sources/sevenSegment.o \
./Sources/spi.o \
./Sources/usbdmError.o 

CPP_DEPS += \
./Sources/ClockGenerator.d \
./Sources/delay.d \
./Sources/fonts.d \
./Sources/ftfl.d \
./Sources/hardware.d \
./Sources/i2c.d \
./Sources/indicator.d \
./Sources/jogStick.d \
./Sources/lcd.d \
./Sources/main.d \
./Sources/sevenSegment.d \
./Sources/spi.d \
./Sources/usbdmError.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -g3 -O0 -ffunction-sections -fdata-sections -fno-rtti -Wall -Wextra -DDEBUG_BUILD -DLCD_AVAILABLE -I"C:/Users/trang/Documents/workspace/LabE4/Sources" -I"C:/Users/trang/Documents/workspace/LabE4/Project_Headers" -fno-exceptions -std=gnu++17 -c -fmessage-length=0 -MT"$@" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)"  -o "$@" $<
	@echo 'Finished building: $<'
	@echo ' '


