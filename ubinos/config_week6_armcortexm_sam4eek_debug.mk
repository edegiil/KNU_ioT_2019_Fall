
CONFIG_APP_NAME			= week6

######################################################################
ITFDIR = $(realpath .)/interface

CONFIG_MODE = debug
CONFIG_PKG = week6
CONFIG_ARCH_COMMON = arm
CONFIG_ARCH = armcortexm
CONFIG_BOARD = sam4eek
CONFIG = armcortexm_sam4eek
CONFIG_LIB = sam4e

OUTDIR = $(realpath .)/out/$(CONFIG_PKG)_$(CONFIG)_$(CONFIG_MODE)

######################################################################