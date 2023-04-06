all:
	clear
	mkdir -p build/
	ccache g++ -c src/main.cpp -o build/main.o
	ccache g++ -c src/gif.cpp -o build/gif.o
	ccache g++ build/*.o -lsfml-system -lsfml-window -lsfml-graphics

windows:
	clear
	mkdir -p build/
	ccache x86_64-pc-linux-gnu-g++ -c src/main.cpp -o build/main.o
	ccache x86_64-pc-linux-gnu-g++ -c src/gif.cpp -o build/gif.o
	ccache x86_64-pc-linux-gnu-g++ build/*.o -o FREECATS.EXE -lsfml-system -lsfml-window -lsfml-graphics