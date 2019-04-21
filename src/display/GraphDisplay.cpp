#include "GraphDisplay.hpp"

#define EPS 1e-6

GraphDisplay::GraphDisplay(Graph G_, int X_, int Y_, int raio_) {
	G = G_;
	X = X_;
	Y = Y_;
	raio = raio_;
	temDir = temPeso = centr = draw = 0;
	this->poligono();
	vel = vector<Vector>(G.n, Vector(0, 0));
	para = vector<int>(G.n, 0);
	color = vector<int>(G.n, 0);
	posPeso = vector<float>(G.m, 0.5);

	isParal = vector<bool>(G.m, 0);
	// calcula matriz de adjacencia
	// TODO: classe Graph calcular isso
	vector<vector<int> > adj(G.n, vector<int>(G.n, 0));
	for (int i = 0; i < G.n; i++) for (int j : G.adj[i]) adj[i][j] = 1;
	for (int i = 0; i < G.m; i++) if (adj[G.edges[i].second][G.edges[i].first])
		isParal[i] = 1;
}

// encontra vertice na posicao 'at'
int GraphDisplay::achaVertice(Vector at) {
	for (int i = 0; i < G.n; i++)
		if (dist(at, pos[i]) < raio) return i;
	return -1;
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

Vector GraphDisplay::deixaDentro(Vector v, bool trav) {
	v.x = max(v.x, (float)raio+1+2*trav);
	v.y = max(v.y, (float)raio+1+2*trav);
	v.x = min(v.x, (float)X-raio-3-2*trav);
	v.y = min(v.y, (float)Y-raio-3-2*trav);
	return v;
}

bool GraphDisplay::taDentro(Vector v) {
	if (v.x < 0) return 0;
	if (v.x > X) return 0;
	if (v.y < 0) return 0;
	if (v.y > Y) return 0;
	return 1;
}

// Eades algorithm
void GraphDisplay::fdpEades(int it) {
	// calcula matriz de adjacencia
	// TODO: classe Graph calcular isso
	vector<vector<int> > adj(G.n, vector<int>(G.n, 0));
	for (int i = 0; i < G.n; i++) for (int j : G.adj[i]) adj[i][j] = adj[j][i] = 1;

	// constantes do algoritmo
	float c1 = 20, c2 = 100, c3 = 50000, c4 = 0.1, c5 = 10000;
	
	// numero de iteracoes
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
				if (!adj[i][j])  f = f - unit*(c3/(d*d));
				else             f = f + unit*(c1*log(d/(c2+G.n+G.m)));
			}

			// forca em relacao as paredes
			vector<Vector> parede = {Vector(0, pos[i].y), Vector(X, pos[i].y),
							  Vector(pos[i].x, 0), Vector(pos[i].x, Y)};
			for (auto j : parede) {
				float d = dist(pos[i], j);
				if (d < EPS) d = EPS;
				Vector unit = (j - pos[i])*(1/d);
				f = f - unit*(c5/(d*d));
			}

			forca.push_back(f);
		}

		// atualiza posicoes
		for (int i = 0; i < G.n; i++) if (!para[i])
			pos[i] = deixaDentro(pos[i] + forca[i]*c4, (para[i] > 1));
	}
}

// Eades algorithm with acceleration
void GraphDisplay::fdpEadesAcc(int it) {
	// calcula matriz de adjacencia
	// TODO: classe Graph calcular isso
	vector<vector<int> > adj(G.n, vector<int>(G.n, 0));
	for (int i = 0; i < G.n; i++) for (int j : G.adj[i]) adj[i][j] = adj[j][i] = 1;

	// constantes do algoritmo
	float c1 = 20, c2 = 100, c3 = 50000, c4 = 0.1, c5 = 10000;
	
	// numero de iteracoes
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
				if (!adj[i][j])  f = f - unit*(c3/(d*d));
				else             f = f + unit*(c1*log(d/(c2+G.n+G.m)));
			}

			// forca em relacao as paredes
			vector<Vector> parede = {Vector(0, pos[i].y), Vector(X, pos[i].y),
							  Vector(pos[i].x, 0), Vector(pos[i].x, Y)};
			for (auto j : parede) {
				float d = dist(pos[i], j);
				if (d < EPS) d = EPS;
				Vector unit = (j - pos[i])*(1/d);
				f = f - unit*(c5/(d*d));
			}

			// forca dissipativa
			Vector dis = vel[i]*(-0.2);
			f = f + dis;

			forca.push_back(f);
		}

		// atualiza velocidade
		for (int i = 0; i < G.n; i++) vel[i] = vel[i] + forca[i]*c4;
		for (int i = 0; i < G.n; i++) if (para[i]) vel[i] = Vector(0, 0);

		// atualiza posicoes
		for (int i = 0; i < G.n; i++)
			pos[i] = deixaDentro(pos[i] + vel[i], (para[i] > 1));
	}
}

