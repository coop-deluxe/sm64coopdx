# Makefile to rebuild SM64 split image

include util.mk

# Default target
default: all

# Preprocessor definitions
DEFINES :=
C_DEFINES :=

#==============================================================================#
# Build Options                                                                #
#==============================================================================#

# These options can either be set by building with 'make SETTING=value'.
# 'make clean' may be required first.

# Build debug version
DEBUG ?= 0

# Enable development/testing flags
DEVELOPMENT ?= 0

# Build for the N64 (turn this off for ports)
TARGET_N64 = 0

# Build and optimize for Raspberry Pi(s)
TARGET_RPI ?= 0

# Build and optimize for RK3588 processor
TARGET_RK3588 ?= 0

# Makeflag to enable OSX fixes
OSX_BUILD ?= 0

# Specify the target you are building for, TARGET_BITS=0 means native
TARGET_ARCH ?= native
TARGET_BITS ?= 0

# Disable texture fixes by default (helps with them purists)
TEXTURE_FIX ?= 0
# Enable level texture enhancements by default (Castle Grounds and Castle Courtyard recolorable texture hills)
ENHANCE_LEVEL_TEXTURES ?= 1
# Enable Discord Game SDK (used for Discord invites)
DISCORD_SDK ?= 1
# Enable CoopNet SDK (used for CoopNet server hosting)
COOPNET ?= 1
# Enable docker build workarounds
DOCKERBUILD ?= 0
# Sets your optimization level for building.
# A choice is made by default for you.
OPT_LEVEL ?= -1
# Enable compiling with more debug info.
DEBUG_INFO_LEVEL ?= 2
# Enable profiling
PROFILE ?= 0
# Enable address sanitizer
ASAN ?= 0
# Compile headless
HEADLESS ?= 0
# Enable Game ICON
ICON ?= 1
# Use .app (for macOS)
USE_APP ?= 1
# Minimum macOS Version
# If our arch is arm, set to macOS 14
ifeq ($(shell arch),arm64)
  MIN_MACOS_VERSION ?= 14
else
  MIN_MACOS_VERSION ?= 10.15
endif
# Make some small adjustments for handheld devices
HANDHELD ?= 0

# Various workarounds for weird toolchains
NO_BZERO_BCOPY ?= 0
NO_LDIV ?= 0

# Backend selection

# Renderers: GL, GL_LEGACY, D3D11, DUMMY
RENDER_API ?= GL
# Window managers: SDL1, SDL2, DXGI (forced if RENDER_API is D3D11), DUMMY (forced if RENDER_API is DUMMY)
WINDOW_API ?= SDL2
# Audio backends: SDL1, SDL2, DUMMY
AUDIO_API ?= SDL2
# Controller backends (can have multiple, space separated): SDL2, SDL1
CONTROLLER_API ?= SDL2

# Automatic settings for PC port(s)

WINDOWS_BUILD ?= 0

WINDOWS_AUTO_BUILDER ?= 0

# Setup extra cflags
EXTRA_CFLAGS ?=
EXTRA_CPP_FLAGS ?=
EXTRA_CFLAGS += -Wno-format-security -Wno-trigraphs

dev:; @$(MAKE) DEVELOPMENT=1

# COMPILER - selects the C compiler to use
#   gcc - uses the GNU C Compiler
COMPILER = gcc
$(eval $(call validate-option,COMPILER,ido gcc clang))

# Attempt to detect OS

ifeq ($(OS),Windows_NT)
  HOST_OS ?= Windows
else
  HOST_OS ?= $(shell uname -s 2>/dev/null || echo Unknown)
  # some weird MINGW/Cygwin env that doesn't define $OS
  ifneq (,$(findstring MINGW,HOST_OS))
    HOST_OS := Windows
  endif
endif

ifeq ($(HOST_OS),Windows)
  WINDOWS_BUILD := 1
endif

ifeq ($(HOST_OS),Darwin)
  OSX_BUILD := 1

  ifndef BREW_PREFIX
    BREW_PREFIX := $(shell brew --prefix)
  endif
endif

ifeq ($(HOST_OS),Linux)
  machine = $(shell sh -c 'uname -m 2>/dev/null || echo unknown')
  ifneq (,$(findstring aarch64,$(machine)))
    #Raspberry Pi 4-5
    TARGET_RPI = 1
  endif
  ifneq (,$(findstring arm,$(machine)))
    #Rasberry Pi zero, 2, 3, etc
    TARGET_RPI = 1
  endif
endif

# MXE overrides

ifeq ($(WINDOWS_BUILD),1)
  ifeq ($(CROSS),i686-w64-mingw32.static-)
    TARGET_ARCH = i386pe
    TARGET_BITS = 32
    NO_BZERO_BCOPY := 1
  else ifeq ($(CROSS),x86_64-w64-mingw32.static-)
    TARGET_ARCH = i386pe
    TARGET_BITS = 64
    NO_BZERO_BCOPY := 1
  endif
endif

# Determine default windows target bits

ifeq ($(WINDOWS_BUILD), 1)
  ifeq ($(TARGET_BITS), 0)
    CPU_TYPE := $(firstword $(subst -, ,$(shell $(CC) -dumpmachine)))
    ifeq ($(CPU_TYPE), x86_64)
      TARGET_BITS := 64
    else ifeq ($(CPU_TYPE), i686)
      TARGET_BITS := 32
    else ifeq ($(CPU_TYPE), mingw32)
      TARGET_BITS := 32
    endif
  endif
endif

ifneq ($(TARGET_BITS),0)
  BITS := -m$(TARGET_BITS)
endif

ifeq ($(WINDOWS_AUTO_BUILDER),1)
  export SHELL=sh.exe

  ifeq ($(TARGET_BITS),32)
    EXTRA_INCLUDES := ../include/1 ../include/2 ../include/3 ../include/4
    EXTRA_CPP_INCLUDES := -I../include/cpp
  else
    EXTRA_INCLUDES :=
    EXTRA_CPP_INCLUDES :=
  endif

  EXTRA_CFLAGS += -Wno-expansion-to-defined
  EXTRA_CPP_FLAGS := -Wno-class-conversion -Wno-packed-not-aligned
else
  EXTRA_INCLUDES ?=
  EXTRA_CPP_INCLUDES ?=
endif

ifeq ($(TARGET_BITS), 32)
    DEFINES += BITS_32=1
endif

# VERSION - selects the version of the game to build
#   jp - builds the 1996 Japanese version
#   us - builds the 1996 North American version
#   eu - builds the 1997 PAL version
#   sh - builds the 1997 Japanese Shindou version, with rumble pak support
VERSION ?= us
$(eval $(call validate-option,VERSION,us))

# Graphics microcode used
GRUCODE ?= f3dex2e

ifeq      ($(VERSION),jp)
  DEFINES   += VERSION_JP=1
  #GRUCODE   ?= f3d_old
  VERSION_JP_US  ?= true
else ifeq ($(VERSION),us)
  DEFINES   += VERSION_US=1
  #GRUCODE   ?= f3d_old
  VERSION_JP_US  ?= true
else ifeq ($(VERSION),eu)
  DEFINES   += VERSION_EU=1
  #GRUCODE   ?= f3d_new
  VERSION_JP_US  ?= false
else ifeq ($(VERSION),sh)
  DEFINES   += VERSION_SH=1
  #GRUCODE   ?= f3d_new
  VERSION_JP_US  ?= false
endif

# Determine our optimization level.
# Optimization Levels 0 through 5 optimize for speed,
# While optimization levels 6, and 7 optimize for size.
# If no optimization is specified, A default is chosen.
ifeq ($(OPT_LEVEL),0) # No optimization
  OPT_FLAGS := -O0
else ifeq ($(OPT_LEVEL),1) # Debugging optimization
  OPT_FLAGS := -Og
else ifeq ($(OPT_LEVEL),2) # Level 1 Optimization
  OPT_FLAGS := -O1
else ifeq ($(OPT_LEVEL),3) # Level 2 Optimization
  OPT_FLAGS := -O2
else ifeq ($(OPT_LEVEL),4) # Level 3 Optimization
  OPT_FLAGS := -O3
else ifeq ($(OPT_LEVEL),5) # Fastest Optimization
  OPT_FLAGS := -Ofast
else ifeq ($(OPT_LEVEL),6) # Size Optimization
  OPT_FLAGS := -Os
else ifeq ($(OPT_LEVEL),7) # Aggresive Size Optimization
  OPT_FLAGS := -Oz
else
  ifeq ($(DEBUG),0)
    # Can't use O2 or higher right now for auto-builders, coop-compiler produces strange graphical errors
    # likely due to undefined behavior somewhere
    #ifeq ($(WINDOWS_AUTO_BUILDER),1)
    #  OPT_FLAGS := -O1
    #else
    OPT_FLAGS := -O2
    #endif
  else
    OPT_FLAGS := -O0
  endif
endif

# Set our level of debug symbol info,
# Including an option to disable it.

# Level 0 produces no debug information at all. Thus, -g0 negates -g.
# Level 1 produces minimal information, enough for making backtraces in parts of the program that you don't plan to debug. This includes descriptions of functions and external variables, and line number tables, but no information about local variables.
# Level 3 includes extra information, such as all the macro definitions present in the program. Some debuggers support macro expansion when you use -g3.
# From https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html
ifeq ($(DEBUG_INFO_LEVEL),3)
  OPT_FLAGS += -g -g3
else ifeq ($(DEBUG_INFO_LEVEL),1)
  OPT_FLAGS += -g -g1
else ifeq ($(DEBUG_INFO_LEVEL),0)
  # If we're compiling with -0g. I don't believe this will do anything worthwhile.
  OPT_FLAGS += -g0
else
  # This is our default AND level 2.
  OPT_FLAGS += -g
endif

ifeq ($(PROFILE),1)
  PROF_FLAGS := -pg
else
  PROF_FLAGS :=
endif

