################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../apue.cc \
../exercise_11_5.cc \
../exercise_11_6.cc \
../example_cond.cc\

OBJS += \
./apue.o \
./exercise_11_5.o \
./exercise_11_6.o \
./example_cond.o \

OBJS_COND += \
./example_cond.o\

OBJS_EXERCISE += \
./apue.o	\
./exercise_11_5.o \
./exercise_11_6.o \

CC_DEPS += \
./apue.d \
./exercise_11_5.d \
./exercise_11_6.d \
./example_cond.d \


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


