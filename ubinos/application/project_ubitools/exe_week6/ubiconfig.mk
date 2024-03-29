#exe_ubinos_test
################

#ITFDIR=../../
#SRCDIR=../src

################

RM                              = rm -rf
MKDIR                           = mkdir -p
RMDIR                           = rmdir -p
CP                              = cp -rf
INSTALL_EXE                     = install -m755
UNPACK                          = tar xvfj

################

TARGET_TOOLCHAIN_TYPE           = armnoneeabi
TARGET_TOOLCHAIN_PREFIX         = arm-none-eabi-

CC                              = $(TARGET_TOOLCHAIN_PREFIX)gcc
CXX                             = $(TARGET_TOOLCHAIN_PREFIX)g++
AS                              = $(TARGET_TOOLCHAIN_PREFIX)gcc

AR                              = $(TARGET_TOOLCHAIN_PREFIX)ar
LD                              = $(TARGET_TOOLCHAIN_PREFIX)g++
OBJCOPY                         = $(TARGET_TOOLCHAIN_PREFIX)objcopy

#CFLAG_ARCH                      = -mcpu=arm7tdmi -mthumb-interwork -mlittle-endian -msoft-float -D__SOCHECK__ -msocheck -D__SUCHECK__ -msucheck 
#CFLAG_ARCH                      = -mcpu=cortex-m4 -mlittle-endian -msoft-float
#CFLAG_ARCH                      = -mcpu=cortex-m4 -mlittle-endian -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -DARM_MATH_CM4 -D__SOFTFP__
#CFLAG_ARCH                      = -mcpu=cortex-m4 -mlittle-endian -DARM_MATH_CM4
CFLAG_ARCH                      = -mcpu=cortex-m4 -mlittle-endian -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -DARM_MATH_CM4 -D__VFP_FP__ -D__FPU_PRESENT=1
CFLAG_OPSTATE                   = -mthumb
CFALG_OPTIMIZATION              = -O0
CFALG_DEBUG                     = -g3
CFLAG_SAM						+= -D__SAM4E16E__
CFLAG_SAM						+= -DBOARD=SAM4E_EK
CFLAG_SAM						+= -std=c99

INCLUDE_MCU_CORE				= -I$(ITFDIR)/../kernel/porting/lib_sam4e/thirdparty/CMSIS/Include
#INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../CORTEXM_CMSIS/Include
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/sam/utils/cmsis/sam4e/include
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/sam/utils/cmsis/sam4e/include/component
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/sam/utils/cmsis/sam4e/include/instance
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/sam/utils
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/sam/utils/fpu
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/sam/utils/header_files
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/sam/utils/preprocessor
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/common/utils
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/sam/boards/sam4e_ek/board_config
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/common/boards
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/common/services/ioport
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/common/services/clock
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/common/services/clock/sam4e/module_config
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/sam/boards/sam4e_ek
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/sam/utils/cmsis/sam4e/source/templates

SAMLIB_PATH						= $(ITFDIR)/../kernel/porting/lib_sam4e
INCLUDE_SDMMC					+= -I$(SAMLIB_PATH)/common/components/memory/sd_mmc
INCLUDE_USB_STD					+= -I$(SAMLIB_PATH)/common/services/usb/class/cdc/device
INCLUDE_USB_STD					+= -I$(SAMLIB_PATH)/common/services/usb/class/cdc
INCLUDE_USB_STD					+= -I$(SAMLIB_PATH)/common/services/usb/udc
INCLUDE_USB_STD					+= -I$(SAMLIB_PATH)/common/services/usb

INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e
INCLUDE_MCU_CORE				+= -I$(ITFDIR)/../kernel/porting/lib_sam4e/sam/drivers

INCLUDE_BOARD_DRIVER			+= -I$(ITFDIR)/../kernel/driver

INCLUDE_BASE					= $(INCLUDE_CMSIS_CORE) $(INCLUDE_MCU_CORE) $(INCLUDE_SDMMC) $(INCLUDE_USB_STD) $(INCLUDE_BOARD_DRIVER)

