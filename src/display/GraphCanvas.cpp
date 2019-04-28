#include "GraphCanvas.hpp"

GraphCanvas::GraphCanvas(sf::RenderWindow &janela, sf::Font &fonte, int X, int Y, int raio) {
	this->janela = &janela;
	this->fonte = fonte;
	this->GD = GraphDisplay(Graph(), X, Y, raio);
}

int GraphCanvas::findFontSize(int n, int fontSize) {
	if (n < 2) return fontSize;
	else if (n < 3) return fontSize-6;
	else if (n < 4) return fontSize-10;
	else if (n < 5) return fontSize-14;
	else return fontSize-10;
}

sf::Color GraphCanvas::getColor(int x) {
	if (x == 0) return sf::Color::White;
	if (x == 1) return sf::Color::Red;
	if (x == 2) return sf::Color::Green;
	if (x == 3) return sf::Color::Blue;
	if (x == 4) return sf::Color::Yellow;
	if (x == 5) return sf::Color::Magenta;
	if (x == 6) return sf::Color::Cyan;
	return sf::Color::Black;
}

int GraphCanvas::findFontSizeNew(int fontSize, int biggest) {
	sf::Text aux;
	aux.setFont(fonte);
	string st = "";
	for (int i = 0; i < biggest; ++i) st = st +'0';
	aux.setString(st);
	aux.setCharacterSize(fontSize);
	sf::FloatRect boundingBox = aux.getLocalBounds();
	int i = fontSize;
	for(; boundingBox.width >= GD.raio+4 && i > 0; i--) {
		aux.setCharacterSize(i);
		boundingBox = aux.getLocalBounds();
		//printf("%.2f && %.2f -- %d\n", boundingBox.width, boundingBox.height, raio);
	}
	fontSize = i;
	//printf("%lf -- %d\n", boundingBox.width, raio);
	//printf("big = %d ... size = %d\n", biggest, fontSize);
	return fontSize;
}

void GraphCanvas::printAresta(Vector at, int aresta) {
	auto position = sf::Mouse::getPosition(*janela);
	Vector positionV(position.x, position.y);
	positionV = GD.deixaDentro(positionV, 0);

	sf::Vertex linha[] =
	{
		sf::Vertex(sf::Vector2f(
			positionV.x, positionV.y),
				sf::Color::Black),

		sf::Vertex(sf::Vector2f(
			GD.pos[aresta].x, GD.pos[aresta].y),
				sf::Color::Black)
	};

	janela->draw(linha, 2, sf::Lines);

	if (GD.temDir) {
		const float pi = acos(-1.0);

		Vector fim = positionV;
		Vector v = fim - GD.pos[aresta];
		Vector unit = v*(1/v.norm());

		Vector pos = fim - unit*GD.raio*0.5;

		// angulo que tem que rodar pra seta ficar certa
		float angle = v.angle()-pi/6;

		Vector delta = Vector(GD.raio/2-1, GD.raio/2-1).rotate(angle)
				- Vector(GD.raio/2-1, GD.raio/2-1);

		// arreda um pouqinho a seta se ta dentro do vertice
		float add = 0;
		int achaAt = GD.achaVertice(at);
		if (achaAt > -1 and achaAt != aresta) {
			Vector yv = GD.pos[GD.achaVertice(at)] - at;
			float y = yv.norm();

			float alpha = (GD.pos[aresta]-at).angle() - yv.angle();

			// lei dos cossenos mt louca
			add = y*cos(alpha) + sqrt(GD.raio*GD.raio - y*y*sin(alpha)*sin(alpha));
		}

		Vector addV = v*(1/v.norm())*(-add);

		// cria triangulo na ponta da aresta
		sf::CircleShape tri(GD.raio/2, 3);
		tri.setRotation((angle)*180/pi);
		tri.setFillColor(sf::Color::Black);
		tri.setPosition(pos.x-GD.raio/2+1-delta.x+addV.x, pos.y-GD.raio/2+1-delta.y+addV.y);
		janela->draw(tri);
	}	
}

