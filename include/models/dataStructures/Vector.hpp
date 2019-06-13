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
	/// @param inteiros x e y correspondentes às posições do vetor
	Vector(float, float);

	///
	/// Construtor do vetor por par de posições.
	/// @param um pair que corresponde às posições do vetor
	Vector(pair<float, float>);

	///
	/// Calcula a norma do vetor.
	float norm();

	///
	/// Calcula o ângulo do vetor com o eixo x.
	float angle();

	///
	/// Rotaciona o vetor em um dado ângulo.
	/// @param float do ângulo de rotação
	/// @return o Vector rotacionado 
	Vector rotate(float);

	///
	/// Projeção do vetor sobre um outro vetor.
	/// @param Vector para a projeção
	/// @return Vector projetado
	Vector project(Vector);
};

///
/// Soma de vetores.
/// @param Vectores a serem somados
/// @return Vector resultante
Vector operator+(const Vector &, const Vector &);

///
/// Subtração de vetores.
/// @param Vector 1 e Vector 2
/// @return Vector 1 - Vector 2
Vector operator-(const Vector &, const Vector &);

///
/// Multiplicação de um vetor por um escalar.
/// @param Vector e escalar float
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
