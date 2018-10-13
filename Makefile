
CXX = g++
CXXFLAGS	= -std=c++11 -Wall

all: thunderDungeon

clean:
	rm Board.o Tile.o thunderDungeon

thunderDungeon: Board.o Tile.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp Board.o Tile.o -o thunderDungeon

Board.o: Board.cpp
	$(CXX) $(CXXFLAGS) -c Board.cpp

Tile.o: Tile.cpp
	$(CXX) $(CXXFLAGS) -c Tile.cpp

