#ifndef GRAPH
#define GRAPH

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Graph {
	public:
		vector<string> label;
		vector<vector<pair<int, int> > > adj;

		Graph();
		Graph(int);
		Graph(int, vector<string>&);

		int getN();
		int getM();
		bool isWeighted();
		void checkWeighted();
		vector<pair<int, int> > getEdges();
		vector<int> getPesos();
		vector<vector<int> > getMatrix();
		vector<vector<int> > getSimMatrix();
		void addEdge(int, int);
		void addEdge(int, int, int);

	private:
		int n, m;
		bool weighted;
};

#endif
