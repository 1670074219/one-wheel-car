################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Image/Cheku.c \
../src/Image/Cirque.c \
../src/Image/Cross.c \
../src/Image/Duanlu.c \
../src/Image/Image_process.c \
../src/Image/Zhangai.c \
../src/Image/podao.c 

OBJS += \
./src/Image/Cheku.o \
./src/Image/Cirque.o \
./src/Image/Cross.o \
./src/Image/Duanlu.o \
./src/Image/Image_process.o \
./src/Image/Zhangai.o \
./src/Image/podao.o 

COMPILED_SRCS += \
./src/Image/Cheku.src \
./src/Image/Cirque.src \
./src/Image/Cross.src \
./src/Image/Duanlu.src \
./src/Image/Image_process.src \
./src/Image/Zhangai.src \
./src/Image/podao.src 

C_DEPS += \
./src/Image/Cheku.d \
./src/Image/Cirque.d \
./src/Image/Cross.d \
./src/Image/Duanlu.d \
./src/Image/Image_process.d \
./src/Image/Zhangai.d \
./src/Image/podao.d 


# Each subdirectory must supply rules for building sources it contributes
src/Image/%.src: ../src/Image/%.c src/Image/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc29xb "-fD:/desktop/workspace/One_Wheel_Car_LQ/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc29xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

src/Image/%.o: ./src/Image/%.src src/Image/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


