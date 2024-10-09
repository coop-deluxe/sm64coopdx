#!/bin/bash

if [ $# -eq 0 ]; then
	EXTRA=""
else
	EXTRA="--enable=all --suppress=constStatement --suppress=duplicateCondition --suppress=redundantAssignment --suppress=variableScope --suppress=unusedVariable --suppress=unreadVariable --suppress=shadowVariable"
fi

INCLUDES="-Iinclude -Isrc -I. -Ilib/lua/include"
DEFINES="-DRAPI_GL=1 -DWAPI_SDL2=1 -DAAPI_SDL2=1 -DCAPI_SDL2=1 -DHAVE_SDL2=1 -DVERSION_US -D_LANGUAGE_C -DNIGHTLY -DNON_MATCHING -DAVOID_UB -DF3DEX_GBI_2E -DDISCORD_SDK"
PARAMS="--language=c --quiet --platform=unix64 -v src -j8"

cppcheck -DLLONG_MAX $INCLUDES $DEFINES $EXTRA $PARAMS
