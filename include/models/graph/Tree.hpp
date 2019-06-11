#ifndef TREEH
#define TREEH

#include "Chordal.hpp"

class Tree : public Chordal {
  public:
	Tree();
	Tree(int);
	Tree(GraphGen &);
};

class TreeConstructorException : public GraphException {
  public:
	TreeConstructorException() {}
	const char *what() const throw() {
		return "constructor parameter is not a tree";
	}
};

#endif
