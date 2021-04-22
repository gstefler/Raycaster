output: main.o
	g++ -o ./build/raycaster  ./build/main.o -Llib -std=c++14 -g -Wall -O3 -lmingw32 -lsfml-system -lsfml-window -lsfml-graphics -lsfml-main

main.o: ./src/main.cpp
	g++ -o ./build/main.o -c ./src/main.cpp -Iinclude