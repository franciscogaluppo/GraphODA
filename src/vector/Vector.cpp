#include "Vector.hpp"

Vector::Vector(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector::Vector(pair<float, float> v) {
	x = v.first, y = v.second;
}

Vector operator +(const Vector &u, const Vector &v) {
	return Vector(u.x+v.x, u.y+v.y);
}

Vector operator -(const Vector &u, const Vector &v) {
	return Vector(u.x-v.x, u.y-v.y);
}

Vector operator *(const Vector &u, const float c) {
	return Vector(u.x*c, u.y*c);
}

float Vector::norm() {
	return sqrt(x*x + y*y);
}

float Vector::angle() {
	return atan2(y, x);
}

Vector Vector::rotate(float th) {
	return Vector(x*cos(th)-y*sin(th), x*sin(th)+y*cos(th));
}

// norma do produvo vetorial
float cross(Vector u, Vector v) {
	return u.x*v.y - u.y*v.x;
}

float dist(Vector u, Vector v) {
	return (u-v).norm();
}