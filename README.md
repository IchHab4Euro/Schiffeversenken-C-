# Schiffeversenken-C-
Schiffeversenken

Compilieren:
Kompilieren des Codes durch Makefile oder alternativ mit folgendem Befehl im Terminal:
g++ .\BattleShip.cpp .\Board.cpp .\BoardSegment.cpp .\ComputerBoard.cpp .\GameLogic.cpp .\Input.cpp .\Output.cpp .\PlayerBoard.cpp .\Ship.cpp -o BattleShip

Löschen der .o Dateien
Um alle .o Dateien zu löschen muss man "mingw32-make clean" eingaben

Windows:
Bei Benutzung auf Windows, muss der Zufallszahlengenerator eventuell auf generateRandomNumberWindows in der ComputerBoard Klasse umgestellt werden

Symbole auf dem Feld:
#=Schiff
#Rot=Schiff getroffen
#Grau=Schiff sunken
~Blau=Water Hit