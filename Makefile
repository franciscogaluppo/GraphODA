CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wshadow -Wno-sign-compare
DEPS = -ltgui -lsfml-graphics -lsfml-window -lsfml-system

all: build clean

build: obj/main.o obj/Interface.o obj/GraphDisplay.o obj/Graph.o obj/Vector.o
	$(CXX) $(CXXFLAGS) -o graphODA obj/main.o obj/Interface.o obj/GraphDisplay.o obj/Graph.o obj/Vector.o $(DEPS)

obj/main.o: src/main.cpp src/display/Interface.cpp src/display/Interface.hpp src/display/GraphDisplay.cpp src/display/GraphDisplay.hpp src/graph/Graph.cpp src/graph/Graph.hpp src/vector/Vector.cpp src/vector/Vector.hpp
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -o obj/main.o -c src/main.cpp

obj/Interface.o: src/display/Interface.cpp src/display/Interface.hpp src/display/GraphDisplay.cpp src/display/GraphDisplay.hpp src/graph/Graph.cpp src/graph/Graph.hpp src/vector/Vector.cpp src/vector/Vector.hpp
	$(CXX) $(CXXFLAGS) -o obj/Interface.o -c src/display/Interface.cpp

obj/GraphDisplay.o: src/display/GraphDisplay.cpp src/display/GraphDisplay.hpp src/graph/Graph.cpp src/graph/Graph.hpp src/vector/Vector.cpp src/vector/Vector.hpp
	$(CXX) $(CXXFLAGS) -o obj/GraphDisplay.o -c src/display/GraphDisplay.cpp

obj/Graph.o: src/graph/Graph.cpp src/graph/Graph.hpp
	$(CXX) $(CXXFLAGS) -o obj/Graph.o -c src/graph/Graph.cpp

obj/Vector.o: src/vector/Vector.cpp src/vector/Vector.hpp
	$(CXX) $(CXXFLAGS) -o obj/Vector.o -c src/vector/Vector.cpp

mac:
	clang++ -std=c++14 src/main.cpp src/display/Interface.cpp src/display/GraphDisplay.cpp src/graph/Graph.cpp src/vector/Vector.cpp -ltgui -lsfml-graphics -lsfml-window -lsfml-system -o graphODA

locus_chico:
	/usr/bin/g++ -std=c++14 src/main.cpp src/display/Interface.cpp src/display/GraphDisplay.cpp src/graph/Graph.cpp src/vector/Vector.cpp -ltgui -lsfml-graphics -lsfml-window -lsfml-system -o graphODA

clean:
	rm -rf obj

commit:
	rm -f graphODA
	rm -rf obj
