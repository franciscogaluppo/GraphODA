#ifndef CHORDALH
#define CHORDALH

#include "GraphGen.hpp"

class Chordal : public GraphGen {
	public:
		Chordal();
		Chordal(int);
		Chordal(GraphGen&);

		// Algoritmos
		vector<int> perfectEliminationOrdering();
		vector<int> coloring() override;
		int chromaticNumber();
};

class ChordalConstructorException : public GraphException {
	public:
		ChordalConstructorException() {}
		const char *what() const throw () {
			return "constructor parameter is not chordal";	
		}
};

#endif
