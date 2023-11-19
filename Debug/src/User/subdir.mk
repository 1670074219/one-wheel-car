################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/User/Ano_DT.c \
../src/User/LQ_AnoScope.c \
../src/User/LQ_Inductor.c \
../src/User/LQ_MotorServo.c \
../src/User/LQ_PID.c \
../src/User/Loop.c \
../src/User/PID.c \
../src/User/image.c \
../src/User/menu.c \
../src/User/my_math.c \
../src/User/swj.c \
../src/User/vofa+.c 

OBJS += \
./src/User/Ano_DT.o \
./src/User/LQ_AnoScope.o \
./src/User/LQ_Inductor.o \
./src/User/LQ_MotorServo.o \
./src/User/LQ_PID.o \
./src/User/Loop.o \
./src/User/PID.o \
./src/User/image.o \
./src/User/menu.o \
./src/User/my_math.o \
./src/User/swj.o \
./src/User/vofa+.o 

COMPILED_SRCS += \
./src/User/Ano_DT.src \
./src/User/LQ_AnoScope.src \
./src/User/LQ_Inductor.src \
./src/User/LQ_MotorServo.src \
./src/User/LQ_PID.src \
./src/User/Loop.src \
./src/User/PID.src \
./src/User/image.src \
./src/User/menu.src \
./src/User/my_math.src \
./src/User/swj.src \
./src/User/vofa+.src 

C_DEPS += \
./src/User/Ano_DT.d \
./src/User/LQ_AnoScope.d \
./src/User/LQ_Inductor.d \
./src/User/LQ_MotorServo.d \
./src/User/LQ_PID.d \
./src/User/Loop.d \
./src/User/PID.d \
./src/User/image.d \
./src/User/menu.d \
./src/User/my_math.d \
./src/User/swj.d \
./src/User/vofa+.d 


# Each subdirectory must supply rules for building sources it contributes
src/User/%.src: ../src/User/%.c src/User/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc29xb "-fD:/desktop/workspace/One_Wheel_Car_LQ/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc29xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

src/User/%.o: ./src/User/%.src src/User/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


