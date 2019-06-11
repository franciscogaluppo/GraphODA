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
#include <string>

using namespace std;

namespace repl {
void run(int, int);
}

class REPLException : public exception {
   public:
	REPLException() {}
	const char *what() const throw() { return "REPL Exception"; }
};

class REPLInvalidCommandException : public REPLException {
   public:
	REPLInvalidCommandException() {}
	const char *what() const throw() { return "invalid syntax"; }
};

class REPLVertexNotFoundException : public REPLException {
   public:
	REPLVertexNotFoundException(string v) {
		msg = "coudn't find vertex with label: " + v;
	}
	const char *what() const throw() { return msg.c_str(); }

   private:
	string msg;
};

#endif
