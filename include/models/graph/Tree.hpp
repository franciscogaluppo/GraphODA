#ifndef TREEH
#define TREEH

#include "Chordal.hpp"

class Tree : public Chordal {
	public:
		Tree();
		Tree(int);
		Tree(GraphGen&);
};

#endif