ifeq ($(TARGET_RPI),1)
  $(info Compiling for Raspberry Pi)
  DISCORD_SDK := 0

    # Raspberry Pi B+, Zero, etc
	ifneq (,$(findstring armv6l,$(machine)))
		OPT_FLAGS := -march=armv6zk+fp -mfpu=vfp -Ofast
	endif

    # Raspberry Pi 2 and 3 in ARM 32bit mode
	ifneq (,$(findstring armv7l,$(machine)))
  $(info ARM 32bit mode)
		model = $(shell sh -c 'cat /sys/firmware/devicetree/base/model 2>/dev/null || echo unknown')
		ifneq (,$(findstring 3,$(model)))
			 OPT_FLAGS := -march=armv8-a+crc -mtune=cortex-a53 -mfpu=neon-fp-armv8 -O3
		else
			 OPT_FLAGS := -march=armv7-a -mtune=cortex-a7 -mfpu=neon-vfpv4 -O3
		endif
	endif

    # RPi3 or RPi4, in ARM64 (aarch64) mode. NEEDS TESTING 32BIT.
    # DO NOT pass -mfpu stuff here, thats for 32bit ARM only and will fail for 64bit ARM.
	ifneq (,$(findstring aarch64,$(machine)))
    $(info ARM64 mode)
		model = $(shell sh -c 'cat /sys/firmware/devicetree/base/model 2>/dev/null || echo unknown')
		ifneq (,$(findstring 3,$(model)))
			 OPT_FLAGS := -march=armv8-a+crc -mtune=cortex-a53 -O3
		else ifneq (,$(findstring 4,$(model)))
			 OPT_FLAGS := -march=armv8-a+crc+simd -mtune=cortex-a72 -O3
		endif
	endif
endif

ifeq ($(TARGET_RK3588),1)
  $(info Compiling for RK3588)
  DISCORD_SDK := 0
  COOPNET := 0
  machine = $(shell sh -c 'uname -m 2>/dev/null || echo unknown')

  # RK3588 in ARM64 (aarch64) mode
  $(info ARM64 mode)
  OPT_FLAGS := -march=armv8.2-a+crc+simd -mtune=cortex-a76 -O3
endif

# Set BITS (32/64) to compile for
OPT_FLAGS += $(BITS)

TARGET := sm64.$(VERSION)

# GRUCODE - selects which RSP microcode to use.
#   f3d_old - default for JP and US versions
#   f3d_new - default for EU and Shindou versions
#   f3dex   -
#   f3dex2  -
#   f3dex2e - default for PC Port
#   f3dzex  - newer, experimental microcode used in Animal Crossing
$(eval $(call validate-option,GRUCODE,f3d_old f3dex f3dex2 f3dex2e f3d_new f3dzex))

ifeq      ($(GRUCODE),f3d_old)
  DEFINES += F3D_OLD=1
else ifeq ($(GRUCODE),f3d_new) # Fast3D 2.0H
  DEFINES += F3D_NEW=1
else ifeq ($(GRUCODE),f3dex) # Fast3DEX
  DEFINES += F3DEX_GBI=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE), f3dex2) # Fast3DEX2
  DEFINES += F3DEX_GBI_2=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE), f3dex2e) # Fast3DEX2 Extended (PC default)
  DEFINES += F3DEX_GBI_2E=1 F3DEX_GBI_SHARED=1
else ifeq ($(GRUCODE),f3dzex) # Fast3DZEX (2.0J / Animal Forest - Dōbutsu no Mori)
  $(warning Fast3DZEX is experimental. Try at your own risk.)
  DEFINES += F3DZEX_GBI_2=1 F3DEX_GBI_2=1 F3DEX_GBI_SHARED=1
endif

# Check for certain target types.

ifeq ($(TARGET_RPI),1) # Define RPi to change SDL2 title & GLES2 hints
     DEFINES += USE_GLES=1
endif

ifeq ($(TARGET_RK3588),1) # Define RK3588 to change SDL2 title & GLES2 hints
  DEFINES += USE_GLES=1
endif

ifeq ($(OSX_BUILD),1) # Modify GFX & SDL2 for OSX GL
     DEFINES += OSX_BUILD=1
endif

# Check backends

ifneq (,$(filter $(RENDER_API),D3D11))
  ifneq ($(WINDOWS_BUILD),1)
    $(error DirectX is only supported on Windows)
  endif
  ifneq ($(WINDOW_API),DXGI)
    $(warning DirectX renderers require DXGI, forcing WINDOW_API value)
    WINDOW_API := DXGI
  endif
else
  ifeq ($(WINDOW_API),DXGI)
    $(error DXGI can only be used with DirectX renderers)
  endif
  ifneq ($(WINDOW_API),DUMMY)
    ifeq ($(RENDER_API),DUMMY)
      $(warning Dummy renderer requires dummy window API, forcing WINDOW_API value)
      WINDOW_API := DUMMY
    endif
  else
    ifneq ($(RENDER_API),DUMMY)
      $(warning Dummy window API requires dummy renderer, forcing RENDER_API value)
      RENDER_API := DUMMY
    endif
  endif
endif

ifeq ($(HEADLESS),1)
  $(info Compiling headless)
  RENDER_API := DUMMY
  WINDOW_API := DUMMY
  AUDIO_API := DUMMY
  CONTROLLER_API :=
endif

# NON_MATCHING - whether to build a matching, identical copy of the ROM
#   1 - enable some alternate, more portable code that does not produce a matching ROM
#   0 - build a matching ROM
NON_MATCHING ?= 0
$(eval $(call validate-option,NON_MATCHING,0 1))

ifeq ($(TARGET_N64),0)
  NON_MATCHING := 1
endif

ifeq ($(NON_MATCHING),1)
  DEFINES += NON_MATCHING=1 AVOID_UB=1
endif

ifeq ($(OSX_BUILD),0)
	USE_APP := 0
endif

# Whether to hide commands or not
VERBOSE ?= 0
ifeq ($(VERBOSE),0)
  V := @
endif

# Whether to colorize build messages
COLOR ?= 1

# display selected options unless 'make clean' or 'make distclean' is run
ifeq ($(filter clean distclean,$(MAKECMDGOALS)),)
  $(info ==== Build Options ====)
  $(info Version:        $(VERSION))
  $(info Microcode:      $(GRUCODE))
  ifeq ($(NON_MATCHING),1)
    $(info Build Matching: no)
  else
    $(info Build Matching: yes)
  endif
  $(info =======================)
endif


#==============================================================================#
# Universal Dependencies                                                       #
#==============================================================================#

TOOLS_DIR := tools

# (This is a bit hacky, but a lot of rules implicitly depend
# on tools and assets, and we use directory globs further down
# in the makefile that we want should cover assets.)

PYTHON := python3

ifeq ($(filter clean distclean print-%,$(MAKECMDGOALS)),)
  ifeq ($(WINDOWS_AUTO_BUILDER),0)
    $(info Building tools...)
    DUMMY != $(MAKE) -C $(TOOLS_DIR) >&2 || echo FAIL
      ifeq ($(DUMMY),FAIL)
        $(error Failed to build tools)
      endif
  endif

  $(info Building Game...)

endif

#==============================================================================#
# Extra Source Files                                                           #
#==============================================================================#

# Copy missing instrument samples from the music sound banks
_ := $(shell $(PYTHON) $(TOOLS_DIR)/copy_extended_sounds.py)

#==============================================================================#
# Target Executable and Sources                                                #
#==============================================================================#

BUILD_DIR_BASE := build
# BUILD_DIR is the location where all build artifacts are placed
BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_pc

ifeq ($(WINDOWS_BUILD),1)
	EXE := $(BUILD_DIR)/sm64coopdx.exe
else # Linux builds/binary namer
	ifeq ($(TARGET_RPI),1)
		EXE := $(BUILD_DIR)/sm64coopdx.arm
	else
		EXE := $(BUILD_DIR)/sm64coopdx
	endif
endif

ifeq ($(TARGET_RK3588),1)
  EXE := $(BUILD_DIR)/sm64coopdx.arm
endif

