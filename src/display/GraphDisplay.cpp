#include "GraphDisplay.hpp"

#define EPS 1e-6

GraphDisplay::GraphDisplay(Graph G_, int X_, int Y_, int raio_) {
	G = G_;
	X = X_;
	Y = Y_;
	raio = raio_;
	temDir = 0, temPeso = 0, clique = -1;
	this->poligono();
	color = vector<int>(G.n, 0);
	posPeso = vector<float>(G.m, 0.5);
}

void GraphDisplay::fdpPeso(int it) {
	// constroi posicoes de fato
	vector<Vector> posPesoV;
	for (int i = 0; i < G.m; i++) {
		Vector v = pos[G.edges[i].second] - pos[G.edges[i].first];
		posPesoV.push_back(pos[G.edges[i].first] + v*posPeso[i]);
	}

	// constantes do algoritmo de Eades
	float c3 = 50000/(float)(1+G.n+G.m), c4 = 0.1;

	while (it--) {

		// forca aplicada a cada peso
		vector<Vector> forca;

		for (int i = 0; i < G.m; i++) {
			Vector f(0, 0);

			// forca em relacao aos vertices adjacentes
			for (int j = 0; j < 2; j++) {
				// escolhe um deles
				Vector v = pos[G.edges[i].first];
				if (j) v = pos[G.edges[i].second];

				float d = dist(posPesoV[i], v);
				if (d < EPS) d = EPS;

				// vetor unitario na direcao de i para j
				Vector unit = (v - posPesoV[i])*(1/d);

				// repulsao
				f = f - unit*(c3/(d*d));
			}

			// forca em relacao aos pesos
			for (int j = 0; j < G.m; j++) if (i != j) {
				float d = dist(posPesoV[i], posPesoV[j]);
				if (d < EPS) d = EPS;
				Vector unit = (posPesoV[j] - posPesoV[i])*(1/d);
				f = f - unit*(c3/(d*d));
			}

			// projeta a forca no vetor da aresta
			Vector ar = pos[G.edges[i].second] - pos[G.edges[i].first];
			f = f.project(ar);
			forca.push_back(f);
		}

		// atualiza posicoes
		for (int i = 0; i < G.m; i++) posPesoV[i] = posPesoV[i] + forca[i]*c4;
	}

	// transforma de volta para numeros
	posPeso = vector<float>();
	for (int i = 0; i < G.m; i++) {
		Vector v = pos[G.edges[i].second] - pos[G.edges[i].first];
		if (v.norm() < EPS) {
			posPeso.push_back(0.5);
			continue;
		}
		posPeso.push_back((posPesoV[i] - pos[G.edges[i].first]).norm() / v.norm());

		// para o peso ficar na aresta
		if (posPeso[i] < 0.1) posPeso[i] = 0.1;
		if (posPeso[i] > 0.9) posPeso[i] = 0.9;
	}
}

Vector GraphDisplay::deixaDentro(Vector v) {
	v.x = max(v.x, (float)raio+1);
	v.y = max(v.y, (float)raio+1);
	v.x = min(v.x, (float)X-raio-3);
	v.y = min(v.y, (float)Y-raio-3);
	return v;
}

// Eades algorithm
void GraphDisplay::fdp1(int it) {
	// calcula matriz de adjacencia
	// TODO: classe Graph calcular isso
	vector<vector<int> > adj(G.n, vector<int>(G.n, 0));
	for (int i = 0; i < G.n; i++) for (int j : G.adj[i]) adj[i][j] = adj[j][i] = 1;

	// constantes do algoritmo
	float c1 = 20, c2 = 100, c3 = 50000, c4 = 0.1, c5 = 1000;
	
	// paredes como vertices artificiais
	vector<Vector> parede;
	for (int i = 0; i <= X; i += 10) {
		parede.push_back(Vector(i, 0));
		parede.push_back(Vector(i, Y));
	}
	for (int i = 0; i <= Y; i += 10) {
		parede.push_back(Vector(0, i));
		parede.push_back(Vector(X, i));
	}

	// numero de iteracoes
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
				if (!adj[i][j])  f = f - unit*(c3/(d*d));
				else             f = f + unit*(c1*log(d/(c2+G.n+G.m)));
			}

			// forca em relacao as paredes
			for (auto j : parede) {

				float d = dist(pos[i], j);
				if (d < EPS) d = EPS;
				Vector unit = (j - pos[i])*(1/d);

				// repulsao
				f = f - unit*(c5/(d*d));
			}

			forca.push_back(f);
		}

		// atualiza posicoes
		if (clique > -1) forca[clique] = Vector(0, 0);
		for (int i = 0; i < G.n; i++)
			pos[i] = deixaDentro(pos[i] + forca[i]*c4);
	}
}

// Fruchterman algorithm
void GraphDisplay::fdp2(int it) {
	// calcula matriz de adjacencia
	// TODO: classe Graph calcular isso
	vector<vector<int> > adj(G.n, vector<int>(G.n, 0));
	for (int i = 0; i < G.n; i++) for (int j : G.adj[i]) adj[i][j] = adj[j][i] = 1;

	// constante do algoritmo
	float k = sqrt(X*Y/float(G.n))/2;
	float t = min(X, Y)/8.0;
	float delta = t/it;

	// paredes como vertices artificiais
	vector<Vector> parede;
	for (int i = 0; i <= X; i += 10) {
		parede.push_back(Vector(i, 0));
		parede.push_back(Vector(i, Y));
	}
	for (int i = 0; i <= Y; i += 10) {
		parede.push_back(Vector(0, i));
		parede.push_back(Vector(X, i));
	}

	while (it--) {

		// forca aplicada a cada vertice
		vector<Vector> forca;

		for (int i = 0; i < G.n; i++) {
			Vector f(0, 0);

			for (int j = 0; j < G.n; j++) if (j != i) {

				float d = dist(pos[i], pos[j]);
				if (d < EPS) d = EPS;

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
				if (d < EPS) d = EPS;

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
int GraphDisplay::inter() {
	int ret = 0;
	for (auto &i : G.edges) for (auto &j : G.edges)
		if (cruza(pos[i.first], pos[i.second], pos[j.first], pos[j.second])) ret++;
	return ret;
}

void GraphDisplay::poligono() {
	const float raioGrafo = (min(X, Y)-100)/2;
	Vector centro(X/2, Y/2);
	// angulo = 360/n
	const double theta = 2*acos(-1.0)/G.n;

	// numero impar de vertices tem que arredar um pouco
	if (G.n % 2 == 1) {
		float falta = raioGrafo - raioGrafo*cos(theta/2);
		centro = centro + Vector(0, falta/2);
	}

	pos = vector<Vector>();
	for (int i = 0; i < G.n; i++)
		pos.push_back(Vector(centro.x+sin(i*theta+theta/2)*raioGrafo,
			centro.y+cos(i*theta+theta/2)*raioGrafo));
}

void GraphDisplay::random() {
	pos = vector<Vector>();
	for (int i = 0; i < G.n; i++)
		pos.push_back(Vector((rand()%(X-100))+50, (rand()%(Y-100)+50)));
}

void GraphDisplay::good(int randIt, int fdpIt) {
	int best = 2*G.m*G.m+10;
	vector<Vector> posBest = vector<Vector>();
	while (randIt--) {
		this->random();
		this->fdp2(fdpIt);

		int inters = this->inter();
		if (inters < best) {
			best = inters;
			posBest = this->pos;
		}
	}
	this->pos = posBest;
}
