
CXX = g++
CXXFLAGS	= -std=c++11 -Wall

all: thunderDungeon

clean:
	rm Board.o thunderDungeon

thunderDungeon: Board.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp Board.o -o thunderDungeon

Board.o: Board.cpp
	$(CXX) $(CXXFLAGS) -c Board.cpp

