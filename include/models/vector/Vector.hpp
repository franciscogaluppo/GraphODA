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

float cross(Vector, Vector);
float dist(Vector, Vector);
float dot(Vector, Vector);

#endif
