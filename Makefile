schiffe: main.o playfield.o gameRessources.o 
	g++ main.o playfield.o gameRessources.o -o schiffe

main.o: Main.cpp
	g++ -c Main.cpp

playfield.o: Playfield.cpp Headerdateien/Playfield.h
	g++ -c Playfield.cpp

gameRessources.o: GameRessources.cpp Headerdateien/GameRessources.h
	g++ -c GameRessources.cpp

clean:
	del *.o schiffe
