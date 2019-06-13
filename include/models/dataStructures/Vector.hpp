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
	/// @param Inteiros x e y correspondentes às posições do vetor.
	Vector(float, float);

	///
	/// Construtor do vetor por par de posições.
	/// @param pair que corresponde às posições do vetor.
	Vector(pair<float, float>);

	///
	/// Calcula a norma do vetor.
	/// @return Norma do vetor.
	float norm();

	///
	/// Calcula o ângulo do vetor com o eixo x.
	/// @return Ãngulo do vetor com o eixo x.
	float angle();

	///
	/// Rotaciona o vetor em um dado ângulo.
	/// @param float do ângulo de rotação.
	/// @return O Vector rotacionado.
	Vector rotate(float);

	///
	/// Projeção do vetor sobre um outro vetor.
	/// @param Vector no qual se deseja projetar.
	/// @return Vector projetado.
	Vector project(Vector);
};

///
/// Soma de vetores.
/// @param Vetores a serem somados.
/// @return Vector resultante.
Vector operator+(const Vector &, const Vector &);

///
/// Subtração de vetores.
/// @param Vetores a serem subtraídos.
/// @return Vector resultante.
Vector operator-(const Vector &, const Vector &);

///
/// Multiplicação de um vetor por um escalar.
/// @param Vector a ser multiplicado.
/// @param Escalar a se multiplicar.
/// @return Vector resultante.
Vector operator*(const Vector &, const float);

///
/// Produto escalar entre vetores.
/// @param Vetores a serem multiplicados.
/// @return Vector resultante.
float operator*(const Vector &, const Vector &);

///
/// Produto vetorial entre vetores.
/// @param Vetores a serem multiplicados.
/// @return Vector resultante.
float operator%(const Vector &, const Vector &);

///
/// Distância normalizada entre vetores.
/// @param Vetores a se calcular a distância.
/// @return Distância entre eles.
float operator^(const Vector &, const Vector &);

#endif
