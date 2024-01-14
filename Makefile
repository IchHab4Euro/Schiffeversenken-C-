schiffe: main.o board.o gameRessources.o playerboard.o computerboard.o ship.o shipsegment.o
	g++ main.o board.o gameRessources.o playerboard.o computerboard.o ship.o shipsegment.o -o schiffe

main.o: src/Main.cpp
	g++ -c src/Main.cpp

board.o: src/Board.cpp include/Board.h
	g++ -c src/Board.cpp

gameRessources.o: src/GameRessources.cpp include/GameRessources.h
	g++ -c src/GameRessources.cpp

playerboard.o: src/PlayerBoard.cpp include/PlayerBoard.h
	g++ -c src/PlayerBoard.cpp

computerboard.o: src/ComputerBoard.cpp include/ComputerBoard.h
	g++ -c src/ComputerBoard.cpp

ship.o: src/Ship.cpp include/Ship.h 
	g++ -c src/Ship.cpp

shipsegment.o: src/Shipsegment.cpp include/Shipsegment.h
	g++ -c src/Shipsegment.cpp

clean:
	del *.o schiffe