
CXX = g++
CXXFLAGS	= -std=c++11 -Wall -pthread

all: thunderDungeon

clean:
	rm Game.o Board.o Tile.o Command.o thunderDungeon

thunderDungeon: Game.o Board.o Tile.o Command.o main.cpp
	$(CXX) $(CXXFLAGS) main.cpp Game.o Board.o Tile.o Command.o -o thunderDungeon

Game.o: Game.cpp
	$(CXX) $(CXXFLAGS) -c Game.cpp

Board.o: Board.cpp
	$(CXX) $(CXXFLAGS) -c Board.cpp

Tile.o: Tile.cpp
	$(CXX) $(CXXFLAGS) -c Tile.cpp

Command.o: Command.cpp
	$(CXX) $(CXXFLAGS) -c Command.cpp
