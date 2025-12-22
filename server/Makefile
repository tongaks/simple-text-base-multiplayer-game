server: build/socket.o build/main.o build/game.o
	g++ build/socket.o build/main.o build/game.o -o server


build/main.o: headers/socket.h src/main.cpp src/socket.cpp
	g++ -c src/main.cpp -o build/main.o


build/socket.o: headers/socket.h headers/includes.h src/socket.cpp
	g++ -c src/socket.cpp -o build/socket.o

build/game.o: headers/game.h headers/includes.h src/game.cpp
	g++ -c src/game.cpp -o build/game.o

# build/window.o: headers/window.h src/window.cpp src/setup_controls.cpp src/system_handler.cpp
# 	g++ -c src/window.cpp -o build/window.o `wx-config --cxxflags --libs`

clean:
	rm build/*.o