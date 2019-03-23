#ifndef GRAPH
#define GRAPH

#include <bits/stdc++.h>
using namespace std;

struct Graph {
	int n, m;
	vector<string> label;
	vector<vector<int> > adj;
	vector<pair<int, int> > edges;

	Graph(int);
	Graph(int, vector<string>);
	void addEdge(int, int);
};

#endif
