################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm.c \
../Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Atom.c \
../Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Cmu.c \
../Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Dpll.c \
../Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tbu.c \
../Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tim.c \
../Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tom.c 

OBJS += \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm.o \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Atom.o \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Cmu.o \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Dpll.o \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tbu.o \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tim.o \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tom.o 

COMPILED_SRCS += \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm.src \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Atom.src \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Cmu.src \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Dpll.src \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tbu.src \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tim.src \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tom.src 

C_DEPS += \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm.d \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Atom.d \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Cmu.d \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Dpll.d \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tbu.d \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tim.d \
./Libraries/iLLD/TC29B/Tricore/Gtm/Std/IfxGtm_Tom.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/iLLD/TC29B/Tricore/Gtm/Std/%.src: ../Libraries/iLLD/TC29B/Tricore/Gtm/Std/%.c Libraries/iLLD/TC29B/Tricore/Gtm/Std/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc29xb "-fD:/desktop/workspace/One_Wheel_Car_LQ/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc29xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/iLLD/TC29B/Tricore/Gtm/Std/%.o: ./Libraries/iLLD/TC29B/Tricore/Gtm/Std/%.src Libraries/iLLD/TC29B/Tricore/Gtm/Std/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


