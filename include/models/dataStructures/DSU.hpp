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
	/// @param número de elementos
	DSU(int);

	///
	/// Encontra representante do conjunto ao qual um elemento pretence.
	/// Complexidade: O(invAckermann(n))
	/// @param inteiro que representa um elemento
	/// @return inteiro que indica o representante do conjunto
	int find(int);

	///
	/// Une dois conjuntos a partir de elementos dos mesmos.
	///
	/// Complexidade: O(invAckermann(n))
	/// @param elemento 1
	/// @param elemento 2
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
	DSUException() {}
	///
	/// @return a mensagem de erro da exceção.
	const char *what() const throw() { return "DSU Exception"; }
};

///
/// Classe de exceções de parâmetro negativo no construtor.
class DSUNegativeConstructorParameterException : public DSUException {
  public:
	///
	/// Construtor para exceção de parâmetro negativo.
	DSUNegativeConstructorParameterException(int n) {
		msg = "constructor parameter cannot be negative; got " + to_string(n);
	}

	/// @param inteiro negativo que corresponde ao número de elementos
	/// @return a mensagem de erro da exceção.
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
	DSUValueOutOfBoundsException(int n) {
		msg = "value out of bounds: " + to_string(n);
	}
	/// @param inteiro n fora do range
	/// @return mensagem de erro da exceção.
	const char *what() const throw() { return msg.c_str(); }

  private:
	string msg;
};

#endif
