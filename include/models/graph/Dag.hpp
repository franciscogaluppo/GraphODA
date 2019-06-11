#ifndef DAGH
#define DAGH

#include "GraphGen.hpp"

class Dag : public GraphGen {
   public:
	Dag();
	Dag(int);
	Dag(GraphGen &);
};

class DagConstructorException : public GraphException {
   public:
	DagConstructorException() {}
	const char *what() const throw() {
		return "construcor parameter is not a dag";
	}
};

#endif
