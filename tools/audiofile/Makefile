CXX := g++

CFLAGS :=

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
  CFLAGS += -DWIN32 -D_WIN32
endif

libaudiofile.a: audiofile.o
	$(AR) rcs $@ $^

audiofile.o: audiofile.cpp audiofile.h aupvlist.h
	#$(CXX) $(CFLAGS) -std=c++11 -DNDEBUG -fno-rtti -fno-exceptions -fvisibility-inlines-hidden -O2 -I. -c audiofile.cpp
	$(CXX) $(CFLAGS) -std=c++11 -O2 -I. -c $< -o $@

clean:
	$(RM) audiofile.o libaudiofile.a

.PHONY: clean
