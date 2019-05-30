#ifndef REPLH
#define REPLH

#include "Bipartite.hpp"
#include "Chordal.hpp"
#include "Dag.hpp"
#include "Graph.hpp"
#include "GraphCanvas.hpp"
#include "Interface.hpp"
#include "Tree.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

namespace repl {
	void run();
}

class REPLException : public exception {
	public:
		REPLException() {}
		const char *what() const throw () { return "REPL Exception"; }
};

class REPLInvalidCommandException : REPLException {
	public:
		REPLInvalidCommandException() {}
		const char *what() const throw () { return "invalid syntax"; }
};

class REPLVertexNotFoundException : REPLException {
	public:
		REPLVertexNotFoundException() {}
		const char *what() const throw () {
			return "coudn't find vertex with given label";
		}
};

#endif
