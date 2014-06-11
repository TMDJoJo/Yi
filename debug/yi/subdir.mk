################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../yi/yi_buffer.cpp \
../yi/yi_message_decoder.cpp \
../yi/yi_message_encoder.cpp \
../yi/yi_server.cpp \
../yi/yi_session_manager.cpp \
../yi/yi_utils.cpp 

OBJS += \
./yi/yi_buffer.o \
./yi/yi_message_decoder.o \
./yi/yi_message_encoder.o \
./yi/yi_server.o \
./yi/yi_session_manager.o \
./yi/yi_utils.o 

CPP_DEPS += \
./yi/yi_buffer.d \
./yi/yi_message_decoder.d \
./yi/yi_message_encoder.d \
./yi/yi_server.d \
./yi/yi_session_manager.d \
./yi/yi_utils.d 


# Each subdirectory must supply rules for building sources it contributes
yi/%.o: ../yi/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


