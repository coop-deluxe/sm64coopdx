# Makefile to rebuild SM64 split image

include util.mk

# Default target
default: all

# Preprocessor definitions
DEFINES :=

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

# Makeflag to enable OSX fixes
OSX_BUILD ?= 0

# Specify the target you are building for, TARGET_BITS=0 means native
TARGET_ARCH ?= native
TARGET_BITS ?= 0

# Enable immediate load by default
IMMEDIATELOAD ?= 1
# Enable better camera by default
BETTERCAMERA ?= 1
# Enable no drawing distance by default
NODRAWINGDISTANCE ?= 1
# Disable texture fixes by default (helps with them purists)
TEXTURE_FIX ?= 0
# Enable extended options menu by default
EXT_OPTIONS_MENU ?= 1
# Disable text-based save-files by default
TEXTSAVES ?= 0
# Load resources from external files
EXTERNAL_DATA ?= 0
# Enable Discord Game SDK (used for Discord invites)
DISCORD_SDK ?= 1
# Enable CoopNet SDK (used for CoopNet server hosting)
COOPNET ?= 1
# Enable docker build workarounds
DOCKERBUILD ?= 0
# Sets your optimization level for building.
# A choose is chosen by default for you.
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
# Use .app (mac only)
USE_APP ?= 1
# Various workarounds for weird toolchains

NO_BZERO_BCOPY ?= 0
NO_LDIV ?= 0

# Backend selection

# Renderers: GL, GL_LEGACY, D3D11, D3D12, DUMMY
RENDER_API ?= GL
# Window managers: SDL1, SDL2, DXGI (forced if D3D11 or D3D12 in RENDER_API), DUMMY (forced if RENDER_API is DUMMY)
WINDOW_API ?= SDL2
# Audio backends: SDL1, SDL2, DUMMY
AUDIO_API ?= SDL2
# Controller backends (can have multiple, space separated): SDL2, SDL1
CONTROLLER_API ?= SDL2

# Misc settings for EXTERNAL_DATA

BASEDIR ?= res
BASEPACK ?= base.zip

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
$(eval $(call validate-option,VERSION,jp us eu sh))

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
# Level 1 produces minimal information, enough for making backtraces in parts of the program that you don’t plan to debug. This includes descriptions of functions and external variables, and line number tables, but no information about local variables.
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
	machine = $(shell sh -c 'uname -m 2>/dev/null || echo unknown')

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

# Set BITS (32/64) to compile for
OPT_FLAGS += $(BITS)

TARGET := sm64.$(VERSION)

# Stuff for showing the git hash in the intro on nightly builds
# From https://stackoverflow.com/questions/44038428/include-git-commit-hash-and-or-branch-name-in-c-c-source
#ifeq ($(shell git rev-parse --abbrev-ref HEAD),nightly)
#  GIT_HASH=`git rev-parse --short HEAD`
#  COMPILE_TIME=`date -u +'%Y-%m-%d %H:%M:%S UTC'`
#  DEFINES += -DNIGHTLY -DGIT_HASH="\"$(GIT_HASH)\"" -DCOMPILE_TIME="\"$(COMPILE_TIME)\""
#endif


# GRUCODE - selects which RSP microcode to use.
#   f3d_old - default for JP and US versions
#   f3d_new - default for EU and Shindou versions
#   f3dex   -
#   f3dex2  -
#   f3dex2e -
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

ifeq ($(OSX_BUILD),1) # Modify GFX & SDL2 for OSX GL
     DEFINES += OSX_BUILD=1
endif

# Check backends

ifneq (,$(filter $(RENDER_API),D3D11 D3D12))
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
  COMPARE := 0
endif


# COMPARE - whether to verify the SHA-1 hash of the ROM after building
#   1 - verifies the SHA-1 hash of the selected version of the game
#   0 - does not verify the hash
COMPARE ?= 1
$(eval $(call validate-option,COMPARE,0 1))

ifeq ($(OSX_BUILD),0)
	USE_APP := 0
endif

