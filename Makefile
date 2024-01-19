battleship: main.o board.o input.o output.o playerboard.o computerboard.o ship.o gamelogic.o battleship.o
	g++ main.o board.o input.o output.o playerboard.o computerboard.o ship.o gamelogic.o battleship.o -o BattleShip

battleship.o: src/BattleShip.cpp
	g++ 

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

gamelogic.o: src/GameLogic.cpp include/GameLogic.h
	g++ -c src/GameLogic.cpp

battleship.o: src/BattleShip.cpp
	g++ -c src/BattleShip.cpp

clean:
	del *.o schiffe