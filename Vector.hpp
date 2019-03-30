#ifndef VECTORH
#define VECTORH

#include <bits/stdc++.h>
using namespace std;

struct Vector {
	float x, y;

	Vector(float, float);
	Vector(pair<float, float>);
	float norm();
};

Vector operator +(const Vector&, const Vector&);
Vector operator -(const Vector&, const Vector&);
Vector operator *(const Vector&, const float);

float cross(Vector, Vector);
float dist(Vector, Vector);

#endif
