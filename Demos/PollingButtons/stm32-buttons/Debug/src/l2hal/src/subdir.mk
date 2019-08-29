################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/l2hal/src/l2hal.c \
../src/l2hal/src/l2hal_aux.c \
../src/l2hal/src/l2hal_custom.c \
../src/l2hal/src/l2hal_errors.c 

OBJS += \
./src/l2hal/src/l2hal.o \
./src/l2hal/src/l2hal_aux.o \
./src/l2hal/src/l2hal_custom.o \
./src/l2hal/src/l2hal_errors.o 

C_DEPS += \
./src/l2hal/src/l2hal.d \
./src/l2hal/src/l2hal_aux.d \
./src/l2hal/src/l2hal_custom.d \
./src/l2hal/src/l2hal_errors.d 


# Each subdirectory must supply rules for building sources it contributes
src/l2hal/src/%.o: ../src/l2hal/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -flto -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DDEBUG -DSTM32F103x6 -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DHSE_VALUE=8000000 -I"../include" -I"../src/l2hal/drivers/input/encoders/include" -I"../src/l2hal/drivers/input/buttons/include" -I"../src/l2hal/drivers/display/ssd1306/include" -I"../src/fmgl/charsets/include" -I"../src/fmgl/fonts/include" -I"../src/fmgl/include" -I"../src/l2hal/include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1xx" -std=gnu11 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