void GraphCanvas::printGrafo() {
	// Cria as arestas
	for (int i = 0; i < GD.G.m; i++) {
		// Arestas sem largura, por isso vetores
		Vector add(0, 0);
		if (GD.isParal[i] and GD.temDir) {
			add = GD.pos[GD.G.edges[i].second] - GD.pos[GD.G.edges[i].first];
			if (add.norm()) {
				add = add*(1/add.norm());
				add = add.rotate(acos(-1.0)/2);
				add = add*(GD.raio/3.0);
			}
		}
		sf::Vertex linha[] =
		{
			sf::Vertex(sf::Vector2f(
				GD.pos[GD.G.edges[i].first].x+add.x, GD.pos[GD.G.edges[i].first].y+add.y),
					sf::Color::Black),

			sf::Vertex(sf::Vector2f(
				GD.pos[GD.G.edges[i].second].x+add.x, GD.pos[GD.G.edges[i].second].y+add.y),
					sf::Color::Black)
		};

		janela->draw(linha, 2, sf::Lines);
	}

	// encontra tamanho da fonte
	int fontSize = 10000;
	for (auto& i : GD.G.label) fontSize = min(fontSize, findFontSize(i.size(), 24));

	// Cria os vértices
	for (int i = 0; i < GD.G.n; i++) {
		// Cria um círculo
		sf::CircleShape v(GD.raio);
		v.setFillColor(getColor(GD.color[i]));

		// vertice travado
		if (GD.para[i] > 1) v.setOutlineThickness(4.f);
		else v.setOutlineThickness(2.f);

		v.setOutlineColor(sf::Color::Black);
		v.setPosition(GD.pos[i].x-GD.raio+1, GD.pos[i].y-GD.raio+1);
		janela->draw(v);

		// Coloca texto dentro da bola
		sf::Text label;
		label.setFont(fonte);
		label.setString(GD.G.label[i]);
		label.setCharacterSize(fontSize);
		label.setFillColor(sf::Color::Black);

		// centraliza texto
		sf::FloatRect box = label.getLocalBounds();
		label.setOrigin(box.left + round(box.width/2), box.top + round(box.height/2));
		label.setPosition(GD.pos[i].x, GD.pos[i].y);
		janela->draw(label);
	}
}

// eu sou mt bom com vetores
void GraphCanvas::printSetas() {
	const float pi = acos(-1.0);

	for (int i = 0; i < GD.G.m; i++) {
		Vector fim = GD.pos[GD.G.edges[i].second];
		Vector v = fim - GD.pos[GD.G.edges[i].first];
		Vector unit = v*(1/v.norm());

		Vector pos = fim - unit*GD.raio*1.6;
		// se ta travado arreda um pouco a seta
		if (GD.para[GD.G.edges[i].second] > 1)
			pos = pos - unit*2;

		// angulo que tem que rodar pra seta ficar certa
		float angle = v.angle()-pi/6;

		Vector delta = Vector(GD.raio/2-1, GD.raio/2-1).rotate(angle)
				- Vector(GD.raio/2-1, GD.raio/2-1);

		// trata aresta paralelas
		Vector add(0, 0);
		if (GD.isParal[i]) {
			add = GD.pos[GD.G.edges[i].second] - GD.pos[GD.G.edges[i].first];
			if (add.norm()) {
				add = add*(1/add.norm());
				add = add.rotate(acos(-1.0)/2);
				add = add*(GD.raio/3.0);
			}
		}

		// cria triangulo na ponta da aresta
		sf::CircleShape tri(GD.raio/2, 3);
		tri.setRotation((angle)*180/pi);
		tri.setFillColor(sf::Color::Black);
		tri.setPosition(pos.x-GD.raio/2+1-delta.x+add.x, pos.y-GD.raio/2+1-delta.y+add.y);
		janela->draw(tri);
	}
}

void GraphCanvas::printPesos() {
	int fontSize = 10000;
	for (auto& i : GD.peso) fontSize = min(fontSize, findFontSize(i.size(), 24));

	for (int i = 0; i < GD.G.m; i++) {
		sf::Text p;
		p.setFont(fonte);
		p.setString(GD.peso[i]);
		p.setCharacterSize(fontSize);
		p.setFillColor(sf::Color::Black);

		// acha posicao
		Vector v = GD.pos[GD.G.edges[i].second] - GD.pos[GD.G.edges[i].first];
		Vector at = GD.pos[GD.G.edges[i].first] + v*GD.posPeso[i];

		// arestas paralelas
		Vector add(0, 0);
		if (GD.isParal[i]) {
			add = GD.pos[GD.G.edges[i].second] - GD.pos[GD.G.edges[i].first];
			if (add.norm()) {
				add = add*(1/add.norm());
				add = add.rotate(acos(-1.0)/2);
				add = add*(GD.raio/3.0);
			}
		}

		sf::FloatRect box = p.getLocalBounds();
		p.setOrigin(box.left + round(box.width/2), box.top + round(box.height/2));
		p.setPosition(at.x+add.x, at.y+add.y);
		p.setOutlineColor(sf::Color::White);
		p.setOutlineThickness(2.0);
		janela->draw(p);
	}
}

