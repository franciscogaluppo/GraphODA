#ifndef DSUH
#define DSUH

#include <vector>
#include <iostream>
using namespace std;

class DSU {
	public:
		DSU(int);
		int find(int);
		void une(int, int);
	
	private:
		int n;
		vector<int> v;
		vector<int> sz;
};

#endif
