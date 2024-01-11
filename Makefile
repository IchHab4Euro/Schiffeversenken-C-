schiffe: main.o board.o gameRessources.o playerboard.o computerboard.o ship.o shipsegment.o
	g++ main.o board.o gameRessources.o playerboard.o computerboard.o ship.o shipsegment.o -o schiffe

main.o: Main.cpp
	g++ -c Main.cpp

board.o: Board.cpp Headerdateien/Board.h
	g++ -c Board.cpp

gameRessources.o: GameRessources.cpp Headerdateien/GameRessources.h
	g++ -c GameRessources.cpp

playerboard.o: PlayerBoard.cpp Headerdateien/PlayerBoard.h
	g++ -c PlayerBoard.cpp

computerboard.o: ComputerBoard.cpp Headerdateien/ComputerBoard.h
	g++ -c ComputerBoard.cpp

ship.o: Ship.cpp Headerdateien/Ship.h 
	g++ -c Ship.cpp

shipsegment.o: Shipsegment.cpp Headerdateien/Shipsegment.h
	g++ -c Shipsegment.cpp

clean:
	del *.o schiffe