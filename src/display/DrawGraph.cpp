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
	float c1 = 20, c2 = 100, c3 = 50000, c4 = 0.1, c5 = 1000;
	
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
				if (!adj[i][j])  f = f - unit*(c3/(d*d));
				else             f = f + unit*(c1*log(d/(c2+G.n+G.m)));
			}

			// forca em relacao as paredes
			for (auto j : parede) {

				float d = dist(pos[i], j);
				Vector unit = (j - pos[i])*(1/d);

				// repulsao
				f = f - unit*(c5/(d*d));
			}

			forca.push_back(f);
		}

		// atualiza posicoes
		if (clique > -1) forca[clique] = Vector(0, 0);
		for (int i = 0; i < G.n; i++)
			pos[i] = deixaDentro(pos[i] + forca[i]*c4, MAXX, MAXY, raio);
	}
}

// Fruchterman algorithm
void fdp2(Graph &G, vector<Vector> &pos, int it, int MAXX, int MAXY) {
	if (pos.size() != G.n) {
		// TODO: Erro direito
		cout << "Erro: posicoes zoadas" << endl;
		return;
	}

	// calcula matriz de adjacencia
	// TODO: classe Graph calcular isso
	vector<vector<int> > adj(G.n, vector<int>(G.n, 0));
	for (int i = 0; i < G.n; i++) for (int j : G.adj[i]) adj[i][j] = adj[j][i] = 1;

	// constante do algoritmo
	float k = sqrt(MAXX*MAXY/float(G.n))/2;
	float t = min(MAXX, MAXY)/8.0;
	float delta = t/it;

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

	while (it--) {

		// forca aplicada a cada vertice
		vector<Vector> forca;

		for (int i = 0; i < G.n; i++) {
			Vector f(0, 0);

			for (int j = 0; j < G.n; j++) if (j != i) {

				float d = dist(pos[i], pos[j]);
				if (d < 1e-12) d = 1e-2;

				// vetor unitario na direcao de i para j
				Vector unit = (pos[j] - pos[i])*(1/d);

				// computa forca de acordo com o algoritmo
				if (d < 2*k)   f = f - unit*(k*k/d);
				if (adj[i][j]) f = f + unit*(d*d/k);
			}

			// forca em relacao as paredes
			for (auto j : parede) {

				float d = dist(pos[i], j);
				Vector unit = (j - pos[i])*(1/d);
				if (d < 1e-12) d = 1e-2;

				// repulsao
				if (d < k) f = f - unit*(k*k/d);
			}

			// limitante das forcas
			float disp = f.norm();
			if (disp > 1e-12) {
				f = f*(1/disp);
				f = f*min(disp, t);
			}

			forca.push_back(f);
		}

		// atualiza posicoes
		for (int i = 0; i < G.n; i++) pos[i] = pos[i] + forca[i];

		t = max((float)0, t-delta);
	}
}

// se os segmentos de reta interceptam
bool cruza(Vector a, Vector b, Vector c, Vector d) {
	if (cross(b-a, c-b)*cross(b-a, d-b) > 0) return 0;
	if (cross(d-c, a-d)*cross(d-c, b-d) > 0) return 0;
	return 1;
}

// numero de intersecoes de arestas
int inter(vector<Vector> &pos, Graph &G) {
	int ret = 0;
	for (auto &i : G.edges) for (auto &j : G.edges)
		if (cruza(pos[i.first], pos[i.second], pos[j.first], pos[j.second])) ret++;
	return ret;
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

vector<Vector> getRandom(Graph &G, int MAXX, int MAXY) {
	vector<Vector> pos;
	for (int i = 0; i < G.n; i++)
		pos.push_back(Vector((rand()%(MAXX-100))+50, (rand()%(MAXY-100)+50)));
	return pos;
}

vector<Vector> getGood(Graph &G, int MAXX, int MAXY, int randIt, int fdpIt) {
	int best = 10000000; vector<Vector> pos;
	while (randIt--) {
		vector<Vector> pos2 = getRandom(G, MAXX, MAXY);
		fdp2(G, pos2, fdpIt, MAXX, MAXY);

		int inters = inter(pos2, G);
		if (inters < best) {
			best = inters;
			pos = pos2;
		}
	}
	return pos;
}
