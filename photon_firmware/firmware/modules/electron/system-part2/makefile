MODULE=system-part2
SYSTEM_PART2_MODULE_PATH=.
PROJECT_ROOT = ../../..
BUILD_PATH_EXT = $(BUILD_TARGET_PLATFORM)
HAL_LINK :=
PLATFORM_DFU = 0x8040000

DEPENDENCIES = modules/electron/user-part modules/electron/system-part1 dynalib services services-dynalib hal platform system wiring communication-dynalib communication rt-dynalib wiring_globals
MAKE_DEPENDENCIES = services-dynalib system wiring communication-dynalib hal platform wiring_globals
include ../modular.mk
include $(PROJECT_ROOT)/build/platform-id.mk

LIBS += $(MAKE_DEPENDENCIES)
LIB_DEPS += $(SERVICES_DYNALIB_LIB_DEP) $(PLATFORM_LIB_DEP) $(HAL_LIB_DEP) $(SYSTEM_LIB_DEP) $(COMMUNICATION_DYNALIB_LIB_DEP) $(WIRING_LIB_DEP) $(WIRING_GLOBALS_LIB_DEP)
LIB_DIRS += $(dir $(LIB_DEPS))

TARGET=elf bin lst hex size


include $(PROJECT_ROOT)/build/arm-tlm.mk

$(call check_modular)


