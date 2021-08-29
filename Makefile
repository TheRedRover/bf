CXX			= g++
CXXFLAGS	= -std=c++17 -O2 -Wall

ODIR		= ./build
BDIR		= ./bin
IDIR		= ./brainfuck

bfmachine: dir
	$(CXX) -o $(BDIR)/$@ $(IDIR)/brainfuck.cpp $(IDIR)/bfmake.cpp $(CXXFLAGS)

dir: $(IDIR)/brainfuck.cpp $(IDIR)/brainfuck.h $(IDIR)/bfmake.cpp
	mkdir -p bin build

clean:
	rm -rv bin 