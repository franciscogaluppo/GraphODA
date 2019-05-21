#ifndef DAGH
#define DAGH

#include "GraphGen.hpp"

class Dag : public GraphGen {
	public:
		Dag();
		Dag(int);
		Dag(GraphGen&);
};

#endif
