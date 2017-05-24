################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../encode.c \
../logger.c \
../test_main.c \
../xrandom.c \
../xstring.c 

OBJS += \
./encode.o \
./logger.o \
./test_main.o \
./xrandom.o \
./xstring.o 

C_DEPS += \
./encode.d \
./logger.d \
./test_main.d \
./xrandom.d \
./xstring.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


