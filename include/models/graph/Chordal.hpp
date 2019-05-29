#ifndef CHORDALH
#define CHORDALH

#include "GraphGen.hpp"

class Chordal : public GraphGen {
	public:
		Chordal();
		Chordal(int);
		Chordal(GraphGen&);
};

class ChordalConstructorException : public GraphException {
	public:
		ChordalConstructorException() {}
		const char *what() const throw () {
			return "constructor parameter is not chordal";	
		}
};

#endif
