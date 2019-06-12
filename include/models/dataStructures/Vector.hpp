#ifndef VECTORH
#define VECTORH

#include <cmath>
#include <utility>
using namespace std;

///
/// @file

///
/// Classe para operações vetoriais no espaço real de duas dimensões.
class Vector {
  public:
	///
	/// Coordenada x do vetor.
	float x;

	///
	/// Coordenada y do vetor.
	float y;

	///
	/// Construtor do vetor zero;
	Vector();

	///
	/// Construtor do vetor pelas posições x e y.
	Vector(float, float);

	///
	/// Construtor do vetor por par de posições.
	Vector(pair<float, float>);

	///
	/// Calcula a norma do vetor.
	float norm();

	///
	/// Calcula o ângulo do vetor com o eixo x.
	float angle();

	///
	/// Rotaciona o vetor em um dado ângulo.
	Vector rotate(float);

	///
	/// Projeção do vetor sobre um outro vetor.
	Vector project(Vector);
};

///
/// Soma de vetores.
Vector operator+(const Vector &, const Vector &);

///
/// Subtração de vetores.
Vector operator-(const Vector &, const Vector &);

///
/// Multiplicação de um vetor por um escalar.
Vector operator*(const Vector &, const float);

///
/// Produto escalar entre vetores.
float operator*(const Vector &, const Vector &);

///
/// Produto vetorial entre vetores.
float operator%(const Vector &, const Vector &);

///
/// Distância normalizada entre vetores.
float operator^(const Vector &, const Vector &);

#endif