CFLAG_INCLUDE                   = -I$(ITFDIR) $(INCLUDE_BASE) $(CONFIG_INCLUDE_DRIVER)
CFALG_MISC                      = -fomit-frame-pointer -Wall -fmessage-length=0 -c

CFLAGS                          = $(CFLAG_ARCH) $(CFALG_OPTIMIZATION) $(CFALG_DEBUG) $(CFLAG_INCLUDE) $(CFALG_MISC) $(CFLAG_SAM)
CXXFLAGS                        = $(CFLAGS)
ASFLAGS                         = $(CFLAGS)

ARFLAGS                         = rcs
LDFLAGS                         = -mcpu=cortex-m4 -nostartfiles -nostdlib

AS_entry                        = $(AS)
ASFLAGS_entry                   = $(ASFLAGS) -mthumb -D__ASSEMBLY__

CC_default                      = $(CC)
CFLAGS_default                  = $(CFLAGS) $(CFLAG_OPSTATE)

CXX_default                     = $(CXX)
CXXFLAGS_default                = $(CXXFLAGS) $(CFLAG_OPSTATE)

AS_default                      = $(AS)
ASFLAGS_default                 = $(ASFLAGS) $(CFLAG_OPSTATE) -D__ASSEMBLY__

CC__arm                         = $(CC)
CFLAGS__arm                     = $(CFLAGS) -mthumb

AS__arm                         = $(AS)
ASFLAGS__arm                    = $(ASFLAGS) -mthumb -D__ASSEMBLY__

CC__thumb                       = $(CC)
CFLAGS__thumb                   = $(CFLAGS) -mthumb

AS__thumb                       = $(AS)
ASFLAGS__thumb                  = $(ASFLAGS) -mthumb -D__ASSEMBLY__

CC_nosocheck                    = $(CC)
#CFLAGS_nosocheck                = $(CFLAGS) $(CFLAG_OPSTATE) -D__NOSOCHECK__ -mnosocheck -D__NOSUCHECK__ -mnosucheck
CFLAGS_nosocheck                = $(CFLAGS) $(CFLAG_OPSTATE)

CC_nosocheck__arm               = $(CC)
#CFLAGS_nosocheck__arm           = $(CFLAGS) -mthumb -D__NOSOCHECK__ -mnosocheck -D__NOSUCHECK__ -mnosucheck
CFLAGS_nosocheck__arm           = $(CFLAGS) -mthumb

CC_nosocheck__thumb             = $(CC)
#CFLAGS_nosocheck__thumb         = $(CFLAGS) -mthumb -D__NOSOCHECK__ -mnosocheck -D__NOSUCHECK__ -mnosucheck
CFLAGS_nosocheck__thumb         = $(CFLAGS) -mthumb

################

OBJS                            = 
DEPS                            = 
LIBS                            = 

################

TARGET                          = exe_week6

CSRCS_default                  += usrmain.c
COBJS_default                  += $(patsubst %.c,%.o, $(CSRCS_default))
$(COBJS_default) : %.o: $(SRCDIR)/%.c
	@$(MKDIR) $(dir $@)
	$(CC_default) $(CFLAGS_default) -MD -MP -MF"$(@:%.o=%.d)" -o "$@" "$<"	
OBJS                           += $(COBJS_default)
DEPS                           += $(patsubst %.o,%.d, $(COBJS_default))

BSPDIR                          = ../../../../kernel/porting/bsp_armcortexm_sam4eek
ENTRYOBJ                        = $(BSPDIR)/out/board/cstartup.o
LDSCRIPTDIR                     = $(SRCDIR)/$(BSPDIR)/rsc/ld/flash
LDSCRIPTFILE                    = kernel.ld
GDBSCRIPTDIR                    = $(SRCDIR)/$(BSPDIR)/rsc/gdb/flash
GDBSCRIPTFILE                   = download.gdb

