schiffe: main.o playfield.o gameRessources.o playerPlayField.o
	g++ main.o playfield.o gameRessources.o playerPlayField.o -o schiffe

main.o: Main.cpp
	g++ -c Main.cpp

playfield.o: Playfield.cpp Headerdateien/Playfield.h
	g++ -c Playfield.cpp

gameRessources.o: GameRessources.cpp Headerdateien/GameRessources.h
	g++ -c GameRessources.cpp

playerPlayField.o: PlayerPlayField.cpp Headerdateien/PlayerPlayField.h
	g++ -c PlayerPlayField.cpp

clean:
	del *.o schiffe