ELF            := $(BUILD_DIR)/$(TARGET).elf
LIBULTRA       := $(BUILD_DIR)/libultra.a
LD_SCRIPT      := sm64.ld
MIO0_DIR       := $(BUILD_DIR)/bin
SOUND_BIN_DIR  := $(BUILD_DIR)/sound
TEXTURE_DIR    := textures
ACTOR_DIR      := actors
LEVEL_DIRS     := $(patsubst levels/%,%,$(dir $(wildcard levels/*/header.h)))

# Directories containing source files
SRC_DIRS := src src/engine src/game src/audio src/menu src/buffers actors levels bin data assets asm lib sound
BIN_DIRS := bin bin/$(VERSION)

# PC files
SRC_DIRS += src/pc src/pc/gfx src/pc/audio src/pc/controller src/pc/fs src/pc/fs/packtypes src/pc/mods src/pc/dev src/pc/network src/pc/network/packets src/pc/network/socket src/pc/network/coopnet src/pc/utils src/pc/utils/miniz src/pc/djui src/pc/lua src/pc/lua/utils src/pc/os

ifeq ($(DISCORD_SDK),1)
  SRC_DIRS += src/pc/discord
endif

SRC_DIRS += src/pc/mumble

ULTRA_SRC_DIRS := lib/src lib/src/math lib/asm lib/data
ULTRA_BIN_DIRS := lib/bin

GODDARD_SRC_DIRS := src/goddard src/goddard/dynlists

# File dependencies and variables for specific files
include Makefile.split

# Dynos
include dynos.mk

# Source code files
LEVEL_C_FILES     := $(wildcard levels/*/leveldata.c) $(wildcard levels/*/script.c) $(wildcard levels/*/geo.c)
C_FILES           := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c)) $(LEVEL_C_FILES)
CPP_FILES         := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))
S_FILES           := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.s))
ULTRA_C_FILES     := $(foreach dir,$(ULTRA_SRC_DIRS),$(wildcard $(dir)/*.c))
GODDARD_C_FILES   := $(foreach dir,$(GODDARD_SRC_DIRS),$(wildcard $(dir)/*.c))
ULTRA_S_FILES     := $(foreach dir,$(ULTRA_SRC_DIRS),$(wildcard $(dir)/*.s))
GENERATED_C_FILES := $(BUILD_DIR)/assets/mario_anim_data.c $(BUILD_DIR)/assets/demo_data.c

#ifeq ($(TARGET_N64),0)
#  GENERATED_C_FILES += $(addprefix $(BUILD_DIR)/bin/,$(addsuffix _skybox.c,$(notdir $(basename $(wildcard textures/skyboxes/*.png)))))
#endif

# "If we're N64, use the above"
ifeq ($(TARGET_N64),0)
	ULTRA_C_FILES := \
	  alBnkfNew.c \
	  guLookAtRef.c \
	  guMtxF2L.c \
	  guNormalize.c \
	  guOrthoF.c \
	  guPerspectiveF.c \
	  guRotateF.c \
	  guScaleF.c \
	  guTranslateF.c \
	  ldiv.c

	C_FILES           := $(filter-out src/game/main.c,$(C_FILES))
	ULTRA_C_FILES     := $(addprefix lib/src/,$(ULTRA_C_FILES))
endif

# Sound files
SOUND_BANK_FILES    := $(wildcard sound/sound_banks/*.json)
SOUND_SAMPLE_DIRS   := $(wildcard sound/samples/*)
SOUND_SAMPLE_AIFFS  := $(foreach dir,$(SOUND_SAMPLE_DIRS),$(wildcard $(dir)/*.aiff))
SOUND_SAMPLE_TABLES := $(foreach file,$(SOUND_SAMPLE_AIFFS),$(BUILD_DIR)/$(file:.aiff=.table))
SOUND_SAMPLE_AIFCS  := $(foreach file,$(SOUND_SAMPLE_AIFFS),$(BUILD_DIR)/$(file:.aiff=.aifc))
SOUND_SEQUENCE_DIRS := sound/sequences sound/sequences/$(VERSION)
# all .m64 files in SOUND_SEQUENCE_DIRS, plus all .m64 files that are generated from .s files in SOUND_SEQUENCE_DIRS
SOUND_SEQUENCE_FILES := \
  $(foreach dir,$(SOUND_SEQUENCE_DIRS),\
    $(wildcard $(dir)/*.m64) \
    $(foreach file,$(wildcard $(dir)/*.s),$(BUILD_DIR)/$(file:.s=.m64)) \
  )

# Object files
O_FILES := $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file:.c=.o)) \
           $(foreach file,$(CPP_FILES),$(BUILD_DIR)/$(file:.cpp=.o)) \
           $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
           $(foreach file,$(GENERATED_C_FILES),$(file:.c=.o))

ULTRA_O_FILES := $(foreach file,$(ULTRA_S_FILES),$(BUILD_DIR)/$(file:.s=.o)) \
                 $(foreach file,$(ULTRA_C_FILES),$(BUILD_DIR)/$(file:.c=.o))

GODDARD_O_FILES := $(foreach file,$(GODDARD_C_FILES),$(BUILD_DIR)/$(file:.c=.o))

RPC_LIBS :=
DISCORD_SDK_LIBS :=

ifeq ($(DISCORD_SDK), 1)
  ifeq ($(WINDOWS_BUILD),1)
    ifeq ($(TARGET_BITS), 32)
      DISCORD_SDK_LIBS := lib/discordsdk/x86/discord_game_sdk.dll
    else
      DISCORD_SDK_LIBS := lib/discordsdk/discord_game_sdk.dll
    endif
  else ifeq ($(OSX_BUILD),1)
    # needs testing
    # HACKY! Instead of figuring out all of the dynamic library linking madness...
    # I copied the library and gave it two names.
    # This really shouldn't be required, but I got tired of trying to do it the "right way"
    ifeq ($(shell uname -m),arm64) # A hacky way of determining if the user is running on Apple Silicon hardware
      DISCORD_SDK_LIBS := lib/discordsdk/aarch64/discord_game_sdk.dylib lib/discordsdk/aarch64/libdiscord_game_sdk.dylib
    else
      DISCORD_SDK_LIBS := lib/discordsdk/discord_game_sdk.dylib lib/discordsdk/libdiscord_game_sdk.dylib
    endif
  else
    DISCORD_SDK_LIBS := lib/discordsdk/libdiscord_game_sdk.so
  endif
endif

LANG_DIR := lang

# Remove old lang dir
_ := $(shell rm -rf ./$(BUILD_DIR)/$(LANG_DIR))

MOD_DIR := mods

# Remove old mod dir
_ := $(shell $(PYTHON) $(TOOLS_DIR)/remove_built_in_mods.py)

PALETTES_DIR := palettes

# Remove old palettes dir
_ := $(shell rm -rf ./$(BUILD_DIR)/$(PALETTES_DIR))

# Automatic dependency files
DEP_FILES := $(O_FILES:.o=.d) $(ULTRA_O_FILES:.o=.d) $(GODDARD_O_FILES:.o=.d) $(BUILD_DIR)/$(LD_SCRIPT).d

# Segment elf files
SEG_FILES := $(SEGMENT_ELF_FILES) $(ACTOR_ELF_FILES) $(LEVEL_ELF_FILES)

# Files with GLOBAL_ASM blocks
ifeq ($(NON_MATCHING),0)
  ifeq ($(VERSION),sh)
    GLOBAL_ASM_C_FILES != grep -rl 'GLOBAL_ASM(' $(wildcard src/**/*.c) $(wildcard lib/src/*.c)
  else
    GLOBAL_ASM_C_FILES != grep -rl 'GLOBAL_ASM(' $(wildcard src/**/*.c)
  endif
GLOBAL_ASM_O_FILES = $(foreach file,$(GLOBAL_ASM_C_FILES),$(BUILD_DIR)/$(file:.c=.o))
GLOBAL_ASM_DEP = $(BUILD_DIR)/src/audio/non_matching_dep
endif


#==============================================================================#
# Compiler Options                                                             #
#==============================================================================#

AS        := $(CROSS)as

ifeq ($(OSX_BUILD),1)
  AS := i686-w64-mingw32-as
endif

ifeq ($(WINDOWS_AUTO_BUILDER),1)
  CC      := cc
  CXX     := g++
else ifeq ($(COMPILER),gcc)
  CC      := $(CROSS)gcc
  CXX     := $(CROSS)g++
  ifeq ($(OSX_BUILD),0)
	  EXTRA_CFLAGS += -Wno-unused-result -Wno-format-truncation
  else
	  EXTRA_CFLAGS += -Wno-unused-result -mmacosx-version-min=$(MIN_MACOS_VERSION)
  endif
else ifeq ($(COMPILER),clang)
  CC      := clang
  CXX     := clang++
  CPP     := clang++
  EXTRA_CFLAGS += -Wno-unused-function -Wno-unused-variable -Wno-unknown-warning-option -Wno-self-assign -Wno-unknown-pragmas -Wno-unused-result
else
  ifeq ($(USE_QEMU_IRIX),1)
    IRIX_ROOT := $(TOOLS_DIR)/ido5.3_compiler
    CC      := $(QEMU_IRIX) -silent -L $(IRIX_ROOT) $(IRIX_ROOT)/usr/bin/cc
    ACPP    := $(QEMU_IRIX) -silent -L $(IRIX_ROOT) $(IRIX_ROOT)/usr/lib/acpp
    COPT    := $(QEMU_IRIX) -silent -L $(IRIX_ROOT) $(IRIX_ROOT)/usr/lib/copt
  else
    IDO_ROOT := $(TOOLS_DIR)/ido5.3_recomp
    CC      := $(IDO_ROOT)/cc
    ACPP    := $(IDO_ROOT)/acpp
    COPT    := $(IDO_ROOT)/copt
  endif
endif

ifeq ($(WINDOWS_BUILD),1) # fixes compilation in MXE on Linux and WSL
  CPP := cpp -P
  OBJCOPY := objcopy
  OBJDUMP := $(CROSS)objdump
else ifeq ($(OSX_BUILD),1)
  OSX_GCC_VER = $(shell find $(BREW_PREFIX)/bin/gcc* | grep -oE '[[:digit:]]+' | sort -n | uniq | tail -1)
  # if we couldn't find a gcc ver, default to 9
  ifeq ($(OSX_GCC_VER),)
    OSX_GCC_VER = 9
  endif
  CPP := cpp-$(OSX_GCC_VER) -P
  OBJDUMP := i686-w64-mingw32-objdump
  OBJCOPY := i686-w64-mingw32-objcopy
else ifeq ($(TARGET_N64),0) # Linux & other builds
  CPP := $(CROSS)cpp -P
  OBJCOPY := $(CROSS)objcopy
  OBJDUMP := $(CROSS)objdump
else
  # Prefer gcc's cpp if installed on the system
  ifneq (,$(call find-command,cpp-10))
    CPP     := cpp-10
  else
    CPP     := cpp
  endif
  OBJDUMP := $(CROSS)objdump
  OBJCOPY := $(CROSS)objcopy
endif

# thank you apple very cool
ifeq ($(HOST_OS),Darwin)
  CP := gcp
else
  CP := cp
endif

ifeq ($(DISCORD_SDK),1)
  LD := $(CXX)
else ifeq ($(WINDOWS_BUILD),1)
  ifeq ($(CROSS),i686-w64-mingw32.static-) # fixes compilation in MXE on Linux and WSL
    LD := $(CC)
  else ifeq ($(CROSS),x86_64-w64-mingw32.static-)
    LD := $(CC)
  else
    LD := $(CXX)
  endif
else
  LD := $(CXX)
endif

AR        := $(CROSS)ar

ifeq ($(TARGET_N64),1)
  TARGET_CFLAGS := -nostdinc -DTARGET_N64 -D_LANGUAGE_C
  CC_CFLAGS := -fno-builtin
else
  TARGET_CFLAGS := -D_LANGUAGE_C
  TARGET_CFLAGS += $(EXTRA_CFLAGS)
endif


INCLUDE_DIRS := include $(BUILD_DIR) $(BUILD_DIR)/include src .
ifeq ($(TARGET_N64),1)
  INCLUDE_DIRS += include/libc
else
  INCLUDE_DIRS += sound lib/lua/include lib/coopnet/include $(EXTRA_INCLUDES)
endif

# Connfigure backend flags

SDLCONFIG := $(CROSS)sdl2-config

BACKEND_CFLAGS := -DRAPI_$(RENDER_API)=1 -DWAPI_$(WINDOW_API)=1 -DAAPI_$(AUDIO_API)=1
# can have multiple controller APIs
BACKEND_CFLAGS += $(foreach capi,$(CONTROLLER_API),-DCAPI_$(capi)=1)
BACKEND_LDFLAG0S :=

SDL1_USED := 0
SDL2_USED := 0

# for now, it's either SDL+GL or DXGI+DirectX, so choose based on WAPI
ifeq ($(WINDOW_API),DXGI)
  DXBITS := `cat $(ENDIAN_BITWIDTH) | tr ' ' '\n' | tail -1`
  BACKEND_LDFLAGS += -ld3dcompiler -ldxgi -ldxguid
  BACKEND_LDFLAGS += -lsetupapi -ldinput8 -luser32 -lgdi32 -limm32 -lole32 -loleaut32 -lshell32 -lwinmm -lversion -luuid -static
else ifeq ($(findstring SDL,$(WINDOW_API)),SDL)
  ifeq ($(WINDOWS_BUILD),1)
    BACKEND_LDFLAGS += -lglew32 -lglu32 -lopengl32
  else ifeq ($(TARGET_RPI),1)
    BACKEND_LDFLAGS += -lGLESv2
  else ifeq ($(TARGET_RK3588),1)
    BACKEND_LDFLAGS += -lGLESv2
  else ifeq ($(OSX_BUILD),1)
    BACKEND_LDFLAGS += -framework OpenGL `pkg-config --libs glew` -mmacosx-version-min=$(MIN_MACOS_VERSION)
    EXTRA_CPP_FLAGS += -stdlib=libc++ -std=c++17 -mmacosx-version-min=$(MIN_MACOS_VERSION)
  else
    BACKEND_LDFLAGS += -lGL
   endif
endif

ifeq ($(WINDOW_API),DUMMY)
  ifeq ($(WINDOWS_BUILD),1)
    BACKEND_LDFLAGS += -lole32 -luuid -lshlwapi
  endif
endif

ifneq (,$(findstring SDL2,$(AUDIO_API)$(WINDOW_API)$(CONTROLLER_API)))
  SDL2_USED := 1
endif

ifneq (,$(findstring SDL1,$(AUDIO_API)$(WINDOW_API)$(CONTROLLER_API)))
  SDL1_USED := 1
endif

ifeq ($(SDL1_USED)$(SDL2_USED),11)
  $(error Cannot link both SDL1 and SDL2 at the same time)
endif

# SDL can be used by different systems, so we consolidate all of that shit into this

ifeq ($(SDL2_USED),1)
  SDLCONFIG := $(CROSS)sdl2-config
  BACKEND_CFLAGS += -DHAVE_SDL2=1
else ifeq ($(SDL1_USED),1)
  SDLCONFIG := $(CROSS)sdl-config
  BACKEND_CFLAGS += -DHAVE_SDL1=1
endif

ifneq ($(SDL1_USED)$(SDL2_USED),00)
  ifeq ($(OSX_BUILD),1)
    # on OSX at least the homebrew version of sdl-config gives include path as `.../include/SDL2` instead of `.../include`
    OSX_PREFIX := $(shell $(SDLCONFIG) --prefix)
    BACKEND_CFLAGS += -I$(OSX_PREFIX)/include $(shell $(SDLCONFIG) --cflags)
  else
    BACKEND_CFLAGS += `$(SDLCONFIG) --cflags`
  endif

  ifeq ($(WINDOWS_BUILD),1)
    BACKEND_LDFLAGS += `$(SDLCONFIG) --static-libs` -lsetupapi -luser32 -limm32 -lole32 -loleaut32 -lshell32 -lshlwapi -lwinmm -lversion
  else
    BACKEND_LDFLAGS += `$(SDLCONFIG) --libs`
  endif
endif

C_DEFINES += $(foreach d,$(DEFINES),-D$(d))
DEF_INC_CFLAGS := $(foreach i,$(INCLUDE_DIRS),-I$(i)) $(C_DEFINES)

# Check code syntax with host compiler
CC_CHECK := $(CC)

ifeq ($(WINDOWS_BUILD),1)
  CC_CHECK_CFLAGS := -fsyntax-only -fsigned-char $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -Wall -Wextra $(TARGET_CFLAGS) -DWINSOCK
  CFLAGS := $(OPT_FLAGS) $(DEF_INC_CFLAGS) $(BACKEND_CFLAGS) $(TARGET_CFLAGS) -fno-strict-aliasing -fwrapv -DWINSOCK

  ifeq ($(TARGET_BITS), 32)
    BACKEND_LDFLAGS += -ldbghelp
  endif
else ifeq ($(TARGET_N64),0) # Linux / Other builds below
  CC_CHECK_CFLAGS := -fsyntax-only -fsigned-char $(BACKEND_CFLAGS) $(DEF_INC_CFLAGS) -Wall -Wextra $(TARGET_CFLAGS)
  CFLAGS := $(OPT_FLAGS) $(DEF_INC_CFLAGS) $(BACKEND_CFLAGS) $(TARGET_CFLAGS) -fno-strict-aliasing -fwrapv
else # C compiler options for N64
  CC_CHECK_CFLAGS := -fsyntax-only -fsigned-char $(CC_CFLAGS) $(TARGET_CFLAGS) -std=gnu90 -Wall -Wextra -Wno-main -DNON_MATCHING -DAVOID_UB $(DEF_INC_CFLAGS)
  CFLAGS = -G 0 $(OPT_FLAGS) $(TARGET_CFLAGS) $(MIPSISET) $(DEF_INC_CFLAGS)
  ifeq ($(COMPILER),gcc)
    CFLAGS += -mno-shared -march=vr4300 -mfix4300 -mabi=32 -mhard-float -mdivide-breaks -fno-stack-protector -fno-common -fno-zero-initialized-in-bss -fno-PIC -mno-abicalls -fno-strict-aliasing -fno-inline-functions -ffreestanding -fwrapv -Wall -Wextra
  else
    CFLAGS += -non_shared -Wab,-r4300_mul -Xcpluscomm -Xfullwarn -signed -32
  endif
endif

ifeq ($(TARGET_N64),1)
  ASFLAGS     := -march=vr4300 -mabi=32 $(foreach i,$(INCLUDE_DIRS),-I$(i)) $(foreach d,$(DEFINES),--defsym $(d))
  RSPASMFLAGS := $(foreach d,$(DEFINES),-definelabel $(subst =, ,$(d)))
else
  ASFLAGS     := $(foreach i,$(INCLUDE_DIRS),-I$(i)) $(foreach d,$(DEFINES),--defsym $(d))
  RSPASMFLAGS :=
endif

# C preprocessor flags
CPPFLAGS := -P -Wno-trigraphs $(DEF_INC_CFLAGS)

ifeq ($(TARGET_N64),1)
  ifeq ($(shell getconf LONG_BIT), 32)
    # Work around memory allocation bug in QEMU
    export QEMU_GUEST_BASE := 1
  else
    # Ensure that gcc treats the code as 32-bit
    CC_CHECK_CFLAGS += -m32
  endif
endif

ifeq ($(WINDOWS_BUILD),1)
  LDFLAGS := $(BITS) -march=$(TARGET_ARCH) -Llib -lpthread $(BACKEND_LDFLAGS) -static -mconsole
  ifeq ($(CROSS),)
    LDFLAGS += -no-pie
  endif
  LDFLAGS += -T windows.ld
else ifeq ($(TARGET_RPI),1)
  LDFLAGS := $(OPT_FLAGS) -lm $(BACKEND_LDFLAGS) -no-pie
else ifeq ($(TARGET_RK3588),1)
  LDFLAGS := $(OPT_FLAGS) -lm $(BACKEND_LDFLAGS) -no-pie
else ifeq ($(OSX_BUILD),1)
  LDFLAGS := -lm $(BACKEND_LDFLAGS) -lpthread
else
  LDFLAGS := $(BITS) -march=$(TARGET_ARCH) -lm $(BACKEND_LDFLAGS) -no-pie -lpthread
endif

# used by crash handler and loading screen on linux
ifeq ($(WINDOWS_BUILD),0)
  LDFLAGS += -rdynamic -ldl -pthread
endif

# icon
ifeq ($(WINDOWS_BUILD),1)
  ifeq ($(ICON),1)
    Command := mkdir -p "$(BUILD_DIR)/res"
    Resp := $(shell $(call Command))
    Command := windres -o "$(BUILD_DIR)/res/icon.o" -i "res/icon.rc" --preprocessor $(word 1, $(CC)) --preprocessor-arg -E --preprocessor-arg -xc-header --preprocessor-arg -DRC_INVOKED
    Resp := $(shell $(call Command))
    ifeq ($(.SHELLSTATUS),0)
      LDFLAGS += $(BUILD_DIR)/res/icon.o
    endif
  endif
endif

ifeq ($(ASAN),1)

  ifeq ($(COMPILER),gcc)
    EXTRA_CFLAGS += -fsanitize=address -fsanitize=bounds-strict -fsanitize=undefined -ggdb
    EXTRA_CPP_FLAGS += -fsanitize=address -fsanitize=bounds-strict -fsanitize=undefined -ggdb
    LDFLAGS += -fsanitize=address -fsanitize=bounds-strict -fsanitize=undefined -static-libasan
  else ifeq ($(COMPILER),clang)
    EXTRA_CFLAGS += -fsanitize=address -fsanitize=undefined -ggdb
    EXTRA_CPP_FLAGS += -fsanitize=address -fsanitize=undefined -ggdb
    LDFLAGS += -fsanitize=address -fsanitize=undefined
  endif

endif

# Coop specific libraries

# Zlib
LDFLAGS += -lz

# Update checker library
ifeq ($(WINDOWS_BUILD),1)
  LDFLAGS += -lwininet
else
  LDFLAGS += -lcurl
endif

# Lua
ifeq ($(WINDOWS_BUILD),1)
  ifeq ($(TARGET_BITS), 32)
    LDFLAGS += -Llib/lua/win32 -l:liblua53.a
  else
    LDFLAGS += -Llib/lua/win64 -l:liblua53.a
  endif
else ifeq ($(OSX_BUILD),1)
  ifeq ($(shell uname -m),arm64)
    LDFLAGS += -L./lib/lua/mac_arm/ -l lua53
  else
    LDFLAGS += -L./lib/lua/mac_intel/ -l lua53
  endif
else ifeq ($(TARGET_RPI),1)
	ifneq (,$(findstring aarch64,$(machine)))
    LDFLAGS += -Llib/lua/linux -l:liblua53-arm64.a
  else
    LDFLAGS += -Llib/lua/linux -l:liblua53-arm.a
  endif
else ifeq ($(TARGET_RK3588),1)
  LDFLAGS += -Llib/lua/linux -l:liblua53-arm64.a
else
  LDFLAGS += -Llib/lua/linux -l:liblua53.a -ldl
endif

# CoopNet
COOPNET_LIBS :=
ifeq ($(COOPNET),1)
  ifeq ($(WINDOWS_BUILD),1)
    ifeq ($(TARGET_BITS), 32)
      LDFLAGS += -Llib/coopnet/win32 -l:libcoopnet.a -l:libjuice.a -lbcrypt -liphlpapi
    else
      LDFLAGS += -Llib/coopnet/win64 -l:libcoopnet.a -l:libjuice.a -lbcrypt -liphlpapi
    endif
  else ifeq ($(OSX_BUILD),1)
    ifeq ($(shell uname -m),arm64)
      LDFLAGS += -Wl,-rpath,@loader_path -L./lib/coopnet/mac_arm/ -l coopnet
      COOPNET_LIBS += ./lib/coopnet/mac_arm/libcoopnet.dylib
      COOPNET_LIBS += ./lib/coopnet/mac_arm/libjuice.1.2.2.dylib
    else
      LDFLAGS += -Wl,-rpath,@loader_path -L./lib/coopnet/mac_intel/ -l coopnet
      COOPNET_LIBS += ./lib/coopnet/mac_intel/libcoopnet.dylib
      COOPNET_LIBS += ./lib/coopnet/mac_intel/libjuice.1.2.2.dylib
    endif
  else ifeq ($(TARGET_RPI),1)
    ifneq (,$(findstring aarch64,$(machine)))
      LDFLAGS += -Llib/coopnet/linux -l:libcoopnet-arm64.a -l:libjuice-arm64.a
    else
      LDFLAGS += -Llib/coopnet/linux -l:libcoopnet-arm.a -l:libjuice-arm.a
    endif
  else ifeq ($(TARGET_RK3588),1)
    LDFLAGS += -Llib/coopnet/linux -l:libcoopnet-arm64.a -l:libjuice.a
  else
    LDFLAGS += -Llib/coopnet/linux -l:libcoopnet.a -l:libjuice.a
  endif
endif

# Network/Discord (ugh, needs cleanup)
ifeq ($(WINDOWS_BUILD),1)
  LDFLAGS += -lws2_32 -lwsock32
  ifeq ($(DISCORD_SDK),1)
    LDFLAGS += -Wl,-Bdynamic -L./lib/discordsdk/ -ldiscord_game_sdk -Wl,-Bstatic
  endif
else
  ifeq ($(DISCORD_SDK),1)
    LDFLAGS += -ldiscord_game_sdk -Wl,-rpath . -Wl,-rpath lib/discordsdk
  endif
endif

IS_DEV_OR_DEBUG := $(or $(filter 1,$(DEVELOPMENT)),$(filter 1,$(DEBUG)),0)
ifeq ($(IS_DEV_OR_DEBUG),0)
  CFLAGS += -fno-ident -fno-common -ffile-prefix-map="$(PWD)"=. -D__DATE__="\"\"" -D__TIME__="\"\"" -Wno-builtin-macro-redefined
  ifeq ($(OSX_BUILD),0)
    LDFLAGS += -Wl,--build-id=none
  endif
else
  # Stuff for showing the git hash and build time in dev builds
  # Originally from https://stackoverflow.com/questions/44038428/include-git-commit-hash-and-or-branch-name-in-c-c-source
  GIT_HASH=$(shell git rev-parse --short HEAD)
  COMPILE_TIME=$(shell date -u +'%Y-%m-%d %H:%M:%S UTC')
  C_DEFINES += -DGIT_HASH="\"$(GIT_HASH)\"" -DCOMPILE_TIME="\"$(COMPILE_TIME)\""
endif

# Enable ASLR
CFLAGS += -fPIE

# Prevent a crash with -sopt
export LANG := C

ifeq ($(OSX_BUILD),0)
  LDFLAGS += -latomic
endif

#==============================================================================#
# Extra CC Flags                                                               #
#==============================================================================#

# Enforce -Werror in strict mode
ifeq ($(STRICT),1)
  CC_CHECK_CFLAGS += -Werror
  CFLAGS += -Werror
endif

# Check for debug option
ifeq ($(DEBUG),1)
  CC_CHECK_CFLAGS += -DDEBUG
  CFLAGS += -DDEBUG
endif

# Check for enhancement options

# Check for docker build workaround option
ifeq ($(DOCKERBUILD),1)
  CC_CHECK_CFLAGS += -DDOCKERBUILD
  CFLAGS += -DDOCKERBUILD
endif

# Check for Discord SDK option
ifeq ($(DISCORD_SDK),1)
  CC_CHECK_CFLAGS += -DDISCORD_SDK
  CFLAGS += -DDISCORD_SDK
endif

# Check for COOPNET option
ifeq ($(COOPNET),1)
  CC_CHECK_CFLAGS += -DCOOPNET
  CFLAGS += -DCOOPNET
endif

# Check for development option
ifeq ($(DEVELOPMENT),1)
  CC_CHECK_CFLAGS += -DDEVELOPMENT
  CFLAGS += -DDEVELOPMENT
endif

# Check for rpi option
ifeq ($(TARGET_RPI),1)
  CC_CHECK_CFLAGS += -DTARGET_RPI
  CFLAGS += -DTARGET_RPI
endif

# Check for rk3588 option
ifeq ($(TARGET_RK3588),1)
  CC_CHECK_CFLAGS += -DTARGET_RK3588
  CFLAGS += -DTARGET_RK3588
endif

# Check for texture fix option
ifeq ($(TEXTURE_FIX),1)
  CC_CHECK_CFLAGS += -DTEXTURE_FIX
  CFLAGS += -DTEXTURE_FIX
endif

# Check for enhance level textures option
ifeq ($(ENHANCE_LEVEL_TEXTURES),1)
  CC_CHECK_CFLAGS += -DENHANCE_LEVEL_TEXTURES
  CFLAGS += -DENHANCE_LEVEL_TEXTURES
endif

# Check for handheld option
ifeq ($(HANDHELD),1)
  CC_CHECK_CFLAGS += -DHANDHELD
  CFLAGS += -DHANDHELD
endif

# Check for no bzero/bcopy workaround option
ifeq ($(NO_BZERO_BCOPY),1)
  CC_CHECK_CFLAGS += -DNO_BZERO_BCOPY
  CFLAGS += -DNO_BZERO_BCOPY
endif

# Use internal ldiv()/lldiv()
ifeq ($(NO_LDIV),1)
  CC_CHECK_CFLAGS += -DNO_LDIV
  CFLAGS += -DNO_LDIV
endif

# Use OpenGL 1.3
ifeq ($(LEGACY_GL),1)
  CC_CHECK_CFLAGS += -DLEGACY_GL
  CFLAGS += -DLEGACY_GL
endif

#==============================================================================#
# Miscellaneous Tools                                                          #
#==============================================================================#

# N64 tools
MIO0TOOL              := $(TOOLS_DIR)/mio0
N64CKSUM              := $(TOOLS_DIR)/n64cksum
N64GRAPHICS           := $(TOOLS_DIR)/n64graphics
N64GRAPHICS_CI        := $(TOOLS_DIR)/n64graphics_ci
TEXTCONV              := $(TOOLS_DIR)/textconv
AIFF_EXTRACT_CODEBOOK := $(TOOLS_DIR)/aiff_extract_codebook
VADPCM_ENC            := $(TOOLS_DIR)/vadpcm_enc
EXTRACT_DATA_FOR_MIO  := $(TOOLS_DIR)/extract_data_for_mio
SKYCONV               := $(TOOLS_DIR)/skyconv

# Use the system installed armips if available. Otherwise use the one provided with this repository.
ifneq (,$(call find-command,armips))
  RSPASM              := armips
else
  RSPASM              := $(TOOLS_DIR)/armips
endif
ENDIAN_BITWIDTH       := $(BUILD_DIR)/endian-and-bitwidth
EMULATOR = mupen64plus
EMU_FLAGS = --noosd
LOADER = loader64
LOADER_FLAGS = -vwf
SHA1SUM = sha1sum
PRINT = printf

ifeq ($(COLOR),1)
  NO_COL  := \033[0m
  RED     := \033[0;31m
  GREEN   := \033[0;32m
  BLUE    := \033[0;34m
  YELLOW  := \033[0;33m
  BLINK   := \033[33;5m
endif

# Use Objcopy instead of extract_data_for_mio
ifeq ($(COMPILER),gcc)
  EXTRACT_DATA_FOR_MIO := $(OBJCOPY) -O binary --only-section=.data
endif

# Common build print status function
define print
  @$(PRINT) "$(GREEN)$(1) $(YELLOW)$(2)$(GREEN) -> $(BLUE)$(3)$(NO_COL)\n"
endef

#==============================================================================#
# Main Targets                                                                 #
#==============================================================================#

#all: $(ROM)
all: $(EXE)

ifeq ($(WINDOWS_BUILD),1)
MAPFILE = $(BUILD_DIR)/coop.map
exemap: $(EXE)
	@$(PRINT) "$(GREEN)Creating map file: $(BLUE)$(MAPFILE) $(NO_COL)\n"
	$(V)$(OBJDUMP) -t $(EXE) > $(MAPFILE)
	@cp $(EXE) $(EXE).bak && cp $(MAPFILE) $(MAPFILE).bak
	$(V)$(PYTHON) $(TOOLS_DIR)/clean_mapfile.py $(EXE) $(MAPFILE)
ifeq ($(IS_DEV_OR_DEBUG),0)
	$(V)$(OBJCOPY) -p --strip-unneeded $(EXE)
endif
all: exemap
endif

clean:
	$(RM) -r $(BUILD_DIR_BASE)

cleantools:
	$(MAKE) -s -C $(TOOLS_DIR) clean

distclean: clean cleantools
	$(PYTHON) extract_assets.py --clean

test: $(ROM)
	$(EMULATOR) $(EMU_FLAGS) $<

load: $(ROM)
	$(LOADER) $(LOADER_FLAGS) $<

libultra: $(BUILD_DIR)/libultra.a

$(BUILD_DIR)/$(RPC_LIBS):
	@$(CP) -f $(RPC_LIBS) $(BUILD_DIR)

$(BUILD_DIR)/$(DISCORD_SDK_LIBS):
	@$(CP) -f $(DISCORD_SDK_LIBS) $(BUILD_DIR)

$(BUILD_DIR)/$(COOPNET_LIBS):
	@$(CP) -f $(COOPNET_LIBS) $(BUILD_DIR)

$(BUILD_DIR)/$(LANG_DIR):
	@$(CP) -f -r $(LANG_DIR) $(BUILD_DIR)

$(BUILD_DIR)/$(MOD_DIR):
	$(CP) -f -r $(MOD_DIR) $(BUILD_DIR)

$(BUILD_DIR)/$(PALETTES_DIR):
	@$(CP) -f -r $(PALETTES_DIR) $(BUILD_DIR)

# Extra object file dependencies

ifeq ($(TARGET_N64),1)
	$(BUILD_DIR)/asm/boot.o:              $(IPL3_RAW_FILES)
	$(BUILD_DIR)/src/game/crash_screen.o: $(CRASH_TEXTURE_C_FILES)
	$(BUILD_DIR)/lib/rsp.o:               $(BUILD_DIR)/rsp/rspboot.bin $(BUILD_DIR)/rsp/fast3d.bin $(BUILD_DIR)/rsp/audio.bin
endif

$(BUILD_DIR)/src/game/characters.o:   $(SOUND_SAMPLE_TABLES)
$(SOUND_BIN_DIR)/sound_data.o:        $(SOUND_BIN_DIR)/sound_data.ctl.inc.c $(SOUND_BIN_DIR)/sound_data.tbl.inc.c $(SOUND_BIN_DIR)/sequences.bin.inc.c $(SOUND_BIN_DIR)/bank_sets.inc.c
$(BUILD_DIR)/levels/scripts.o:        $(BUILD_DIR)/include/level_headers.h

ifeq ($(VERSION),sh)
  $(BUILD_DIR)/src/audio/load.o: $(SOUND_BIN_DIR)/bank_sets.inc.c $(SOUND_BIN_DIR)/sequences_header.inc.c $(SOUND_BIN_DIR)/ctl_header.inc.c $(SOUND_BIN_DIR)/tbl_header.inc.c
endif

$(CRASH_TEXTURE_C_FILES): TEXTURE_ENCODING := u32

ifeq ($(COMPILER),gcc)
  $(BUILD_DIR)/lib/src/math/%.o: CFLAGS += -fno-builtin
endif

ifeq ($(VERSION),eu)
  TEXT_DIRS := text/de text/us text/fr

  # EU encoded text inserted into individual segment 0x19 files,
  # and course data also duplicated in leveldata.c
  $(BUILD_DIR)/bin/eu/translation_en.o: $(BUILD_DIR)/text/us/define_text.inc.c
  $(BUILD_DIR)/bin/eu/translation_de.o: $(BUILD_DIR)/text/de/define_text.inc.c
  $(BUILD_DIR)/bin/eu/translation_fr.o: $(BUILD_DIR)/text/fr/define_text.inc.c
  $(BUILD_DIR)/levels/menu/leveldata.o: $(BUILD_DIR)/text/us/define_courses.inc.c
  $(BUILD_DIR)/levels/menu/leveldata.o: $(BUILD_DIR)/text/de/define_courses.inc.c
  $(BUILD_DIR)/levels/menu/leveldata.o: $(BUILD_DIR)/text/fr/define_courses.inc.c
  $(BUILD_DIR)/src/game/level_info.o: $(BUILD_DIR)/text/us/define_courses.inc.c
  $(BUILD_DIR)/src/game/level_info.o: $(BUILD_DIR)/text/de/define_courses.inc.c
  $(BUILD_DIR)/src/game/level_info.o: $(BUILD_DIR)/text/fr/define_courses.inc.c

  O_FILES += $(BUILD_DIR)/bin/eu/translation_en.o $(BUILD_DIR)/bin/eu/translation_de.o $(BUILD_DIR)/bin/eu/translation_fr.o
else
  ifeq ($(VERSION),sh)
    TEXT_DIRS := text/jp
    $(BUILD_DIR)/bin/segment2.o: $(BUILD_DIR)/text/jp/define_text.inc.c
  else
    TEXT_DIRS := text/$(VERSION)
    # non-EU encoded text inserted into segment 0x02
    $(BUILD_DIR)/bin/segment2.o: $(BUILD_DIR)/text/$(VERSION)/define_text.inc.c
  endif
endif

ALL_DIRS := $(BUILD_DIR) $(addprefix $(BUILD_DIR)/,$(SRC_DIRS) $(GODDARD_SRC_DIRS) $(ULTRA_SRC_DIRS) $(ULTRA_BIN_DIRS) $(BIN_DIRS) $(TEXTURE_DIRS) $(TEXT_DIRS) $(SOUND_SAMPLE_DIRS) $(addprefix levels/,$(LEVEL_DIRS)) rsp include) $(MIO0_DIR) $(addprefix $(MIO0_DIR)/,$(VERSION)) $(SOUND_BIN_DIR) $(SOUND_BIN_DIR)/sequences/$(VERSION)

# Make sure build directory exists before compiling anything
DUMMY != mkdir -p $(ALL_DIRS)

#==============================================================================#
# Texture Generation                                                           #
#==============================================================================#
TEXTURE_ENCODING := u8

# Convert PNGs to RGBA32, RGBA16, IA16, IA8, IA4, IA1, I8, I4 binary files
$(BUILD_DIR)/%: %.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS) -s raw -i $@ -g $< -f $(lastword $(subst ., ,$@))

$(BUILD_DIR)/%.inc.c: %.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS) -s $(TEXTURE_ENCODING) -i $@ -g $< -f $(lastword ,$(subst ., ,$(basename $<)))

# Color Index CI8
$(BUILD_DIR)/%.ci8: %.ci8.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS_CI) -i $@ -g $< -f ci8

# Color Index CI4
$(BUILD_DIR)/%.ci4: %.ci4.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS_CI) -i $@ -g $< -f ci4

#==============================================================================#
# Compressed Segment Generation                                                #
#==============================================================================#

ifeq ($(TARGET_N64),1)

# Link segment file to resolve external labels
# TODO: ideally this would be `-Trodata-segment=0x07000000` but that doesn't set the address
$(BUILD_DIR)/%.elf: $(BUILD_DIR)/%.o
	$(call print,Linking ELF file:,$<,$@)
	$(V)$(LD) $(PROF_FLAGS) -e 0 -Ttext=$(SEGMENT_ADDRESS) -Map $@.map -o $@ $<

# Override for leveldata.elf, which otherwise matches the above pattern
.SECONDEXPANSION:
$(BUILD_DIR)/levels/%/leveldata.elf: $(BUILD_DIR)/levels/%/leveldata.o $(BUILD_DIR)/bin/$$(TEXTURE_BIN).elf
	$(call print,Linking ELF file:,$<,$@)
	$(V)$(LD) $(PROF_FLAGS) -e 0 -Ttext=$(SEGMENT_ADDRESS) -Map $@.map --just-symbols=$(BUILD_DIR)/bin/$(TEXTURE_BIN).elf -o $@ $<

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(call print,Extracting compressionable data from:,$<,$@)
	$(V)$(EXTRACT_DATA_FOR_MIO) $< $@

$(BUILD_DIR)/levels/%/leveldata.bin: $(BUILD_DIR)/levels/%/leveldata.elf
	$(call print,Extracting compressionable data from:,$<,$@)
	$(V)$(EXTRACT_DATA_FOR_MIO) $< $@

# Compress binary file
$(BUILD_DIR)/%.mio0: $(BUILD_DIR)/%.bin
	$(call print,Compressing:,$<,$@)
	$(V)$(MIO0TOOL) $< $@

# convert binary mio0 to object file
$(BUILD_DIR)/%.mio0.o: $(BUILD_DIR)/%.mio0
	$(call print,Converting MIO0 to ELF:,$<,$@)
	$(V)printf ".section .data\n\n.incbin \"$<\"\n" | $(AS) $(ASFLAGS) -o $@

endif


#==============================================================================#
# Sound File Generation                                                        #
#==============================================================================#

$(BUILD_DIR)/%.table: %.aiff
	$(call print,Extracting codebook:,$<,$@)
	$(V)$(AIFF_EXTRACT_CODEBOOK) $< >$@
	$(call print,Piping:,$<,$@.inc.c)

$(BUILD_DIR)/%.aifc: $(BUILD_DIR)/%.table %.aiff
	$(call print,Encoding VADPCM:,$<,$@)
	$(V)$(VADPCM_ENC) -c $^ $@

$(ENDIAN_BITWIDTH): $(TOOLS_DIR)/determine-endian-bitwidth.c
	@$(PRINT) "$(GREEN)Generating endian-bitwidth $(NO_COL)\n"
	$(V)$(CC) $(PROF_FLAGS) -c $(CFLAGS) -o $@.dummy2 $< 2>$@.dummy1; true
	$(V)grep -o 'msgbegin --endian .* --bitwidth .* msgend' $@.dummy1 > $@.dummy2
	$(V)head -n1 <$@.dummy2 | cut -d' ' -f2-5 > $@
	@$(RM) $@.dummy1
	@$(RM) $@.dummy2

$(SOUND_BIN_DIR)/sound_data.tbl: sound/sound_data_compressed.tbl
	@$(PRINT) "$(GREEN)Decompressing:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(PYTHON) $(TOOLS_DIR)/decompress.py sound/sound_data_compressed.tbl $(SOUND_BIN_DIR)/sound_data.tbl

$(SOUND_BIN_DIR)/sound_data.ctl: sound/sound_data_compressed.ctl
	@$(PRINT) "$(GREEN)Decompressing:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(PYTHON) $(TOOLS_DIR)/decompress.py sound/sound_data_compressed.ctl $(SOUND_BIN_DIR)/sound_data.ctl

$(SOUND_BIN_DIR)/bank_sets: sound/bank_sets_compressed
	@$(PRINT) "$(GREEN)Decompressing:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(PYTHON) $(TOOLS_DIR)/decompress.py sound/bank_sets_compressed $(SOUND_BIN_DIR)/bank_sets

$(SOUND_BIN_DIR)/ctl_header: $(SOUND_BIN_DIR)/sound_data.ctl
	@true

$(SOUND_BIN_DIR)/tbl_header: $(SOUND_BIN_DIR)/sound_data.ctl
	@true

$(SOUND_BIN_DIR)/sequences.bin:
	@$(PRINT) "$(GREEN)Decompressing:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(PYTHON) $(TOOLS_DIR)/decompress.py sound/sequences_compressed.bin $(SOUND_BIN_DIR)/sequences.bin

$(SOUND_BIN_DIR)/sequences_header: $(SOUND_BIN_DIR)/sequences.bin
	@true

$(SOUND_BIN_DIR)/%.m64: $(SOUND_BIN_DIR)/%.o
	$(call print,Converting to M64:,$<,$@)
	$(V)$(OBJCOPY) -j .rodata $< -O binary $@


#==============================================================================#
# Generated Source Code Files                                                  #
#==============================================================================#

# Convert binary file to a comma-separated list of byte values for inclusion in C code
$(BUILD_DIR)/%.inc.c: $(BUILD_DIR)/%
	$(call print,Piping:,$<,$@)
	$(V)hexdump -v -e '1/1 "0x%X,"' $< > $@
	$(V)echo >> $@

# Generate animation data
$(BUILD_DIR)/assets/mario_anim_data.c: $(wildcard assets/anims/*.inc.c)
	@$(PRINT) "$(GREEN)Generating animation data $(NO_COL)\n"
	$(V)$(PYTHON) $(TOOLS_DIR)/mario_anims_converter.py > $@

# Generate demo input data
$(BUILD_DIR)/assets/demo_data.c: assets/demo_data.json $(wildcard assets/demos/*.bin)
	@$(PRINT) "$(GREEN)Generating demo data $(NO_COL)\n"
	$(V)$(PYTHON) $(TOOLS_DIR)/demo_data_converter.py assets/demo_data.json $(DEF_INC_CFLAGS) > $@

# Encode in-game text strings
$(BUILD_DIR)/text/%/define_courses.inc.c: text/define_courses.inc.c text/%/courses.h
	@$(PRINT) "$(GREEN)Preprocessing: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(CPP) $(PROF_FLAGS) $(CPPFLAGS) $< -o - -I text/$*/ | $(TEXTCONV) charmap.txt - $@
$(BUILD_DIR)/text/%/define_text.inc.c: text/define_text.inc.c text/%/courses.h text/%/dialogs.h
	@$(PRINT) "$(GREEN)Preprocessing: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(CPP) $(PROF_FLAGS) $(CPPFLAGS) $< -o - -I text/$*/ | $(TEXTCONV) charmap.txt - $@

# Level headers
$(BUILD_DIR)/include/level_headers.h: levels/level_headers.h.in
	$(call print,Preprocessing level headers:,$<,$@)
	$(V)$(CPP) $(PROF_FLAGS) $(CPPFLAGS) -I . levels/level_headers.h.in | $(PYTHON) $(TOOLS_DIR)/output_level_headers.py > $(BUILD_DIR)/include/level_headers.h

# Run asm_processor on files that have NON_MATCHING code
ifeq ($(NON_MATCHING),0)
$(GLOBAL_ASM_O_FILES): CC := $(V)$(PYTHON) $(TOOLS_DIR)/asm_processor/build.py $(CC) -- $(AS) $(ASFLAGS) --
endif

# Rebuild files with 'GLOBAL_ASM' if the NON_MATCHING flag changes.
$(GLOBAL_ASM_O_FILES): $(GLOBAL_ASM_DEP).$(NON_MATCHING)
$(GLOBAL_ASM_DEP).$(NON_MATCHING):
	@$(RM) $(GLOBAL_ASM_DEP).*
	$(V)touch $@


#==============================================================================#
# Compilation Recipes                                                          #
#==============================================================================#

# Compile C++ code
$(BUILD_DIR)/%.o: %.cpp
	$(call print,Compiling:,$<,$@)
	$(V)$(CXX) $(PROF_FLAGS) -fsyntax-only $(EXTRA_CPP_FLAGS) $(EXTRA_CPP_INCLUDES) $(CFLAGS) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(V)$(CXX) $(PROF_FLAGS) -c $(EXTRA_CPP_FLAGS) $(EXTRA_CPP_INCLUDES) $(CFLAGS) -o $@ $<

# Compile C code
$(BUILD_DIR)/%.o: %.c
	$(call print,Compiling:,$<,$@)
	$(V)$(CC_CHECK) $(PROF_FLAGS) $(CC_CHECK_CFLAGS) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(V)$(CC) $(PROF_FLAGS) -c $(CFLAGS) -o $@ $<
$(BUILD_DIR)/%.o: $(BUILD_DIR)/%.c
	$(call print,Compiling:,$<,$@)
	$(V)$(CC_CHECK) $(PROF_FLAGS) $(CC_CHECK_CFLAGS) -MMD -MP -MT $@ -MF $(BUILD_DIR)/$*.d $<
	$(V)$(CC) $(PROF_FLAGS) -c $(CFLAGS) -o $@ $<

# Alternate compiler flags needed for matching
ifeq ($(COMPILER),ido)
  $(BUILD_DIR)/levels/%/leveldata.o: OPT_FLAGS := -g
  $(BUILD_DIR)/actors/%.o:           OPT_FLAGS := -g
  $(BUILD_DIR)/bin/%.o:              OPT_FLAGS := -g
  $(BUILD_DIR)/src/goddard/%.o:      OPT_FLAGS := -g
  $(BUILD_DIR)/src/goddard/%.o:      MIPSISET := -mips1
  $(BUILD_DIR)/lib/src/%.o:          OPT_FLAGS :=
  $(BUILD_DIR)/lib/src/math/%.o:     OPT_FLAGS := -O2
  $(BUILD_DIR)/lib/src/math/ll%.o:   OPT_FLAGS :=
  $(BUILD_DIR)/lib/src/math/ll%.o:   MIPSISET := -mips3 -32
  $(BUILD_DIR)/lib/src/ldiv.o:       OPT_FLAGS := -O2
  $(BUILD_DIR)/lib/src/string.o:     OPT_FLAGS := -O2
  $(BUILD_DIR)/lib/src/gu%.o:        OPT_FLAGS := -O3
  $(BUILD_DIR)/lib/src/al%.o:        OPT_FLAGS := -O3
  # For the asm-processor, since it doesn't support -O3. Probably not actually compiled with these flags.
  ifeq ($(VERSION),sh)
    $(BUILD_DIR)/lib/src/unk_shindou_file.o: OPT_FLAGS := -O1
    $(BUILD_DIR)/lib/src/func_sh_80304D20.o: OPT_FLAGS := -O1
    $(BUILD_DIR)/lib/src/_Printf.o: OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/contramread.o: OPT_FLAGS := -O1
    $(BUILD_DIR)/lib/src/osPfsIsPlug.o: OPT_FLAGS := -O1
    $(BUILD_DIR)/lib/src/osAiSetFrequency.o: OPT_FLAGS := -O1
    $(BUILD_DIR)/lib/src/contramwrite.o: OPT_FLAGS := -O1
    $(BUILD_DIR)/lib/src/sprintf.o: OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/_Litob.o: OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/_Ldtob.o: OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/osDriveRomInit.o: OPT_FLAGS := -g
  endif
  ifeq ($(VERSION),eu)
    $(BUILD_DIR)/lib/src/_Litob.o:   OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/_Ldtob.o:   OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/_Printf.o:  OPT_FLAGS := -O3
    $(BUILD_DIR)/lib/src/sprintf.o:  OPT_FLAGS := -O3

    # Enable loop unrolling except for external.c (external.c might also have used
    # unrolling, but it makes one loop harder to match).
    # For all audio files other than external.c and port_eu.c, put string literals
    # in .data. (In Shindou, the port_eu.c string literals also moved to .data.)
    $(BUILD_DIR)/src/audio/%.o:        OPT_FLAGS := -O2 -use_readwrite_const
    $(BUILD_DIR)/src/audio/port_eu.o:  OPT_FLAGS := -O2
    $(BUILD_DIR)/src/audio/external.o: OPT_FLAGS := -O2 -Wo,-loopunroll,0
  endif
  ifeq ($(VERSION_JP_US),true)
    $(BUILD_DIR)/src/audio/%.o:        OPT_FLAGS := -O2 -Wo,-loopunroll,0
    $(BUILD_DIR)/src/audio/load.o:     OPT_FLAGS := -O2 -framepointer -Wo,-loopunroll,0
  endif
  ifeq ($(VERSION_JP_US),true)
    # The source-to-source optimizer copt is enabled for audio. This makes it use
    # acpp, which needs -Wp,-+ to handle C++-style comments.
    # All other files than external.c should really use copt, but only a few have
    # been matched so far.
    $(BUILD_DIR)/src/audio/effects.o:   OPT_FLAGS := -O2 -Wo,-loopunroll,0 -sopt,-inline=sequence_channel_process_sound,-scalaroptimize=1 -Wp,-+
    $(BUILD_DIR)/src/audio/synthesis.o: OPT_FLAGS := -O2 -sopt,-scalaroptimize=1 -Wp,-+
  endif

# Add a target for build/eu/src/audio/*.copt to make it easier to see debug
$(BUILD_DIR)/src/audio/%.acpp: src/audio/%.c
	$(ACPP) $(TARGET_CFLAGS) $(DEF_INC_CFLAGS) -D__sgi -+ $< > $@
$(BUILD_DIR)/src/audio/%.copt: $(BUILD_DIR)/src/audio/%.acpp
	$(COPT) -signed -I=$< -CMP=$@ -cp=i -scalaroptimize=1 $(COPTFLAGS)
$(BUILD_DIR)/src/audio/seqplayer.copt: COPTFLAGS := -inline_manual

endif

# Run linker script through the C preprocessor
$(BUILD_DIR)/$(LD_SCRIPT): $(LD_SCRIPT)
	$(call print,Preprocessing linker script:,$<,$@)
	$(V)$(CPP) $(PROF_FLAGS) $(CPPFLAGS) -DBUILD_DIR=$(BUILD_DIR) -MMD -MP -MT $@ -MF $@.d -o $@ $<

# Assemble assembly code
$(BUILD_DIR)/%.o: %.s
	$(call print,Assembling:,$<,$@)
	$(V)$(AS) $(ASFLAGS) -MD $(BUILD_DIR)/$*.d -o $@ $<

ifeq ($(TARGET_N64),1)
  # Assemble RSP assembly code
  $(BUILD_DIR)/rsp/%.bin $(BUILD_DIR)/rsp/%_data.bin: rsp/%.s
	$(call print,Assembling:,$<,$@)
	$(V)$(RSPASM) -sym $@.sym $(RSPASMFLAGS) -strequ CODE_FILE $(BUILD_DIR)/rsp/$*.bin -strequ DATA_FILE $(BUILD_DIR)/rsp/$*_data.bin $<

  # Link libultra
  $(BUILD_DIR)/libultra.a: $(ULTRA_O_FILES)
	@$(PRINT) "$(GREEN)Linking libultra:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(AR) rcs -o $@ $(ULTRA_O_FILES)
	$(V)$(TOOLS_DIR)/patch_libultra_math $@

  # Link libgoddard
  $(BUILD_DIR)/libgoddard.a: $(GODDARD_O_FILES)
	@$(PRINT) "$(GREEN)Linking libgoddard:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(AR) rcs -o $@ $(GODDARD_O_FILES)

  # Link SM64 ELF file
  $(ELF): $(O_FILES) $(MIO0_OBJ_FILES) $(SEG_FILES) $(BUILD_DIR)/$(LD_SCRIPT) undefined_syms.txt $(BUILD_DIR)/libultra.a $(BUILD_DIR)/libgoddard.a
	@$(PRINT) "$(GREEN)Linking ELF file:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(LD) $(PROF_FLAGS) -L $(BUILD_DIR) -T undefined_syms.txt -T $(BUILD_DIR)/$(LD_SCRIPT) -Map $(BUILD_DIR)/sm64.$(VERSION).map --no-check-sections $(addprefix -R ,$(SEG_FILES)) -o $@ $(O_FILES) -lultra -lgoddard

  # Build ROM
  $(ROM): $(ELF)
	$(call print,Building ROM:,$<,$@)
	$(V)$(OBJCOPY) --pad-to=0x800000 --gap-fill=0xFF $< $(@:.z64=.bin) -O binary
	$(V)$(N64CKSUM) $(@:.z64=.bin) $@

  $(BUILD_DIR)/$(TARGET).objdump: $(ELF)
	$(OBJDUMP) -D $< > $@
else
  $(EXE): $(O_FILES) $(MIO0_FILES:.mio0=.o) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(BUILD_DIR)/$(RPC_LIBS) $(BUILD_DIR)/$(DISCORD_SDK_LIBS) $(BUILD_DIR)/$(COOPNET_LIBS) $(BUILD_DIR)/$(LANG_DIR) $(BUILD_DIR)/$(MOD_DIR) $(BUILD_DIR)/$(PALETTES_DIR)
	@$(PRINT) "$(GREEN)Linking executable: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(LD) $(PROF_FLAGS) -L $(BUILD_DIR) -o $@ $(O_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)
endif

.PHONY: all clean distclean default diff test load libultra res
.PRECIOUS: $(BUILD_DIR)/bin/%.elf $(SOUND_BIN_DIR)/%.ctl $(SOUND_BIN_DIR)/%.tbl $(SOUND_SAMPLE_TABLES) $(SOUND_BIN_DIR)/%.s $(BUILD_DIR)/%
# with no prerequisites, .SECONDARY causes no intermediate target to be removed
.SECONDARY:

APP_DIR = ./sm64coopdx.app
APP_CONTENTS_DIR = $(APP_DIR)/Contents
APP_MACOS_DIR = $(APP_CONTENTS_DIR)/MacOS
APP_RESOURCES_DIR = $(APP_CONTENTS_DIR)/Resources


ifeq ($(OSX_BUILD),1)
  GLEW_LIB := $(shell find $(BREW_PREFIX)/Cellar/glew | grep libGLEW.2.2.0 | sort -n | uniq)
  SDL2_LIB := $(shell find $(BREW_PREFIX)/Cellar/sdl2 | grep libSDL2- | sort -n | uniq)
endif

all:
	@if [ "$(USE_APP)" = "0" ]; then \
		rm -rf build/us_pc/sm64coopdx.app; \
  else \
		$(PRINT) "$(GREEN)Creating App Bundle: $(BLUE)build/us_pc/sm64coopdx.app\n"; \
		rm -rf $(APP_DIR); \
		rm -rf build/us_pc/sm64coopdx.app; \
		mkdir -p $(APP_MACOS_DIR); \
		mkdir -p $(APP_RESOURCES_DIR); \
		mv build/us_pc/sm64coopdx $(APP_MACOS_DIR)/sm64coopdx; \
    cp -r build/us_pc/mods $(APP_RESOURCES_DIR); \
    cp -r build/us_pc/lang $(APP_RESOURCES_DIR); \
    cp -r build/us_pc/dynos $(APP_RESOURCES_DIR); \
    cp -r build/us_pc/palettes $(APP_RESOURCES_DIR); \
		cp build/us_pc/discord_game_sdk.dylib $(APP_MACOS_DIR); \
    cp build/us_pc/libdiscord_game_sdk.dylib $(APP_MACOS_DIR); \
    cp build/us_pc/libcoopnet.dylib $(APP_MACOS_DIR); \
    cp build/us_pc/libjuice.1.2.2.dylib $(APP_MACOS_DIR); \
    cp $(SDL2_LIB) $(APP_MACOS_DIR)/libSDL2.dylib; \
    install_name_tool -change $(BREW_PREFIX)/opt/sdl2/lib/libSDL2-2.0.0.dylib @executable_path/libSDL2.dylib $(APP_MACOS_DIR)/sm64coopdx; > /dev/null 2>&1 \
		install_name_tool -id @executable_path/libSDL2.dylib $(APP_MACOS_DIR)/libSDL2.dylib; > /dev/null 2>&1 \
    codesign --force --deep --sign - $(APP_MACOS_DIR)/libSDL2.dylib; \
    cp $(GLEW_LIB) $(APP_MACOS_DIR)/libGLEW.dylib; \
    install_name_tool -change $(BREW_PREFIX)/opt/glew/lib/libGLEW.2.2.dylib @executable_path/libGLEW.dylib $(APP_MACOS_DIR)/sm64coopdx; > /dev/null 2>&1 \
		install_name_tool -id @executable_path/libGLEW.dylib $(APP_MACOS_DIR)/libGLEW.dylib; > /dev/null 2>&1 \
    codesign --force --deep --sign - $(APP_MACOS_DIR)/libGLEW.dylib; \
		cp res/icon.icns $(APP_RESOURCES_DIR)/icon.icns; \
		echo "APPL????" > $(APP_CONTENTS_DIR)/PkgInfo; \
		echo '<?xml version="1.0" encoding="UTF-8"?>' > $(APP_CONTENTS_DIR)/Info.plist; \
		echo '<!DOCTYPE plist PUBLIC "-//Apple Computer//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '<plist version="1.0">' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '<dict>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <key>CFBundleExecutable</key>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <string>sm64coopdx</string>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <key>CFBundleIconFile</key>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <string>icon</string>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <key>CFBundleIconName</key>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <string>AppIcon</string>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <key>CFBundleDisplayName</key>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <string>sm64coopdx</string>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <!-- Add other keys and values here -->' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '</dict>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '</plist>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		chmod +x $(APP_MACOS_DIR)/sm64coopdx; \
		mv $(APP_DIR) build/us_pc/; \
  fi

# Remove built-in rules, to improve performance
MAKEFLAGS += --no-builtin-rules

-include $(DEP_FILES)

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