LIBS                           += ../../../../kernel/common/lib_ubiclib/out/libarmnoneeabi__lib_ubiclib.a
LIBS                           += ../../../../kernel/common/lib_ubiclib_port_arm_gpl/out/libarmnoneeabi__lib_ubiclib_port_arm_gpl.a
LIBS                           += ../../../../kernel/porting/lib_ubiclib_arm/out/libarmnoneeabi__lib_ubiclib_arm.a
LIBS                           += ../../../../kernel/common/lib_ubik/out/libarmnoneeabi__lib_ubik.a
LIBS                           += ../../../../kernel/porting/lib_ubik_armcortexm/out/libarmnoneeabi__lib_ubik_armcortexm.a
LIBS                           += ../../../../kernel/porting/lib_ubik_armcortexm_sam4eek/out/libarmnoneeabi__lib_ubik_armcortexm_sam4eek.a
LIBS                           += ../../../../kernel/porting/bsp_armcortexm_sam4eek/out/libarmnoneeabi__bsp_armcortexm_sam4eek.a
LIBS							+= ../../../../kernel/porting/lib_sam4e/out/libarmnoneeabi__lib_sam4e.a
LIBS							+= ../../../../kernel/driver/lib_ubi_pio/out/libarmnoneeabi__lib_ubi_pio.a
LIBS							+= ../../../../kernel/driver/lib_lowpower/out/libarmnoneeabi__lib_lowpower.a
LIBS							+= ../../../../kernel/driver/lib_new_estk_api/out/libarmnoneeabi__lib_new_estk_api.a
LIBS							+= ../../../../kernel/driver/lib_motor_driver/out/libarmnoneeabi__lib_motor_driver.a
LIBS							+= ../../../../kernel/driver/lib_switch/out/libarmnoneeabi__lib_switch.a
LIBS							+= ../../../../application/project_ubitools/lib_default/out/libarmnoneeabi__lib_default.a
################

.PHONY : all config compile link clean

################

all: config compile link
	@echo "\n[$$(pwd) : make "$@"]"

config:
	@echo "\n[$$(pwd) : make "$@"]"

build: compile link
	@echo "\n[$$(pwd) : make "$@"]"

compile: $(OBJS)
	@echo "\n[$$(pwd) : make "$@"]"

link: out.bin
	@echo "\n[$$(pwd) : make "$@"]"
out.bin: $(OBJS) $(LIBS)
	$(AR) $(ARFLAGS) lib$(TARGET_TOOLCHAIN_TYPE)__$(TARGET).a $(OBJS)
	$(CP) $(LDSCRIPTDIR)/$(LDSCRIPTFILE) ./
	$(CP) $(GDBSCRIPTDIR)/$(GDBSCRIPTFILE) ./
	$(LD) $(LDFLAGS) -T$(LDSCRIPTFILE) -o out.elf -Wl,-Map=out.map,--cref -Wl,--start-group $(ENTRYOBJ) $(LIBS) lib$(TARGET_TOOLCHAIN_TYPE)__$(TARGET).a -Wl,--end-group -Wl,--whole-archive
	$(LD) $(LDFLAGS) -T$(LDSCRIPTFILE) -o out.elf -Wl,-Map=out.map,--cref -Wl,--start-group $(ENTRYOBJ) $(LIBS) lib$(TARGET_TOOLCHAIN_TYPE)__$(TARGET).a -Wl,--end-group
	$(OBJCOPY) out.elf -O binary out.bin
    
clean:
	@echo "\n[$$(pwd) : make "$@"]"
	$(RM) $(OBJS)
	$(RM) $(DEPS)
	$(RM) lib$(TARGET_TOOLCHAIN_TYPE)__$(TARGET).a
	$(RM) out.elf out.map out.bin
	$(RM) $(LDSCRIPTFILE)
	$(RM) $(GDBSCRIPTFILE)

################

-include $(DEPS)

################
