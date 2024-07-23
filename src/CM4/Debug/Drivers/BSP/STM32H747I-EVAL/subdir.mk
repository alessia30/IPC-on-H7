################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval.c \
../Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_bus.c \
../Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_io.c 

OBJS += \
./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval.o \
./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_bus.o \
./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_io.o 

C_DEPS += \
./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval.d \
./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_bus.d \
./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_io.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32H747I-EVAL/%.o Drivers/BSP/STM32H747I-EVAL/%.su Drivers/BSP/STM32H747I-EVAL/%.cyclo: ../Drivers/BSP/STM32H747I-EVAL/%.c Drivers/BSP/STM32H747I-EVAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_STM32H747I_EVAL -DCORE_CM4 -DUSE_HAL_DRIVER -DSTM32H757xx -DMETAL_INTERNAL -DMETAL_MAX_DEVICE_REGIONS=2 -DRPMSG_BUFFER_SIZE=512 -DVIRTIO_SLAVE_ONLY -DNO_ATOMIC_64_SUPPORT -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../OPENAMP -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include -I../../Middlewares/Third_Party/OpenAMP/libmetal/lib/include/metal/compiler/gcc -I../../Middlewares/Third_Party/OpenAMP/open-amp/lib/rpmsg -I../../Common/Inc -I../../Utilities/ResourcesManager -I"/Users/alessia/STM32CubeIDE/workspace_1.14.0/SOC2/CM4/Drivers/BSP" -I"/Users/alessia/STM32CubeIDE/workspace_1.14.0/SOC2/CM4/Drivers/BSP/STM32H747I-EVAL" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32H747I-2d-EVAL

clean-Drivers-2f-BSP-2f-STM32H747I-2d-EVAL:
	-$(RM) ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval.cyclo ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval.d ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval.o ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval.su ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_bus.cyclo ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_bus.d ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_bus.o ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_bus.su ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_io.cyclo ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_io.d ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_io.o ./Drivers/BSP/STM32H747I-EVAL/stm32h747i_eval_io.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32H747I-2d-EVAL

