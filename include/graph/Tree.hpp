#ifndef TREEH
#define TREEH

#include "Chordal.hpp"
#include "../dataStructures/DSU.hpp"

class Tree : public Chordal {
	public:
		Tree();
		Tree(int);
		
		void addEdge(int i, int j);
		void addEdge(int i, int j, int k);

	private:
		DSU dsu;
};

#endif
