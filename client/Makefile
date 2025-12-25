
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

MAIN_OBJECTS := build/main.o build/character.o build/game.o build/client.o

main: $(MAIN_OBJECTS)
	$(CXX) $^ -o $@ -lncurses

build/main.o: src/main.cpp headers/client.h headers/game.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/character.o: src/character.cpp headers/character.h headers/includes.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/game.o: src/game.cpp headers/client.h headers/includes.h headers/game.h headers/character.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@ -lncurses

build/client.o: src/client.cpp headers/client.h
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# build/client.o: headers/client.h headers/includes.h src/client.cpp
# 	g++ -c src/client.cpp -o build/client.o

# build/game.o: headers/client.h headers/includes.h src/client.cpp src/game.cpp headers/game.h
# 	g++ -c src/game.cpp -o build/game.o

# build/window.o: headers/window.h src/window.cpp src/setup_controls.cpp src/system_handler.cpp
# 	g++ -c src/window.cpp -o build/window.o `wx-config --cxxflags --libs`

clean:
	rm build/*.o