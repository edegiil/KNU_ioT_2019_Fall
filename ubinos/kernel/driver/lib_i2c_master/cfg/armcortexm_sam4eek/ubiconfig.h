#ifndef UBICONFIG_H__lib_i2c_master
#define UBICONFIG_H__lib_i2c_master

#define UBI_BUILDMODE__DEBUG					0
#define UBI_BUILDMODE__RELEASE					1
#define UBI_BUILDMODE							UBI_BUILDMODE__DEBUG
#define UBI_CPU_TYPE__ARM7TDMI					0
#define UBI_CPU_TYPE__ARM9						1
#define UBI_CPU_TYPE__ARM926EJ_S				2
#define UBI_CPU_TYPE__CORTEX_M3					3
#define UBI_CPU_TYPE__CORTEX_M4					4
#define UBI_CPU_TYPE							UBI_CPU_TYPE__CORTEX_M4
#define UBI_THUMB_MODE							1
#define UBI_THUMB_INTERWORK						0
#define UBI_LITTLE_ENDIAN						1
#define UBI_SUCHECK								1
#define UBI_SOCHECK								1
#define UBI_SOCHECK_TYPE						0
#define UBI_INCLUDE_STDLIB						0
#define UBI_GNUC								1

#include "cfg/property_prologue.h"



#include "cfg/property_epilogue.h"

#define UBI_COMPONENT__lib_i2c_master
#define UBI_COMCONFIG__lib_i2c_master

#endif /* UBICONFIG_H__lib_i2c_master */
