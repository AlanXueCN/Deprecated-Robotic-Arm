################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
armMainV3.obj: ../armMainV3.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --opt_for_speed=3 --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="C:/StellarisWare" --preinclude="C:/StellarisWare/inc/hw_types.h" -g --gcc --define="ccs" --define=PART_LM4F210H5QR --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="armMainV3.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

lm4f210h5qr_startup_ccs.obj: ../lm4f210h5qr_startup_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --opt_for_speed=3 --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="C:/StellarisWare" --preinclude="C:/StellarisWare/inc/hw_types.h" -g --gcc --define="ccs" --define=PART_LM4F210H5QR --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="lm4f210h5qr_startup_ccs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

struct_xfer.obj: ../struct_xfer.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.9/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me --opt_for_speed=3 --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.9/include" --include_path="C:/StellarisWare" --preinclude="C:/StellarisWare/inc/hw_types.h" -g --gcc --define="ccs" --define=PART_LM4F210H5QR --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="struct_xfer.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


