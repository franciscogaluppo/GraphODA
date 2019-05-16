#ifndef TREEH
#define TREEH

#include "Graph.hpp"
#include "Chordal.hpp"
#include "../dataStructures/DSU.hpp"

#include <algorithm>

class Tree : public Chordal {
	public:
		Tree();
		Tree(int);
};

Tree mst(Graph&);

#endif
