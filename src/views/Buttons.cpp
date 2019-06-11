#include "Buttons.hpp"

namespace functions {
void coloreChordal(GraphCanvas *GC) {
	Chordal C(GC->GD.G);
	auto coloracao = C.coloring();
	GC->GD.color = coloracao;
}

void mst(GraphCanvas *GC) {
	auto v = GC->GD.G.mstEdges();
	for (int i = 0; i < GC->GD.G.getM(); i++)
		GC->GD.colorAresta[i] = (v[i] ? 1 : 100);
}

void greedyColoring(GraphCanvas *GC) {
	auto coloracao = GC->GD.G.greedyColoring();
	GC->GD.color = coloracao;
}

void artPoints(GraphCanvas *GC) {
	auto art = GC->GD.G.artPoints();
	for (int i = 0; i < GC->GD.G.getN(); i++)
		if (art[i]) GC->GD.color[i] = 1;
}
} // namespace functions

namespace buttons {
void general(tgui::Gui &gui, vector<tgui::Button::Ptr> &v) {
	vector<int> op = {1, 2, 3};
	for (int i : op) gui.add(v[i]);
}

void clear(tgui::Gui &gui, vector<tgui::Button::Ptr> &v) {
	for (auto i : v) gui.remove(i);
}

void bipartite(tgui::Gui &gui, vector<tgui::Button::Ptr> &v) {}

void chordal(tgui::Gui &gui, vector<tgui::Button::Ptr> &v) {
	vector<int> op = {0};
	for (int i : op) gui.add(v[i]);
}

void dag(tgui::Gui &gui, vector<tgui::Button::Ptr> &v) {}

void tree(tgui::Gui &gui, vector<tgui::Button::Ptr> &v) {}

void init(vector<tgui::Button::Ptr> &v, GraphCanvas &GC) {
	auto color = tgui::Button::create("Colore");
	v.push_back(color);
	color->setSize(75.f, 20.f);
	color->setPosition(1000.f, 650.f);
	color->connect("pressed", functions::coloreChordal, &GC);

	auto mst = tgui::Button::create("mst");
	v.push_back(mst);
	mst->setSize(75.f, 20.f);
	mst->setPosition(1000.f, 630.f);
	mst->connect("pressed", functions::mst, &GC);

	auto guloso = tgui::Button::create("Colore (guloso)");
	v.push_back(guloso);
	guloso->setSize(115.f, 20.f);
	guloso->setPosition(980.f, 600.f);
	guloso->connect("pressed", functions::greedyColoring, &GC);

	auto artPoints = tgui::Button::create("Pontos de art");
	v.push_back(artPoints);
	artPoints->setSize(115.f, 20.f);
	artPoints->setPosition(860.f, 600.f);
	artPoints->connect("pressed", functions::artPoints, &GC);
}

void update(tgui::Gui &gui, vector<tgui::Button::Ptr> &botoes, GraphCanvas &GC,
			int &tipoGrafo) {
	if (GC.GD.G.isTree())
		tipoGrafo = 4; // tem que ser primeiro pq herda das outras
	else if (GC.GD.G.isBipartite())
		tipoGrafo = 1;
	else if (GC.GD.G.isChordal())
		tipoGrafo = 2;
	else if (GC.GD.G.isDag())
		tipoGrafo = 3;
	else
		tipoGrafo = 0;

	clear(gui, botoes);
	general(gui, botoes);
	if (GC.GD.G.isBipartite()) bipartite(gui, botoes);
	if (GC.GD.G.isChordal()) chordal(gui, botoes);
	if (GC.GD.G.isDag()) dag(gui, botoes);
	if (GC.GD.G.isTree()) tree(gui, botoes);
}
} // namespace buttons
