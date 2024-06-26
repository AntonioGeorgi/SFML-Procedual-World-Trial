all: compile link clean start

compile:
	g++ -c main.cpp .\C-Files\*cpp -I"C:\Users\Tonio\OneDrive\Programmieren\C++\libraries\SFML-2.6.0\include"

link:
	g++ *.o -o .\Executables\game -LC:\Users\Tonio\OneDrive\Programmieren\C++\libraries\SFML-2.6.0\lib -lopenal32 -lsfml-audio -lsfml-graphics -lsfml-network  -lsfml-system -lsfml-window
	
clean:
	erase *.o

start:
	.\Executables\game.exe
	