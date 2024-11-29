################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/GPIO_USART.c \
../User/ch32v00x_it.c \
../User/fsm_table.c \
../User/function_state.c \
../User/main.c \
../User/system_ch32v00x.c 

OBJS += \
./User/GPIO_USART.o \
./User/ch32v00x_it.o \
./User/fsm_table.o \
./User/function_state.o \
./User/main.o \
./User/system_ch32v00x.o 

C_DEPS += \
./User/GPIO_USART.d \
./User/ch32v00x_it.d \
./User/fsm_table.d \
./User/function_state.d \
./User/main.d \
./User/system_ch32v00x.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\MRS_DATA\workspace\CH32V003F4P6\Debug" -I"C:\MRS_DATA\workspace\CH32V003F4P6\Core" -I"C:\MRS_DATA\workspace\CH32V003F4P6\User" -I"C:\MRS_DATA\workspace\CH32V003F4P6\Peripheral\inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

