################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/APP/LQ_ADC_7Mic.c \
../src/APP/LQ_Atom_Motor.c \
../src/APP/LQ_CAMERA.c \
../src/APP/LQ_CCU6_Timer.c \
../src/APP/LQ_EEPROM_TEST.c \
../src/APP/LQ_FFT_TEST.c \
../src/APP/LQ_GPIO_ExInt.c \
../src/APP/LQ_GPIO_KEY.c \
../src/APP/LQ_GPIO_LED.c \
../src/APP/LQ_GPT_mini512.c \
../src/APP/LQ_I2C_9AX.c \
../src/APP/LQ_I2C_VL53.c \
../src/APP/LQ_ICM20602.c \
../src/APP/LQ_IIC_Gyro.c \
../src/APP/LQ_MT9V034.c \
../src/APP/LQ_OLED096.c \
../src/APP/LQ_RDA5807.c \
../src/APP/LQ_STM_Timer.c \
../src/APP/LQ_TFT18.c \
../src/APP/LQ_TFT2.c \
../src/APP/LQ_TFTPicFont.c \
../src/APP/LQ_Tim_InputCature.c \
../src/APP/LQ_Tom_Servo.c \
../src/APP/LQ_UART_Bluetooth.c 

O_SRCS += \
../src/APP/LQ_MPU6050_DMP.o 

OBJS += \
./src/APP/LQ_ADC_7Mic.o \
./src/APP/LQ_Atom_Motor.o \
./src/APP/LQ_CAMERA.o \
./src/APP/LQ_CCU6_Timer.o \
./src/APP/LQ_EEPROM_TEST.o \
./src/APP/LQ_FFT_TEST.o \
./src/APP/LQ_GPIO_ExInt.o \
./src/APP/LQ_GPIO_KEY.o \
./src/APP/LQ_GPIO_LED.o \
./src/APP/LQ_GPT_mini512.o \
./src/APP/LQ_I2C_9AX.o \
./src/APP/LQ_I2C_VL53.o \
./src/APP/LQ_ICM20602.o \
./src/APP/LQ_IIC_Gyro.o \
./src/APP/LQ_MT9V034.o \
./src/APP/LQ_OLED096.o \
./src/APP/LQ_RDA5807.o \
./src/APP/LQ_STM_Timer.o \
./src/APP/LQ_TFT18.o \
./src/APP/LQ_TFT2.o \
./src/APP/LQ_TFTPicFont.o \
./src/APP/LQ_Tim_InputCature.o \
./src/APP/LQ_Tom_Servo.o \
./src/APP/LQ_UART_Bluetooth.o 

COMPILED_SRCS += \
./src/APP/LQ_ADC_7Mic.src \
./src/APP/LQ_Atom_Motor.src \
./src/APP/LQ_CAMERA.src \
./src/APP/LQ_CCU6_Timer.src \
./src/APP/LQ_EEPROM_TEST.src \
./src/APP/LQ_FFT_TEST.src \
./src/APP/LQ_GPIO_ExInt.src \
./src/APP/LQ_GPIO_KEY.src \
./src/APP/LQ_GPIO_LED.src \
./src/APP/LQ_GPT_mini512.src \
./src/APP/LQ_I2C_9AX.src \
./src/APP/LQ_I2C_VL53.src \
./src/APP/LQ_ICM20602.src \
./src/APP/LQ_IIC_Gyro.src \
./src/APP/LQ_MT9V034.src \
./src/APP/LQ_OLED096.src \
./src/APP/LQ_RDA5807.src \
./src/APP/LQ_STM_Timer.src \
./src/APP/LQ_TFT18.src \
./src/APP/LQ_TFT2.src \
./src/APP/LQ_TFTPicFont.src \
./src/APP/LQ_Tim_InputCature.src \
./src/APP/LQ_Tom_Servo.src \
./src/APP/LQ_UART_Bluetooth.src 

C_DEPS += \
./src/APP/LQ_ADC_7Mic.d \
./src/APP/LQ_Atom_Motor.d \
./src/APP/LQ_CAMERA.d \
./src/APP/LQ_CCU6_Timer.d \
./src/APP/LQ_EEPROM_TEST.d \
./src/APP/LQ_FFT_TEST.d \
./src/APP/LQ_GPIO_ExInt.d \
./src/APP/LQ_GPIO_KEY.d \
./src/APP/LQ_GPIO_LED.d \
./src/APP/LQ_GPT_mini512.d \
./src/APP/LQ_I2C_9AX.d \
./src/APP/LQ_I2C_VL53.d \
./src/APP/LQ_ICM20602.d \
./src/APP/LQ_IIC_Gyro.d \
./src/APP/LQ_MT9V034.d \
./src/APP/LQ_OLED096.d \
./src/APP/LQ_RDA5807.d \
./src/APP/LQ_STM_Timer.d \
./src/APP/LQ_TFT18.d \
./src/APP/LQ_TFT2.d \
./src/APP/LQ_TFTPicFont.d \
./src/APP/LQ_Tim_InputCature.d \
./src/APP/LQ_Tom_Servo.d \
./src/APP/LQ_UART_Bluetooth.d 


