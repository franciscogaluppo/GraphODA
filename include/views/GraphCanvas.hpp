#ifndef GRAPH_CANVASH
#define GRAPH_CANVASH

#include "GraphDisplay.hpp"
#include "Vector.hpp"

#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

struct GraphCanvas {
	GraphDisplay GD;
	sf::RenderWindow *janela;
	sf::Font fonte;
	int editLabel, editWeight;

	GraphCanvas(sf::RenderWindow &, sf::Font &, int, int, int);
	void setGraph(Graph);
	void handleClique();
	void display();

	// private:
	sf::Color getColor(int);
	int findFontSize(int, int);
	int findFontSizeNew(int, int);
	void printPesos();
	void printAresta(Vector, int);
	void printGrafo();
	void printSetas();
};

Graph lerGrafoArquivo(string);

class FileNotFoundException : public exception {
	public:
		FileNotFoundException() {}
		const char *what() const throw () {
			return "couldn't read file";
		}
};

#endif
