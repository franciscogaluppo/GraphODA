linux: # Pro chico mexer no Locus
	g++ -std=c++14 main.cpp Graph.cpp -ltgui -lsfml-graphics -lsfml-window -lsfml-system -o infoGraph

mac: # Pro chico mexer
	clang++ -std=c++14 main.cpp Graph.cpp -I SFML/include -I TGUI/include -ltgui -lsfml-graphics -lsfml-window -lsfml-system -o infoGraph

clean:
	rm infoGraph
