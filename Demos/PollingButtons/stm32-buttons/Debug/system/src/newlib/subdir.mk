################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/newlib/_exit.c \
../system/src/newlib/_sbrk.c \
../system/src/newlib/_startup.c \
../system/src/newlib/_syscalls.c \
../system/src/newlib/assert.c 

CPP_SRCS += \
../system/src/newlib/_cxx.cpp 

OBJS += \
./system/src/newlib/_cxx.o \
./system/src/newlib/_exit.o \
./system/src/newlib/_sbrk.o \
./system/src/newlib/_startup.o \
./system/src/newlib/_syscalls.o \
./system/src/newlib/assert.o 

C_DEPS += \
./system/src/newlib/_exit.d \
./system/src/newlib/_sbrk.d \
./system/src/newlib/_startup.d \
./system/src/newlib/_syscalls.d \
./system/src/newlib/assert.d 

CPP_DEPS += \
./system/src/newlib/_cxx.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/newlib/%.o: ../system/src/newlib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -flto -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DDEBUG -DSTM32F103x6 -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DHSE_VALUE=8000000 -I"../include" -I"../src/l2hal/drivers/input/encoders/include" -I"../src/l2hal/drivers/input/buttons/include" -I"../src/l2hal/drivers/display/ssd1306/include" -I"../src/fmgl/charsets/include" -I"../src/fmgl/fonts/include" -I"../src/fmgl/include" -I"../src/l2hal/include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1xx" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -Wabi -Wctor-dtor-privacy -Wnoexcept -Wnon-virtual-dtor -Wstrict-null-sentinel -Wsign-promo -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/src/newlib/%.o: ../system/src/newlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -flto -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DDEBUG -DSTM32F103x6 -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DHSE_VALUE=8000000 -I"../include" -I"../src/l2hal/drivers/input/encoders/include" -I"../src/l2hal/drivers/input/buttons/include" -I"../src/l2hal/drivers/display/ssd1306/include" -I"../src/fmgl/charsets/include" -I"../src/fmgl/fonts/include" -I"../src/fmgl/include" -I"../src/l2hal/include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1xx" -std=gnu11 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


