linux: # Pro chico mexer no Locus
	g++ -std=c++14 src/main.cpp src/display/Interface.cpp src/display/DrawGraph.cpp src/graph/Graph.cpp src/vector/Vector.cpp -ltgui -lsfml-graphics -lsfml-window -lsfml-system -o graphODA.exe

mac: # Pro chico mexer
	clang++ -std=c++14 src/main.cpp src/display/Interface.cpp src/display/DrawGraph.cpp src/graph/Graph.cpp src/vector/Vector.cpp -ltgui -lsfml-graphics -lsfml-window -lsfml-system -o graphODA.exe

locus_chico:
	/usr/bin/g++ -std=c++14 src/main.cpp src/display/Interface.cpp src/display/DrawGraph.cpp src/graph/Graph.cpp src/vector/Vector.cpp -ltgui -lsfml-graphics -lsfml-window -lsfml-system -o graphODA.exe

clean:
	rm graphODA.exe
