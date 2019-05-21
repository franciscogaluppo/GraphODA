#ifndef BIPARTITEH
#define BIPARTITEH

#include "GraphGen.hpp"

class Bipartite : public GraphGen {
	public:
		Bipartite();
		Bipartite(int);
		Bipartite(GraphGen&);
};

#endif
