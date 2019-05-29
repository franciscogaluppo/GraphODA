#ifndef DSUH
#define DSUH

#include <iostream>
#include <vector>
using namespace std;

class DSU {
	public:
		DSU();
		DSU(int);
		int find(int);
		void une(int, int);

	private:
		int n;
		vector<int> v;
		vector<int> sz;
};

class DSUException : public exception {
	public:
		DSUException() {}
		const char *what() const throw () { return "DSU Exception"; }
};

class DSUNegativeConstructorParameterException : public DSUException {
	public:
		DSUNegativeConstructorParameterException(int n_) : n(n_) {}
		const char *what() const throw () {
			return "constructor parameter cannot be negative";
		}
		int get() { return n; }

	private:
		int n;
};

class DSUValueOutOfBoundsException : public DSUException {
	public:
		DSUValueOutOfBoundsException(int n_) : n(n_) {}
		const char *what() const throw () {
			return "value out of bounds";
		}
		int get() { return n; }

	private:
		int n;
};

#endif
