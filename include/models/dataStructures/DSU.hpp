#ifndef DSUH
#define DSUH

#include <iostream>
#include <string>
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
	const char *what() const throw() { return "DSU Exception"; }
};

class DSUNegativeConstructorParameterException : public DSUException {
   public:
	DSUNegativeConstructorParameterException(int n) {
		msg = "constructor parameter cannot be negative; got " + to_string(n);
	}
	const char *what() const throw() { return msg.c_str(); }

   private:
	string msg;
};

class DSUValueOutOfBoundsException : public DSUException {
   public:
	DSUValueOutOfBoundsException(int n) {
		msg = "value out of bounds: " + to_string(n);
	}
	const char *what() const throw() { return msg.c_str(); }

   private:
	string msg;
};

#endif
