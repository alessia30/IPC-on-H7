################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/mfxstm32l152/mfxstm32l152.c \
../Drivers/BSP/Components/mfxstm32l152/mfxstm32l152_reg.c 

OBJS += \
./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152.o \
./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152_reg.o 

C_DEPS += \
./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152.d \
./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152_reg.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/mfxstm32l152/%.o Drivers/BSP/Components/mfxstm32l152/%.su Drivers/BSP/Components/mfxstm32l152/%.cyclo: ../Drivers/BSP/Components/mfxstm32l152/%.c Drivers/BSP/Components/mfxstm32l152/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H757xx -DMETAL_INTERNAL -DMETAL_MAX_DEVICE_REGIONS=2 -DRPMSG_BUFFER_SIZE=512 -DVIRTIO_MASTER_ONLY -DNO_ATOMIC_64_SUPPORT -DUSE_STM32H747I_EVAL -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../OPENAMP -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include/metal/compiler/gcc -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg -I../../Common/Inc -I../../Utilities/ResourcesManager -I"/Users/alessia/STM32CubeIDE/workspace_1.14.0/SOC2/CM7/Drivers/BSP/STM32H747I-EVAL" -I"/Users/alessia/STM32CubeIDE/workspace_1.14.0/SOC2/CM7/Drivers/BSP" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-mfxstm32l152

clean-Drivers-2f-BSP-2f-Components-2f-mfxstm32l152:
	-$(RM) ./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152.cyclo ./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152.d ./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152.o ./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152.su ./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152_reg.cyclo ./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152_reg.d ./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152_reg.o ./Drivers/BSP/Components/mfxstm32l152/mfxstm32l152_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-mfxstm32l152

