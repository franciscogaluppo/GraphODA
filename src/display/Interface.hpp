#ifndef INTERFACEH
#define INTERFACEH

#include "../vector/Vector.hpp"
#include "../graph/Graph.hpp"
#include "DrawGraph.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <bits/stdc++.h>
using namespace std;

int findFontSize(int, int);

void printGrafo(sf::RenderWindow&, sf::Font&, Graph&, vector<Vector>&, int);

void lerGrafoArquivo(tgui::EditBox::Ptr, Graph*, vector<Vector>*, int*, int*);

int achaVertice(Vector, vector<Vector>, float);

void loadWidgets(tgui::Gui&, Graph*, vector<Vector>*, int*, int*);

void displayTeste(int, int);

#endif
