################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Application/Startup/startup_stm32f429zitx.s 

S_DEPS += \
./Application/Startup/startup_stm32f429zitx.d 

OBJS += \
./Application/Startup/startup_stm32f429zitx.o 


# Each subdirectory must supply rules for building sources it contributes
Application/Startup/startup_stm32f429zitx.o: ../Application/Startup/startup_stm32f429zitx.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I"C:/TouchGFXProjects/mearm-stm32f429i/Libraries" -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -x assembler-with-cpp -MMD -MP -MF"Application/Startup/startup_stm32f429zitx.d" -MT"$@" --specs=nano_c_standard_cpp.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