void GraphCanvas::lerGrafoArquivo(string arq) {
	ifstream inFile(arq);
	if (!inFile) {
		inFile = ifstream("grafos/grafo"+arq+".txt");
		if (!inFile) {
			// TODO: Erro direito
			cout << "Erro: arquivo zoado" << endl;
			return;
		}
	}

	int n, m;
	inFile >> n >> m;
	vector<string> label(n);
	for (auto &i : label) inFile >> i;

	Graph G(n, label);

	// verfica se tem peso ou nao
	string l;
	inFile.ignore();
	getline(inFile, l);
	stringstream ss(l);
	vector<int> entrada;
	for (int i; ss >> i;) entrada.push_back(i);
	bool temPeso = 0; vector<string> peso;
	if (entrada.size() == 3) {
		temPeso = 1;
		peso.push_back(to_string(entrada.back()));
	}
	G.addEdge(entrada[0], entrada[1]);

	for (int i = 0; i < m-1; i++) {
		int a, b; inFile >> a >> b;
		G.addEdge(a, b);
		if (temPeso) {
			string p; inFile >> p;
			peso.push_back(p);
		}
	}

	GD.setGraph(G);
	GD.temPeso = temPeso;
	if (GD.temPeso) GD.peso = peso;

	GD.good(max(10, 100 - GD.G.n), max(10, 100 - GD.G.m));

	inFile.close();
}

// muitos ifs
void GraphCanvas::handleClique() {
	static Vector dif;
	static int clique = -2;
	static Vector ini;
	static int aresta = -1;

	auto position = sf::Mouse::getPosition(*janela);
	Vector positionV(position.x, position.y);

	if (!GD.taDentro(positionV)) {
		aresta = -1;
		return;
	}

	// desenha aresta pela metade
	if (aresta > -1 and GD.draw) printAresta(positionV, aresta);

	// testa clique
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		// ta no modo draw
		if (GD.draw) {
			// acabei de clicar
			if (clique == -2) {
				ini = positionV;
				clique = GD.achaVertice(positionV);	
				if (clique == -1 and GD.taDentro(positionV))
					GD.addVertex(positionV), aresta = -2;
				else if (clique > -1)
					dif = GD.pos[clique] - positionV, GD.centr = 0;
			}
		}

		// acabei de clicar
		if (clique == -2) {
			ini = positionV;
			clique = GD.achaVertice(positionV);
			if (clique > -1) {
				GD.centr = 0;
				dif = GD.pos[clique] - positionV;
				GD.para[clique]++;
			}
		}

		// move vertice
		if (clique > -1)
			GD.pos[clique] = GD.deixaDentro(positionV + dif, (GD.para[clique] > 1));
	}
	else if (clique > -2) { // soltei
		// testa se tem que travar vertice ou iniciar aresta
		if (ini.x == positionV.x and ini.y == positionV.y) {
			int vert = GD.achaVertice(positionV);
			if (vert > -1) {
				if (!GD.draw) { // trava
					if (GD.para[vert] >= 2) GD.para[vert] -= 2;
					else GD.para[vert] += 2;
				} else { // desenha aresta
					if (aresta == -1) aresta = vert;
					else {
						if (aresta > -1 and aresta != vert)
							GD.addEdge(aresta, vert);
						aresta = -1;
					}
				}
			} else aresta = -1;
		}

		if (!GD.draw and clique > -1) GD.para[clique]--;
		clique = -2;
	}

	// clique com o botao direito
	if (GD.draw and sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		// acabei de clicar
		if (clique == -2) {
			clique = GD.achaVertice(positionV);
			if (clique > -1) {
				if (clique == aresta) aresta = -1;
				GD.removeVertex(clique);
			} else {
				// tenta encontrar aresta clicada
				for (int i = 0; i < GD.G.m; i++) {
					Vector ini = GD.pos[GD.G.edges[i].first],
							fim = GD.pos[GD.G.edges[i].second];

					Vector add(0, 0);
					if (GD.isParal[i]) {
						add = GD.pos[GD.G.edges[i].second] - GD.pos[GD.G.edges[i].first];
						if (add.norm()) {
							add = add*(1/add.norm());
							add = add.rotate(acos(-1.0)/2);
							add = add*(GD.raio/3.0);
						}
					}

					ini = ini+add;
					fim = fim+add;

					if ((positionV-ini).norm() + (fim-positionV).norm() - 0.5
							< (fim-ini).norm()) {
						GD.removeEdge(i);
						break;
					}
				}
			}
		}
	}
}

void GraphCanvas::display() {
	GD.itera();
	if (GD.temDir) printSetas();
	printGrafo();
	if (GD.temPeso) printPesos();
}
