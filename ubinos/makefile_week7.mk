#include config.mk

MAKE_FUNC = \
make $(1) \
-C $(2) \
CONFIG_ARCH_COMMON=$(CONFIG_ARCH_COMMON) \
CONFIG_ARCH=$(CONFIG_ARCH) \
CONFIG_BOARD=$(CONFIG_BOARD) \
CONFIG=$(CONFIG) \
OUTDIR=$(OUTDIR)/$(2)/out \
ITFDIR=$(ITFDIR) \

.PHONY : all config build clean cleanall rebuild rebuildall info

all: info $(OUTDIR)
	@echo "\n[$$(pwd) : make "$@"]"
	$(call MAKE_FUNC,$@,interface/itf_ubinos)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubiclib)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubiclib_port_arm_gpl)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubik)
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubiclib_$(CONFIG_ARCH_COMMON))
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubik_$(CONFIG_ARCH))
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubik_$(CONFIG))
	$(call MAKE_FUNC,$@,kernel/porting/lib_$(CONFIG_LIB))
	$(call MAKE_FUNC,$@,kernel/porting/bsp_$(CONFIG))
	$(call MAKE_FUNC,$@,kernel/driver/lib_i2c_master)
	$(call MAKE_FUNC,$@,kernel/driver/lib_ubi_pio)
	$(call MAKE_FUNC,$@,kernel/driver/lib_lowpower)
	$(call MAKE_FUNC,$@,kernel/driver/lib_new_estk_api)
	$(call MAKE_FUNC,$@,kernel/driver/lib_motor_driver)
	$(call MAKE_FUNC,$@,kernel/driver/lib_EV3_sensor)
	$(call MAKE_FUNC,$@,kernel/driver/lib_bluetooth)
	$(call MAKE_FUNC,$@,application/project_ubitools/lib_default)
	$(call MAKE_FUNC,$@,application/project_ubitools/exe_week7)

config: info $(OUTDIR)
	@echo "\n[$$(pwd) : make "$@"]"
	$(call MAKE_FUNC,$@,interface/itf_ubinos)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubiclib)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubiclib_port_arm_gpl)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubik)
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubiclib_$(CONFIG_ARCH_COMMON))
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubik_$(CONFIG_ARCH))
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubik_$(CONFIG))
	$(call MAKE_FUNC,$@,kernel/porting/lib_$(CONFIG_LIB))
	$(call MAKE_FUNC,$@,kernel/porting/bsp_$(CONFIG))
	$(call MAKE_FUNC,$@,kernel/driver/lib_i2c_master)
	$(call MAKE_FUNC,$@,kernel/driver/lib_ubi_pio)
	$(call MAKE_FUNC,$@,kernel/driver/lib_lowpower)
	$(call MAKE_FUNC,$@,kernel/driver/lib_new_estk_api)
	$(call MAKE_FUNC,$@,kernel/driver/lib_motor_driver)
	$(call MAKE_FUNC,$@,application/project_ubitools/lib_default)
	$(call MAKE_FUNC,$@,application/project_ubitools/exe_week7)

build: info $(OUTDIR)
	@echo "\n[$$(pwd) : make "$@"]"
	$(call MAKE_FUNC,$@,interface/itf_ubinos)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubiclib)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubiclib_port_arm_gpl)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubik)
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubiclib_$(CONFIG_ARCH_COMMON))
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubik_$(CONFIG_ARCH))
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubik_$(CONFIG))
	$(call MAKE_FUNC,$@,kernel/porting/lib_$(CONFIG_LIB))
	$(call MAKE_FUNC,$@,kernel/porting/bsp_$(CONFIG))
	$(call MAKE_FUNC,$@,kernel/driver/lib_i2c_master)
	$(call MAKE_FUNC,$@,kernel/driver/lib_ubi_pio)
	$(call MAKE_FUNC,$@,kernel/driver/lib_lowpower)
	$(call MAKE_FUNC,$@,kernel/driver/lib_new_estk_api)
	$(call MAKE_FUNC,$@,kernel/driver/lib_motor_driver)
	$(call MAKE_FUNC,$@,application/project_ubitools/lib_default)
	$(call MAKE_FUNC,$@,application/project_ubitools/exe_week7)

clean: info $(OUTDIR)
	@echo "\n[$$(pwd) : make "$@"]"
	$(call MAKE_FUNC,$@,interface/itf_ubinos)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubiclib)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubiclib_port_arm_gpl)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubik)
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubiclib_$(CONFIG_ARCH_COMMON))
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubik_$(CONFIG_ARCH))
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubik_$(CONFIG))
	$(call MAKE_FUNC,$@,kernel/porting/lib_$(CONFIG_LIB))
	$(call MAKE_FUNC,$@,kernel/porting/bsp_$(CONFIG))
	$(call MAKE_FUNC,$@,kernel/driver/lib_i2c_master)
	$(call MAKE_FUNC,$@,kernel/driver/lib_ubi_pio)
	$(call MAKE_FUNC,$@,kernel/driver/lib_lowpower)
	$(call MAKE_FUNC,$@,kernel/driver/lib_new_estk_api)
	$(call MAKE_FUNC,$@,kernel/driver/lib_motor_driver)
	$(call MAKE_FUNC,$@,application/project_ubitools/lib_default)
	$(call MAKE_FUNC,$@,application/project_ubitools/exe_week7)

cleanall: clean
	@echo "\n[$$(pwd) : make "$@"]"
	$(call MAKE_FUNC,$@,interface/itf_ubinos)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubiclib)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubiclib_port_arm_gpl)
	$(call MAKE_FUNC,$@,kernel/common/lib_ubik)
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubiclib_$(CONFIG_ARCH_COMMON))
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubik_$(CONFIG_ARCH))
	$(call MAKE_FUNC,$@,kernel/porting/lib_ubik_$(CONFIG))
	$(call MAKE_FUNC,$@,kernel/porting/lib_$(CONFIG_LIB))
	$(call MAKE_FUNC,$@,kernel/porting/bsp_$(CONFIG))
	$(call MAKE_FUNC,$@,kernel/driver/lib_i2c_master)
	$(call MAKE_FUNC,$@,kernel/driver/lib_ubi_pio)
	$(call MAKE_FUNC,$@,kernel/driver/lib_lowpower)
	$(call MAKE_FUNC,$@,kernel/driver/lib_new_estk_api)
	$(call MAKE_FUNC,$@,kernel/driver/lib_motor_driver)
	$(call MAKE_FUNC,$@,application/project_ubitools/lib_default)
	$(call MAKE_FUNC,$@,application/project_ubitools/exe_week7)

rebuild: clean all
	@echo "\n[$$(pwd) : make "$@"]"

rebuildall:
	@echo "\n[$$(pwd) : make "$@"]"
	make cleanall
	make all

info:
	@echo "\n[$$(pwd) : make "$@"]"
	@echo "CONFIG_ARCH_COMMON : " $(CONFIG_ARCH_COMMON)
	@echo "CONFIG_ARCH        : " $(CONFIG_ARCH)
	@echo "CONFIG_BOARD       : " $(CONFIG_BOARD)
	@echo "CONFIG             : " $(CONFIG)
	@echo "OUTDIR             : " $(OUTDIR)
	
$(OUTDIR):
	mkdir -p $(OUTDIR)
