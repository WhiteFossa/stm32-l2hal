################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/fmgl/src/fmgl.c \
../src/fmgl/src/fmgl_private.c 

OBJS += \
./src/fmgl/src/fmgl.o \
./src/fmgl/src/fmgl_private.o 

C_DEPS += \
./src/fmgl/src/fmgl.d \
./src/fmgl/src/fmgl_private.d 


# Each subdirectory must supply rules for building sources it contributes
src/fmgl/src/%.o: ../src/fmgl/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -flto -fno-move-loop-invariants -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wpadded -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -DDEBUG -DSTM32F103x6 -DUSE_FULL_ASSERT -DOS_USE_SEMIHOSTING -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DHSE_VALUE=8000000 -I"../include" -I"../src/l2hal/mcu_dependent" -I"../src/l2hal/drivers/input/encoders/include" -I"../src/l2hal/drivers/input/buttons/include" -I"../src/l2hal/drivers/display/ssd1306/include" -I"../src/fmgl/charsets/include" -I"../src/fmgl/fonts/include" -I"../src/fmgl/include" -I"../src/l2hal/include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1xx" -std=gnu11 -Wmissing-prototypes -Wstrict-prototypes -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


