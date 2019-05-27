#include "Vector.hpp"

Vector::Vector() {}

Vector::Vector(float x_, float y_) {
  x = x_;
  y = y_;
}

Vector::Vector(pair<float, float> v) { x = v.first, y = v.second; }

Vector operator+(const Vector &u, const Vector &v) {
  return Vector(u.x + v.x, u.y + v.y);
}

Vector operator-(const Vector &u, const Vector &v) {
  return Vector(u.x - v.x, u.y - v.y);
}

Vector operator*(const Vector &u, const float c) {
  return Vector(u.x * c, u.y * c);
}

float operator*(const Vector &u, const Vector &v) {
	return u.x * v.x + u.y * v.y;
}

float operator%(const Vector &u, const Vector &v) {
		return u.x * v.y - u.y * v.x;
}

float operator^(const Vector &u, const Vector &v) {
	return (u - v).norm();	
}

float Vector::norm() { return sqrt(x * x + y * y); }

float Vector::angle() { return atan2(y, x); }

Vector Vector::rotate(float th) {
  return Vector(x * cos(th) - y * sin(th), x * sin(th) + y * cos(th));
}

// projecao sobre o vetor v
Vector Vector::project(Vector v) { return v * ((*this)*v) * (1 / (v*v)); }
