#ifndef DSUH
#define DSUH

#include <iostream>
#include <string>
#include <vector>
using namespace std;

///
/// @file

///
/// Classe para Disjoint Set Union (DSU).
class DSU {
  public:
	///
	/// Construtor para DSU vazio.
	DSU();

	///
	/// Construtor para DSU pelo número de elementos.
	/// @param Número de elementos
	DSU(int);

	///
	/// Encontra representante do conjunto ao qual um elemento pretence.
	///
	/// Complexidade: O(invAckermann(n))
	/// @param Elemento.
	/// @return Representante do conjunto.
	int find(int);

	///
	/// Une dois conjuntos a partir de elementos dos mesmos.
	///
	/// Complexidade: O(invAckermann(n))
	/// @param Elemento 1
	/// @param Elemento 2
	void une(int, int);

  private:
	int n;
	vector<int> v;
	vector<int> sz;
};

///
/// Classe de exceções de DSU.
class DSUException : public exception {
  public:
	///
	/// Construtor para exceção do DSU.
	DSUException() {}
	///
	/// Retorna a mensagem de erro da exceção.
	/// @return Mensagem de erro.
	const char *what() const throw() { return "DSU Exception"; }
};

///
/// Classe de exceções de parâmetro negativo no construtor.
class DSUNegativeConstructorParameterException : public DSUException {
  public:
	///
	/// Construtor para exceção de parâmetro negativo.
	/// @param Valor inválido do parâmetro.
	DSUNegativeConstructorParameterException(int n) {
		msg = "constructor parameter cannot be negative; got " + to_string(n);
	}

	/// Retorna a mensagem de erro da exceção.
	/// @return Mensagem de erro.
	const char *what() const throw() { return msg.c_str(); }

  private:
	string msg;
};

///
/// Classe de exceções de valor fora do range válido.
class DSUValueOutOfBoundsException : public DSUException {
  public:
	///
	/// Construtor para exceção de valor fora do range válido.
	/// @param Valor inválido do parâmetro.
	DSUValueOutOfBoundsException(int n) {
		msg = "value out of bounds: " + to_string(n);
	}
	/// Retorna a mensagem de erro da exceção.
	/// @return Mensagem de erro.
	const char *what() const throw() { return msg.c_str(); }

  private:
	string msg;
};

#endif
