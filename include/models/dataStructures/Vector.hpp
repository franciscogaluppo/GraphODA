#ifndef VECTORH
#define VECTORH

#include <cmath>
#include <utility>
using namespace std;

class Vector {
   public:
	float x, y;

	Vector();
	Vector(float, float);
	Vector(pair<float, float>);
	float norm();
	float angle();
	Vector rotate(float);
	Vector project(Vector);
};

Vector operator+(const Vector &, const Vector &);
Vector operator-(const Vector &, const Vector &);
Vector operator*(const Vector &, const float);
float operator*(const Vector &, const Vector &);  // dot product
float operator%(const Vector &, const Vector &);  // cross product
float operator^(const Vector &, const Vector &);  // distance

#endif
