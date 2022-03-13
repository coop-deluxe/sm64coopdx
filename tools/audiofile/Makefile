CXX := g++

libaudiofile.a: audiofile.o
	$(AR) rcs $@ $^

audiofile.o: audiofile.cpp audiofile.h aupvlist.h
	#$(CXX) -std=c++11 -DNDEBUG -fno-rtti -fno-exceptions -fvisibility-inlines-hidden -O2 -I. -c audiofile.cpp
	$(CXX) -std=c++11 -O2 -I. -c $< -o $@

clean:
	$(RM) audiofile.o libaudiofile.a

.PHONY: clean
