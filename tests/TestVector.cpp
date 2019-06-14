#include "Vector.hpp"
#include "doctest.h"

TEST_CASE("Teste vector - construtor #1") {
	Vector v(1, 1);
	CHECK(v.x == 1.0);
}

TEST_CASE("Teste vector - construtor #2") {
	Vector v(make_pair(1, 1));
	CHECK(v.x == 1.0);
}

TEST_CASE("Teste vector - soma") {
	Vector v(1, 1), u(-1, 1), r = v+u;
	CHECK(r.norm() == 2.0);
}

TEST_CASE("Teste vector - subt") {
	Vector v(1, 1), u(-1, 1), r = v-u;
	CHECK(r.norm() == 2.0);
}

TEST_CASE("Teste vector - mult") {
	Vector v(0.5, 0), r = v*2.0;
	CHECK(r.norm() == 1.0);
}

TEST_CASE("Teste vector - dot") {
	Vector v(1, 1), u(-1, 1);
	CHECK(v*u == 0);
}

TEST_CASE("Teste vector - vetorial") {
	Vector v(1, 1), u(-1, 1);
	CHECK((v%u) == 2.0);
}

TEST_CASE("Teste vector - distancia") {
	Vector v(1, 1), u(-3, 1);
	CHECK((v^u) == 4.0);
}

TEST_CASE("Teste vector - angle") {
	pair<int,int> i = {1, 0};
	Vector v(i);
	CHECK(v.angle() == 0);
}

TEST_CASE("Teste vector - proj") {
	Vector v(1, 1), u(1, 0), r = v.project(u);
	CHECK(r.norm() == 1);
}

TEST_CASE("Teste vector - rotate") {
	Vector v(1, 0), r = v.rotate(0);
	CHECK(r.norm() == 1.0);
}

