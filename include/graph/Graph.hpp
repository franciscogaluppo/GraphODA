#ifndef GRAPH
#define GRAPH

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Graph {
	public:
		vector<string> label;

		Graph();
		Graph(int);
		Graph(int, vector<string>&);

		int getN();
		int getM();
		bool isWeighted();
		vector<vector<pair<int, int> > > getAdj();
		vector<pair<int, int> > getEdges();
		vector<int> getPesos();
		vector<vector<int> > getMatrix();
		vector<vector<int> > getSimMatrix();

		void addEdge(int, int);
		void addEdge(int, int, int);

	private:
		int n, m;
		vector<vector<pair<int, int> > > adj;
		bool weighted;
};

#endif