# Each subdirectory must supply rules for building sources it contributes
src/APP/%.src: ../src/APP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc29xb -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Psi5s\Psi5s" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Eth\Phy_Pef7071" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Fce" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Infra\Platform\Tricore\Compilers" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Psi5\Psi5" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gpt12\IncrEnc" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Infra\Platform" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Psi5" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service\CpuGeneric\If\Ccu6If" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Hssl\Hssl" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Tom\PwmHl" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Smu" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ccu6\TimerWithTrigger" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Emem" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Dts\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ebu\Sram" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Atom\Timer" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service\CpuGeneric\SysSe\Comm" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service\CpuGeneric\SysSe\Math" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Infra\Platform\Tricore" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Dsadc\Rdc" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Asclin\Spi" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Vadc\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Mtu\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Flash" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Vadc" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Infra" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Flash\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Stm" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Cpu\Irq" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ccu6\PwmBc" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Scu" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service\CpuGeneric\SysSe" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Fce\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service\CpuGeneric\If" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Multican\Can" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Fft\Fft" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Asclin\Lin" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Sent\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Tim" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Src\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Dsadc" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Atom\PwmHl" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Hssl\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\_Lib\InternalMux" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Psi5s\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Stm\Timer" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Trig" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ccu6\Timer" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Eth" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Dts\Dts" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Eray\Eray" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Dma\Dma" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ccu6\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Cif\Cam" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gpt12\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Psi5s" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Qspi\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Qspi\SpiMaster" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Infra\Sfr" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\I2c" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service\CpuGeneric\SysSe\Bsp" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service\CpuGeneric\SysSe\General" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Cpu\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ebu" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Dma\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Msc" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Configurations" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Fce\Crc" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ebu\BFlashSt" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Iom\Driver" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Vadc\Adc" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Port\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Cif" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Tom" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Asclin\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Stm\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Atom\Pwm" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Iom\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\I2c\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\_PinMap" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service\CpuGeneric" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Cpu\CStart" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ccu6" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ebu\BFlashSpansion" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Cpu" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Msc\Msc" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Mtu" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Tim\In" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Dsadc\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Qspi\SpiSlave" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service\CpuGeneric\SysSe\Time" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\_Impl" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Cpu\Trap" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Infra\Sfr\TC29B\_Reg" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Asclin" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Atom" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Dsadc\Dsadc" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Eray\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ebu\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Tom\Pwm" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Scu\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Fft" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Psi5\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Sent\Sent" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ccu6\TPwm" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Tom\Timer" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Smu\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Port" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\I2c\I2c" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Fft\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Port\Io" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Iom" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Infra\Sfr\TC29B" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Cif\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Emem\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service\CpuGeneric\StdIf" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\_Lib\DataHandling" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Multican" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Asclin\Asc" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Qspi" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Sent" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Configurations\Debug" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Eray" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Eth\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Hssl" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\Service\CpuGeneric\_Utilities" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Dts" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ccu6\PwmHl" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\_Lib" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ebu\Dram" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Ccu6\Icu" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gpt12" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Multican\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Src" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Dma" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Gtm\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\Libraries\iLLD\TC29B\Tricore\Msc\Std" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\src\APP" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\src\Driver" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\src\Main" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\src\User" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\src" -I"D:\desktop\workspace-ads\One_Wheel_Car_LQ\src\Image" --iso=99 --c++14 --language=+volatile --anachronisms --fp-model=3 --fp-model=c --fp-model=f --fp-model=l --fp-model=n --fp-model=r --fp-model=z -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc29xb -o "$@"  "$<"  -cs --dep-file=$(@:.src=.d) --misrac-version=2012 -N0 -Z0 -Y0 2>&1; sed -i -e '/ctc\\include/d' -e '/Libraries\\iLLD/d' -e '/Libraries\\Infra/d' -e 's/\(.*\)".*\\One_Wheel_Car_LQ\(\\.*\)"/\1\.\.\2/g' -e 's/\\/\//g' $(@:.src=.d) && \
	echo $(@:.src=.d) generated
	@echo 'Finished building: $<'
	@echo ' '

src/APP/%.o: ./src/APP/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


