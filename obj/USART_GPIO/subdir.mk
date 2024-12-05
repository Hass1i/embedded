################################################################################
# MRS Version: 1.9.2
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USART_GPIO/GPIO_USART.c 

OBJS += \
./USART_GPIO/GPIO_USART.o 

C_DEPS += \
./USART_GPIO/GPIO_USART.d 


# Each subdirectory must supply rules for building sources it contributes
USART_GPIO/%.o: ../USART_GPIO/%.c
	@	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"C:\MRS_DATA\workspace\CH32V003F4P6\Debug" -I"C:\MRS_DATA\workspace\CH32V003F4P6\Core" -I"C:\MRS_DATA\workspace\CH32V003F4P6\User" -I"C:\MRS_DATA\workspace\CH32V003F4P6\Peripheral\inc" -I"C:\MRS_DATA\workspace\CH32V003F4P6\FSM_TABLE" -I"C:\MRS_DATA\workspace\CH32V003F4P6\FUNCTION" -I"C:\MRS_DATA\workspace\CH32V003F4P6\USART_GPIO" -I"C:\MRS_DATA\workspace\CH32V003F4P6\TABLE_TYPE" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

