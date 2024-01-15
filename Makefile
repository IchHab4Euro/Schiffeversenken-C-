schiffe: main.o board.o input.o output.o playerboard.o computerboard.o ship.o shipsegment.o
	g++ main.o board.o input.o output.o playerboard.o computerboard.o ship.o shipsegment.o -o schiffe

main.o: src/Main.cpp
	g++ -c src/Main.cpp

board.o: src/Board.cpp include/Board.h
	g++ -c src/Board.cpp

input.o: src/Input.cpp include/Input.h
	g++ -c src/Input.cpp

output.o: src/Output.cpp include/Output.h
	g++ -c src/Output.cpp

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