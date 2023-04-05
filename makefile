all:
	clear
	mkdir -p build/
	ccache g++ -c src/main.cpp -o build/main.o
	ccache g++ -c src/gif.cpp -o build/gif.o
	ccache g++ build/*.o -lsfml-system -lsfml-window -lsfml-graphics