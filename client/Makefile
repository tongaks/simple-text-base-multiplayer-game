client: build/client.o build/main.o
	g++ build/client.o build/main.o -o client


build/main.o: headers/client.h src/main.cpp src/client.cpp
	g++ -c src/main.cpp -o build/main.o


build/client.o: headers/client.h headers/includes.h src/client.cpp
	g++ -c src/client.cpp -o build/client.o

# build/window.o: headers/window.h src/window.cpp src/setup_controls.cpp src/system_handler.cpp
# 	g++ -c src/window.cpp -o build/window.o `wx-config --cxxflags --libs`

clean:
	rm build/*.o