TARGET_STRING := sm64.$(VERSION).$(GRUCODE)
# If non-default settings were chosen, disable COMPARE
ifeq ($(filter $(TARGET_STRING), sm64.jp.f3d_old sm64.us.f3d_old sm64.eu.f3d_new sm64.sh.f3d_new),)
  COMPARE := 0
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
  $(info Target:         $(TARGET))
  ifeq ($(COMPARE),1)
    $(info Compare ROM:    yes)
  else
    $(info Compare ROM:    no)
  endif
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

  # Make sure assets exist
  NOEXTRACT ?= 0
  ifeq ($(NOEXTRACT),0)
    DUMMY != $(PYTHON) extract_assets.py $(VERSION) >&2 || echo FAIL
    ifeq ($(DUMMY),FAIL)
      $(error Failed to extract assets)
    endif
  endif

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

# Luigi and wario sounds don't work on 32-bit right now
# And the audio code is so terrible I don't care enough to figure it out at the moment
ifeq ($(TARGET_BITS), 32)
  _ := $(shell rm -rf sound/samples/sfx_custom_luigi/*.aiff)
  _ := $(shell rm -rf sound/samples/sfx_custom_luigi_peach/*.aiff)
  _ := $(shell rm -rf sound/samples/sfx_custom_wario/*.aiff)
  _ := $(shell rm -rf sound/samples/sfx_custom_wario_peach/*.aiff)

# Copy missing character sounds from mario sound banks
_ := $(shell $(PYTHON) $(TOOLS_DIR)/copy_mario_sounds.py)

endif

# Copy missing instrument samples from the music sound banks
_ := $(shell $(PYTHON) $(TOOLS_DIR)/copy_extended_sounds.py)

#==============================================================================#
# Target Executable and Sources                                                #
#==============================================================================#

BUILD_DIR_BASE := build
# BUILD_DIR is the location where all build artifacts are placed
BUILD_DIR := $(BUILD_DIR_BASE)/$(VERSION)_pc

ifeq ($(WINDOWS_BUILD),1)
	EXE := $(BUILD_DIR)/$(TARGET_STRING).exe
else # Linux builds/binary namer
	ifeq ($(TARGET_RPI),1)
		EXE := $(BUILD_DIR)/$(TARGET_STRING).arm
	else
		EXE := $(BUILD_DIR)/$(TARGET_STRING)
	endif
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
SRC_DIRS := src src/engine src/game src/audio src/bass_audio src/menu src/buffers actors levels bin data assets asm lib sound
BIN_DIRS := bin bin/$(VERSION)

# PC files
SRC_DIRS += src/pc src/pc/gfx src/pc/audio src/pc/controller src/pc/fs src/pc/fs/packtypes src/pc/mods src/dev src/pc/network src/pc/network/packets src/pc/network/socket src/pc/network/coopnet src/pc/utils src/pc/utils/miniz src/pc/djui src/pc/lua src/pc/lua/utils src/pc/os

ifeq ($(DISCORD_SDK),1)
  SRC_DIRS += src/pc/discord
endif

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

ifeq ($(TARGET_N64),0)
  GENERATED_C_FILES += $(addprefix $(BUILD_DIR)/bin/,$(addsuffix _skybox.c,$(notdir $(basename $(wildcard textures/skyboxes/*.png)))))
endif

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
    DISCORD_SDK_LIBS := lib/discordsdk/discord_game_sdk.dylib lib/discordsdk/libdiscord_game_sdk.dylib
  else
    DISCORD_SDK_LIBS := lib/discordsdk/libdiscord_game_sdk.so
  endif
endif

BASS_LIBS :=
ifeq ($(WINDOWS_BUILD),1)
  ifeq ($(TARGET_BITS), 32)
    BASS_LIBS := lib/bass/x86/bass.dll lib/bass/x86/bass_fx.dll
  else
    BASS_LIBS := lib/bass/bass.dll lib/bass/bass_fx.dll
  endif
else ifeq ($(OSX_BUILD),1)
  # needs testing
  # HACKY! Instead of figuring out all of the dynamic library linking madness...
  # I copied the library and gave it two names.
  # This really shouldn't be required, but I got tired of trying to do it the "right way"
  BASS_LIBS := lib/bass/bass.dylib lib/bass/libbass.dylib lib/bass/bass_fx.dylib lib/bass/libbass_fx.dylib
else ifeq ($(TARGET_RPI),1)
	ifneq (,$(findstring aarch64,$(machine)))
    BASS_LIBS := lib/bass/arm/aarch64/libbass.so lib/bass/arm/aarch64/libbass_fx.so
  else
    BASS_LIBS := lib/bass/arm/libbass.so lib/bass/arm/libbass_fx.so
  endif
else
  BASS_LIBS := lib/bass/libbass.so lib/bass/libbass_fx.so
endif

LANG_DIR := lang

# Remove old lang dir
_ := $(shell rm -rf ./$(BUILD_DIR)/$(LANG_DIR))

MOD_DIR := mods

# Remove old mod dir
_ := $(shell rm -rf ./$(BUILD_DIR)/$(MOD_DIR))

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
	EXTRA_CFLAGS += -Wno-unused-result
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
  CPP := cpp-9 -P
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
  ifeq ($(RENDER_API),D3D12)
    BACKEND_CFLAGS += -Iinclude/dxsdk
  endif
  BACKEND_LDFLAGS += -ld3dcompiler -ldxgi -ldxguid
  BACKEND_LDFLAGS += -lsetupapi -ldinput8 -luser32 -lgdi32 -limm32 -lole32 -loleaut32 -lshell32 -lwinmm -lversion -luuid -static
else ifeq ($(findstring SDL,$(WINDOW_API)),SDL)
  ifeq ($(WINDOWS_BUILD),1)
    BACKEND_LDFLAGS += -lglew32 -lglu32 -lopengl32
  else ifeq ($(TARGET_RPI),1)
    BACKEND_LDFLAGS += -lGLESv2
  else ifeq ($(OSX_BUILD),1)
    BACKEND_LDFLAGS += -framework OpenGL `pkg-config --libs glew` -ld_classic
    EXTRA_CPP_FLAGS += -stdlib=libc++ -std=c++0x
  else
    BACKEND_LDFLAGS += -lGL
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
    BACKEND_LDFLAGS += `$(SDLCONFIG) --static-libs` -lsetupapi -luser32 -limm32 -lole32 -loleaut32 -lshell32 -lwinmm -lversion
  else
    BACKEND_LDFLAGS += `$(SDLCONFIG) --libs`
  endif
endif

C_DEFINES := $(foreach d,$(DEFINES),-D$(d))
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
  LDFLAGS := $(BITS) -march=$(TARGET_ARCH) -Llib -lpthread $(BACKEND_LDFLAGS) -static
  ifeq ($(CROSS),)
    LDFLAGS += -no-pie
  endif
  ifeq ($(WINDOWS_CONSOLE),1)
    LDFLAGS += -mconsole
  endif
else ifeq ($(TARGET_RPI),1)
  LDFLAGS := $(OPT_FLAGS) -lm $(BACKEND_LDFLAGS) -no-pie
else ifeq ($(OSX_BUILD),1)
  LDFLAGS := -lm $(BACKEND_LDFLAGS) -lpthread
else
  LDFLAGS := $(BITS) -march=$(TARGET_ARCH) -lm $(BACKEND_LDFLAGS) -no-pie -lpthread
endif

ifeq ($(WINDOWS_BUILD),0)
  LDFLAGS += -rdynamic
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

# Lua
ifeq ($(WINDOWS_BUILD),1)
  ifeq ($(TARGET_BITS), 32)
    LDFLAGS += -Llib/lua/win32 -l:liblua53.a
  else
    LDFLAGS += -Llib/lua/win64 -l:liblua53.a
  endif
else ifeq ($(OSX_BUILD),1)
  LDFLAGS += -L./lib/lua/mac/ -l lua53
else ifeq ($(TARGET_RPI),1)
	ifneq (,$(findstring aarch64,$(machine)))
    LDFLAGS += -Llib/lua/linux -l:liblua53-arm64.a
  else
    LDFLAGS += -Llib/lua/linux -l:liblua53-arm.a
  endif
else
  LDFLAGS += -Llib/lua/linux -l:liblua53.a -ldl
endif

# coopnet
COOPNET_LIBS :=
ifeq ($(COOPNET),1)
  ifeq ($(WINDOWS_BUILD),1)
    ifeq ($(TARGET_BITS), 32)
      LDFLAGS += -Llib/coopnet/win32 -l:libcoopnet.a -l:libjuice.a -lbcrypt -lws2_32 -liphlpapi
    else
      LDFLAGS += -Llib/coopnet/win64 -l:libcoopnet.a -l:libjuice.a -lbcrypt -lws2_32 -liphlpapi
    endif
  else ifeq ($(OSX_BUILD),1)
    LDFLAGS += -Wl,-rpath,@loader_path -L./lib/coopnet/mac/ -l coopnet
    COOPNET_LIBS += ./lib/coopnet/mac/libcoopnet.dylib
    COOPNET_LIBS += ./lib/coopnet/mac/libjuice.1.2.2.dylib
  else ifeq ($(TARGET_RPI),1)
    ifneq (,$(findstring aarch64,$(machine)))
      LDFLAGS += -Llib/coopnet/linux -l:libcoopnet-arm64.a -l:libjuice.a
    else
      LDFLAGS += -Llib/coopnet/linux -l:libcoopnet-arm.a -l:libjuice.a
    endif
  else
    LDFLAGS += -Llib/coopnet/linux -l:libcoopnet.a -l:libjuice.a
  endif
endif

# Network/Discord/Bass (ugh, needs cleanup)
ifeq ($(WINDOWS_BUILD),1)
  LDFLAGS += -L"ws2_32" -lwsock32
  ifeq ($(DISCORD_SDK),1)
    LDFLAGS += -Wl,-Bdynamic -L./lib/discordsdk/ -L./lib/bass/ -ldiscord_game_sdk -lbass -lbass_fx -Wl,-Bstatic
  else
    LDFLAGS += -Wl,-Bdynamic -L./lib/bass/ -lbass -lbass_fx -Wl,-Bstatic
  endif
else
  ifeq ($(DISCORD_SDK),1)
    LDFLAGS += -ldiscord_game_sdk -lbass -lbass_fx -Wl,-rpath . -Wl,-rpath lib/discordsdk -Wl,-rpath lib/bass
  else
    ifeq ($(TARGET_RPI),1)
      LDFLAGS += -lbass -lbass_fx -Wl,-rpath . -Wl,-rpath lib/bass/arm
    else
      LDFLAGS += -lbass -lbass_fx -Wl,-rpath . -Wl,-rpath lib/bass
    endif
  endif
endif

# Prevent a crash with -sopt
export LANG := C

#==============================================================================#
# Extra CC Flags                                                               #
#==============================================================================#

# Identify that this is a coop build so that one patch can be applied to EX
# and/or COOP. They can choose to ifdef entity synchronization out.
CC_CHECK_CFLAGS += -DCOOP
CFLAGS += -DCOOP

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

# Check for immediate load option
ifeq ($(IMMEDIATELOAD),1)
  CC_CHECK_CFLAGS += -DIMMEDIATELOAD
  CFLAGS += -DIMMEDIATELOAD
endif

# Check for docker build workaround option
ifeq ($(DOCKERBUILD),1)
  CC_CHECK_CFLAGS += -DDOCKERBUILD
  CFLAGS += -DDOCKERBUILD
endif

# Check for Puppycam option
ifeq ($(BETTERCAMERA),1)
  CC_CHECK_CFLAGS += -DBETTERCAMERA
  CFLAGS += -DBETTERCAMERA
  EXT_OPTIONS_MENU := 1
endif

#ifeq ($(TEXTSAVES),1)
#  CC_CHECK_CFLAGS += -DTEXTSAVES
#  CFLAGS += -DTEXTSAVES
#endif

# Check for no drawing distance option
#ifeq ($(NODRAWINGDISTANCE),1)
  CC_CHECK_CFLAGS += -DNODRAWINGDISTANCE
  CFLAGS += -DNODRAWINGDISTANCE
#endif

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

# Check for texture fix option
ifeq ($(TEXTURE_FIX),1)
  CC_CHECK_CFLAGS += -DTEXTURE_FIX
  CFLAGS += -DTEXTURE_FIX
endif

# Check for extended options menu option
ifeq ($(EXT_OPTIONS_MENU),1)
  CC_CHECK_CFLAGS += -DEXT_OPTIONS_MENU
  CFLAGS += -DEXT_OPTIONS_MENU
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

# Load external textures
ifeq ($(EXTERNAL_DATA),1)
  CC_CHECK_CFLAGS += -DEXTERNAL_DATA -DFS_BASEDIR="\"$(BASEDIR)\""
  CFLAGS += -DEXTERNAL_DATA -DFS_BASEDIR="\"$(BASEDIR)\""
  # tell skyconv to write names instead of actual texture data and save the split tiles so we can use them later
  SKYTILE_DIR := $(BUILD_DIR)/textures/skybox_tiles
  SKYCONV_ARGS := --store-names --write-tiles "$(SKYTILE_DIR)"
  $(shell mkdir -p $(SKYTILE_DIR))
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



ifeq ($(EXTERNAL_DATA),1)

BASEPACK_PATH := $(BUILD_DIR)/$(BASEDIR)/$(BASEPACK)
BASEPACK_LST := $(BUILD_DIR)/basepack.lst

# depend on resources as well
all: $(BASEPACK_PATH)

# phony target for building resources
res: $(BASEPACK_PATH)

# prepares the basepack.lst
$(BASEPACK_LST): $(EXE)
	@$(PRINT) "$(GREEN)Making basepack list.$(NO_COL)\n"
	@mkdir -p $(BUILD_DIR)/$(BASEDIR)
	@echo -n > $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/bank_sets sound/bank_sets" >> $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/sequences.bin sound/sequences.bin" >> $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/sound_data.ctl sound/sound_data.ctl" >> $(BASEPACK_LST)
	@echo "$(BUILD_DIR)/sound/sound_data.tbl sound/sound_data.tbl" >> $(BASEPACK_LST)
	@$(foreach f, $(wildcard $(SKYTILE_DIR)/*), echo $(f) gfx/$(f:$(BUILD_DIR)/%=%) >> $(BASEPACK_LST);)
	@find actors -name \*.png -exec echo "{} gfx/{}" >> $(BASEPACK_LST) \;
	@find levels -name \*.png -exec echo "{} gfx/{}" >> $(BASEPACK_LST) \;
	@find textures -name \*.png -exec echo "{} gfx/{}" >> $(BASEPACK_LST) \;

# prepares the resource ZIP with base data
$(BASEPACK_PATH): $(BASEPACK_LST)
	@$(PRINT) "$(GREEN)Packing basepack zip file.$(NO_COL)\n"
	$(V)$(PYTHON) $(TOOLS_DIR)/mkzip.py $(BASEPACK_LST) $(BASEPACK_PATH)

endif

#all: $(ROM)
all: $(EXE)

ifeq ($(WINDOWS_BUILD),1)
exemap: $(EXE)
	$(V)$(OBJDUMP) -t $(EXE) > $(BUILD_DIR)/coop.map
all: exemap
endif

ifeq ($(COMPARE),1)
	@$(PRINT) "$(GREEN)Checking if ROM matches.. $(NO_COL)\n"
	@$(SHA1SUM) --quiet -c $(TARGET).sha1 && $(PRINT) "$(TARGET): $(GREEN)OK$(NO_COL)\n" || ($(PRINT) "$(YELLOW)Building the ROM file has succeeded, but does not match the original ROM.\nThis is expected, and not an error, if you are making modifications.\nTo silence this message, use 'make COMPARE=0.' $(NO_COL)\n" && false)
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

$(BUILD_DIR)/$(BASS_LIBS):
	@$(CP) -f $(BASS_LIBS) $(BUILD_DIR)

$(BUILD_DIR)/$(COOPNET_LIBS):
	@$(CP) -f $(COOPNET_LIBS) $(BUILD_DIR)

$(BUILD_DIR)/$(LANG_DIR):
	@$(CP) -f -r $(LANG_DIR) $(BUILD_DIR)

$(BUILD_DIR)/$(MOD_DIR):
	@$(CP) -f -r $(MOD_DIR) $(BUILD_DIR)

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
  $(BUILD_DIR)/levels/menu/leveldata.o: $(BUILD_DIR)/include/text_strings.h
  $(BUILD_DIR)/levels/menu/leveldata.o: $(BUILD_DIR)/text/us/define_courses.inc.c
  $(BUILD_DIR)/levels/menu/leveldata.o: $(BUILD_DIR)/text/de/define_courses.inc.c
  $(BUILD_DIR)/levels/menu/leveldata.o: $(BUILD_DIR)/text/fr/define_courses.inc.c
  $(BUILD_DIR)/src/game/level_info.o: $(BUILD_DIR)/include/text_strings.h
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

$(BUILD_DIR)/include/text_strings.h: $(BUILD_DIR)/include/text_menu_strings.h
$(BUILD_DIR)/src/menu/file_select.o: $(BUILD_DIR)/include/text_strings.h
$(BUILD_DIR)/src/menu/star_select.o: $(BUILD_DIR)/include/text_strings.h
$(BUILD_DIR)/src/game/camera.o:      $(BUILD_DIR)/include/text_strings.h
$(BUILD_DIR)/src/game/ingame_menu.o: $(BUILD_DIR)/include/text_strings.h


#==============================================================================#
# Texture Generation                                                           #
#==============================================================================#
TEXTURE_ENCODING := u8

ifeq ($(EXTERNAL_DATA),1)
  $(BUILD_DIR)/%: %.png
	$(call print,Dummying:,$<,$@)
	$(V)$(PYTHON) $(TOOLS_DIR)/zeroterm.py "$(patsubst %.png,%,$^)" > $@
else
  # Convert PNGs to RGBA32, RGBA16, IA16, IA8, IA4, IA1, I8, I4 binary files
  $(BUILD_DIR)/%: %.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS) -s raw -i $@ -g $< -f $(lastword $(subst ., ,$@))

  $(BUILD_DIR)/%.inc.c: %.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS) -s $(TEXTURE_ENCODING) -i $@ -g $< -f $(lastword ,$(subst ., ,$(basename $<)))
endif


ifeq ($(EXTERNAL_DATA),0)
  # Color Index CI8
  $(BUILD_DIR)/%.ci8: %.ci8.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS_CI) -i $@ -g $< -f ci8

  # Color Index CI4
  $(BUILD_DIR)/%.ci4: %.ci4.png
	$(call print,Converting:,$<,$@)
	$(V)$(N64GRAPHICS_CI) -i $@ -g $< -f ci4
endif

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
	$(V)hexdump -v -e '1/1 "0x%X,"' $< > $@.inc.c
	$(V)echo >> $@.inc.c

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

$(SOUND_BIN_DIR)/sound_data.ctl: sound/sound_banks/ $(SOUND_BANK_FILES) $(SOUND_SAMPLE_AIFCS) $(ENDIAN_BITWIDTH)
	@$(PRINT) "$(GREEN)Generating:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(PYTHON) $(TOOLS_DIR)/assemble_sound.py $(BUILD_DIR)/sound/samples/ sound/sound_banks/ $(SOUND_BIN_DIR)/sound_data.ctl $(SOUND_BIN_DIR)/ctl_header $(SOUND_BIN_DIR)/sound_data.tbl $(SOUND_BIN_DIR)/tbl_header $(C_DEFINES) $$(cat $(ENDIAN_BITWIDTH))

$(SOUND_BIN_DIR)/sound_data.tbl: $(SOUND_BIN_DIR)/sound_data.ctl
	@true

$(SOUND_BIN_DIR)/ctl_header: $(SOUND_BIN_DIR)/sound_data.ctl
	@true

$(SOUND_BIN_DIR)/tbl_header: $(SOUND_BIN_DIR)/sound_data.ctl
	@true

$(SOUND_BIN_DIR)/sequences.bin: $(SOUND_BANK_FILES) sound/sequences.json $(SOUND_SEQUENCE_DIRS) $(SOUND_SEQUENCE_FILES) $(ENDIAN_BITWIDTH)
	@$(PRINT) "$(GREEN)Generating:  $(BLUE)$@ $(NO_COL)\n"
	$(V)$(PYTHON) $(TOOLS_DIR)/assemble_sound.py --sequences $@ $(SOUND_BIN_DIR)/sequences_header $(SOUND_BIN_DIR)/bank_sets sound/sound_banks/ sound/sequences.json $(SOUND_SEQUENCE_FILES) $(C_DEFINES) $$(cat $(ENDIAN_BITWIDTH))

$(SOUND_BIN_DIR)/bank_sets: $(SOUND_BIN_DIR)/sequences.bin
	@true

$(SOUND_BIN_DIR)/sequences_header: $(SOUND_BIN_DIR)/sequences.bin
	@true

$(SOUND_BIN_DIR)/%.m64: $(SOUND_BIN_DIR)/%.o
	$(call print,Converting to M64:,$<,$@)
	$(V)$(OBJCOPY) -j .rodata $< -O binary $@


#==============================================================================#
# Generated Source Code Files                                                  #
#==============================================================================#

ifeq ($(EXTERNAL_DATA),1)
  $(SOUND_BIN_DIR)/%.inc.c: $(SOUND_BIN_DIR)/%
	$(call print,Dummying:,$<,$@)
	$(V)$(PYTHON) $(TOOLS_DIR)/zeroterm.py "$(patsubst $(BUILD_DIR)/%,%,$^)" | hexdump -v -e '1/1 "0x%X,"' > $@
endif

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
$(BUILD_DIR)/include/text_strings.h: include/text_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap.txt $< $@
$(BUILD_DIR)/include/text_menu_strings.h: include/text_menu_strings.h.in
	$(call print,Encoding:,$<,$@)
	$(V)$(TEXTCONV) charmap_menu.txt $< $@
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
  $(EXE): $(O_FILES) $(MIO0_FILES:.mio0=.o) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(BUILD_DIR)/$(RPC_LIBS) $(BUILD_DIR)/$(DISCORD_SDK_LIBS) $(BUILD_DIR)/$(BASS_LIBS) $(BUILD_DIR)/$(COOPNET_LIBS) $(BUILD_DIR)/$(LANG_DIR) $(BUILD_DIR)/$(MOD_DIR)
	@$(PRINT) "$(GREEN)Linking executable: $(BLUE)$@ $(NO_COL)\n"
	$(V)$(LD) $(PROF_FLAGS) -L $(BUILD_DIR) -o $@ $(O_FILES) $(ULTRA_O_FILES) $(GODDARD_O_FILES) $(LDFLAGS)
endif

.PHONY: all clean distclean default diff test load libultra res
.PRECIOUS: $(BUILD_DIR)/bin/%.elf $(SOUND_BIN_DIR)/%.ctl $(SOUND_BIN_DIR)/%.tbl $(SOUND_SAMPLE_TABLES) $(SOUND_BIN_DIR)/%.s $(BUILD_DIR)/%
# with no prerequisites, .SECONDARY causes no intermediate target to be removed
.SECONDARY:

APP_DIR = ./sm64ex-coop.app
APP_CONTENTS_DIR = $(APP_DIR)/Contents
APP_MACOS_DIR = $(APP_CONTENTS_DIR)/MacOS

all:
	@if [ "$(USE_APP)" = "0" ]; then \
		rm -rf build/us_pc/sm64ex-coop.app; \
    else \
		$(PRINT) "$(GREEN)Creating App Bundle: $(BLUE)build/us_pc/sm64ex-coop.app\n"; \
		rm -rf $(APP_DIR); \
		rm -rf build/us_pc/sm64ex-coop.app; \
		mkdir -p $(APP_MACOS_DIR); \
		mkdir -p $(APP_CONTENTS_DIR)/Resources; \
		mv build/us_pc/sm64.us.f3dex2e $(APP_MACOS_DIR)/sm64ex-coop; \
		cp -r build/us_pc/* $(APP_MACOS_DIR); \
		cp res/icon.icns $(APP_CONTENTS_DIR)/Resources/icon.icns; \
		echo "APPL????" > $(APP_CONTENTS_DIR)/PkgInfo; \
		echo '<?xml version="1.0" encoding="UTF-8"?>' > $(APP_CONTENTS_DIR)/Info.plist; \
		echo '<!DOCTYPE plist PUBLIC "-//Apple Computer//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '<plist version="1.0">' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '<dict>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <key>CFBundleExecutable</key>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <string>sm64ex-coop</string>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <key>CFBundleIconFile</key>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <string>icon</string>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <key>CFBundleIconName</key>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <string>AppIcon</string>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <key>CFBundleDisplayName</key>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <string>sm64ex-coop</string>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '    <!-- Add other keys and values here -->' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '</dict>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		echo '</plist>' >> $(APP_CONTENTS_DIR)/Info.plist; \
		chmod +x $(APP_MACOS_DIR)/sm64ex-coop; \
		mv $(APP_DIR) build/us_pc/; \
    fi

# Remove built-in rules, to improve performance
MAKEFLAGS += --no-builtin-rules

-include $(DEP_FILES)

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