// Fruchterman algorithm
void GraphDisplay::fdpFruchterman(int it) {
	// calcula matriz de adjacencia
	// TODO: classe Graph calcular isso
	vector<vector<int> > adj(G.n, vector<int>(G.n, 0));
	for (int i = 0; i < G.n; i++) for (int j : G.adj[i]) adj[i][j] = adj[j][i] = 1;

	// constante do algoritmo
	float k = sqrt(X*Y/float(G.n))/2;
	float t = min(X, Y)/8.0;
	float delta = t/it;

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

			// limitante das forcas
			float disp = f.norm();
			if (disp > EPS) {
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
	for (int i = 0; i < randIt; i++) {
		this->random();
		this->fdpFruchterman(fdpIt);

		int inters = this->inter();
		if (inters < best) {
			best = inters;
			posBest = this->pos;
		}
	}
	this->pos = posBest;
	this->fdpEades(randIt*fdpIt/4);
	this->fdpEadesAcc(randIt*fdpIt/4);
}

void GraphDisplay::addVertex(Vector v) {
	Graph G2(G.n+1, G.label);
	pos.push_back(v);
	vel.push_back(Vector(0, 0));
	para.push_back(0);
	color.push_back(0);
	for (auto i : G.edges) G2.addEdge(i.first, i.second);
	G = G2;
}

void GraphDisplay::removeVertex(int v) {
	G.label.erase(G.label.begin()+v);
	Graph G2(G.n-1, G.label);
	pos.erase(pos.begin()+v);
	vel.erase(vel.begin()+v);
	para.erase(para.begin()+v);
	color.erase(color.begin()+v);

	int erased = 0;
	for (int i = 0; i < G.m; i++) {
		int a = G.edges[i].first, b = G.edges[i].second;
		if (a == v or b == v) {
			if (temPeso) {
				peso.erase(peso.begin()+i-erased);
				posPeso.erase(posPeso.begin()+i-erased);
			}
			isParal.erase(isParal.begin()+i-erased);
			erased++;
			continue;
		}
		if (a > v) a--;
		if (b > v) b--;
		G2.addEdge(a, b);
	}
	G = G2;
}

void GraphDisplay::addEdge(int a, int b) {
	for (int i : G.adj[a]) if (i == b) return;
	G.addEdge(a, b);
	posPeso.push_back(0.5);
	isParal.push_back(0);
	for (int i : G.adj[b]) if (i == a) {
		isParal[G.m-1] = 1;
		for (int j = 0; j < G.m; j++) if (G.edges[j].first == b and G.edges[j].second == a)
			isParal[j] = 1;
	}
	if (temPeso) peso.push_back("1");
}

void GraphDisplay::removeEdge(int e) {
	int a = G.edges[e].first, b = G.edges[e].second;
	for (int i = 0; i < G.adj[a].size(); i++)
		if (G.adj[a][i] == b) {
			G.adj[a].erase(G.adj[a].begin()+i);
			break;
		}
	G.edges.erase(G.edges.begin()+e);
	posPeso.erase(posPeso.begin()+e);
	isParal.erase(isParal.begin()+e);
	for (int i = 0; i < G.m; i++) if (G.edges[i].first == b and G.edges[i].second == a)
		isParal[i] = 0;
	if (temPeso) peso.erase(peso.begin()+e);
	G.m--;
}

void GraphDisplay::itera() {
	if (draw) return;

	if (centr) fdpEadesAcc(2);
	else  fdpEades(2);
	if (temPeso) fdpPeso(2);
}
