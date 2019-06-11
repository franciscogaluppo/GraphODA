#ifndef BIPARTITEH
#define BIPARTITEH

#include "GraphGen.hpp"

class Bipartite : public GraphGen {
  public:
	Bipartite();
	Bipartite(int);
	Bipartite(GraphGen &);
};

class BipartiteConstructorException : public GraphException {
  public:
	BipartiteConstructorException() {}
	const char *what() const throw() {
		return "constructor paramer is not bipartite";
	}
};

#endif
