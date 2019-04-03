#include "DrawGraph.hpp"

Vector deixaDentro(Vector v, int X, int Y, float raio) {
	v.x = max(v.x, raio+1);
	v.y = max(v.y, raio+1);
	v.x = min(v.x, X-raio-1);
	v.y = min(v.y, Y-raio-1);
	return v;
}

// Eades algorithm
void fdp1(Graph &G, vector<Vector> &pos, int it, int clique, int MAXX, int MAXY, float raio) {
	if (pos.size() != G.n) {
		// TODO: Erro direito
		cout << "Erro: posicoes zoadas" << endl;
		return;
	}

	// calcula matriz de adjacencia
	// TODO: classe Graph calcular isso
	vector<vector<int> > adj(G.n, vector<int>(G.n, 0));
	for (int i = 0; i < G.n; i++) for (int j : G.adj[i]) adj[i][j] = adj[j][i] = 1;

	// constantes do algoritmo
	float c1 = 20, c2 = 100, c3 = 10, c4 = 0.1;
	
	// paredes como vertices artificiais
	vector<Vector> parede;
	for (int i = 0; i <= MAXX; i += 10) {
		parede.push_back(Vector(i, 0));
		parede.push_back(Vector(i, MAXY));
	}
	for (int i = 0; i <= MAXY; i += 10) {
		parede.push_back(Vector(0, i));
		parede.push_back(Vector(MAXX, i));
	}

	// numero de iteracoes
	while (it--) {

		// forca aplicada a cada vertice
		vector<Vector> forca;

		for (int i = 0; i < G.n; i++) {
			Vector f(0, 0);

			for (int j = 0; j < G.n; j++) if (j != i) {

				float d = dist(pos[i], pos[j]);

				// vetor unitario na direcao de i para j
				Vector unit = (pos[j] - pos[i])*(1/d);

				// computa forca de acordo com o algoritmo
				if (!adj[i][j])  f = f - unit*(5000*c3/(d*d));
				else             f = f + unit*(c1*log(d/(c2+G.n+G.m)));
			}

			// forca em relacao as paredes
			for (auto j : parede) {

				float d = dist(pos[i], j);
				Vector unit = (j - pos[i])*(1/d);

				// repulsao
				f = f - unit*(100*c3/(d*d));
			}

			forca.push_back(f);
		}

		// atualiza posicoes
		if (clique > -1) forca[clique] = Vector(0, 0);
		for (int i = 0; i < G.n; i++)
			pos[i] = deixaDentro(pos[i] + forca[i]*c4, MAXX, MAXY, raio);
	}
}

vector<Vector> getPoligono(Graph &G, int MAXX, int MAXY) {
	const float raioGrafo = (min(MAXX, MAXY)-100)/2;
	Vector centro(MAXX/2, MAXY/2);
	// angulo = 360/n
	const double theta = 2*acos(-1.0)/G.n;

	// numero impar de vertices tem que arredar um pouco
	if (G.n % 2 == 1) {
		float falta = raioGrafo - raioGrafo*cos(theta/2);
		centro = centro + Vector(0, falta/2);
	}

	vector<Vector> pos(G.n, Vector(0, 0));
	for (int i = 0; i < G.n; i++)
		pos[i] = Vector(centro.x+sin(i*theta+theta/2)*raioGrafo,
			centro.y+cos(i*theta+theta/2)*raioGrafo);
	
	return pos;
}
