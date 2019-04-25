#include "Interface.hpp"


int findFontSize(int n, int fontSize){	//acha o tamanho da fonte
	if (n < 2) return fontSize;
	else if (n < 3) return fontSize-6;
	else if (n< 4) return fontSize-10;
	else if (n < 5) return fontSize-14;
	else return fontSize-10;
}

int findFontSizeNew(int biggest, int fontSize, sf::Font &fonte, int raio) {
	sf::Text aux;
	aux.setFont(fonte);
	string st = "";
	for (int i = 0; i < biggest; ++i) st = st +'0';
	aux.setString(st);
	aux.setCharacterSize(fontSize);
	sf::FloatRect boundingBox = aux.getLocalBounds();
	int i = fontSize;
	for(; boundingBox.width >= raio+4 && i > 0; i--) {
		aux.setCharacterSize(i);
		boundingBox = aux.getLocalBounds();
		//printf("%.2f && %.2f -- %d\n", boundingBox.width, boundingBox.height, raio);
	}
	fontSize = i;
	//printf("%lf -- %d\n", boundingBox.width, raio);
	//printf("big = %d ... size = %d\n", biggest, fontSize);
	return fontSize;
}
sf::Color getColor(int x) {
	if (x == 0) return sf::Color::White;
	if (x == 1) return sf::Color::Red;
	if (x == 2) return sf::Color::Green;
	if (x == 3) return sf::Color::Blue;
	if (x == 4) return sf::Color::Yellow;
	if (x == 5) return sf::Color::Magenta;
	if (x == 6) return sf::Color::Cyan;
	return sf::Color::Black;
}

void drawAresta(sf::RenderWindow &janela, GraphDisplay &GD, Vector at, int aresta) {
	auto position = sf::Mouse::getPosition(janela);
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

	janela.draw(linha, 2, sf::Lines);

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
		janela.draw(tri);
	}
}

void printGrafo(sf::RenderWindow &janela, sf::Font &fonte, GraphDisplay &GD, int biggest) {

	// Cria as arestas
	for (int i = 0; i < GD.G.m; i++) {
		// Arestas sem largura, por isso vetores
		Vector add(0, 0);
		if (GD.isParal[i]) {
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

		janela.draw(linha, 2, sf::Lines);
	}
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
		janela.draw(v);

		// Coloca texto dentro da bola
		sf::Text label;
		label.setFont(fonte);
		label.setString(GD.G.label[i]);
		//parte nova
		label.setCharacterSize(findFontSizeNew(biggest, 24, fonte, GD.raio));
		//label.setCharacterSize(findFontSize(biggest, 24)); // fontSize default = 24 --> parte subst
		label.setFillColor(sf::Color::Black);


		//sf::FloatRect boundingBox = label.getGlobalBounds(); //rect minimum
		//cout << "BoB " <<  G.label[i] << " = "<< boundingBox.width << '\n';	//printa a largura minima de  cd vértice
		label.setPosition(GD.pos[i].x+9-15, GD.pos[i].y-15);	//TODO mudar posição
		janela.draw(label);
	}
}

// eu sou mt bom com vetores
void printSetas(sf::RenderWindow &janela, GraphDisplay &GD) {
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
		janela.draw(tri);
	}
}

void printPesos(sf::RenderWindow &janela, sf::Font &fonte, GraphDisplay &GD) {

	for (int i = 0; i < GD.G.m; i++) {
		sf::Text p;
		p.setFont(fonte);
		p.setString(GD.peso[i]);
		p.setCharacterSize(findFontSize(GD.peso[i].size(), 24));
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

		p.setPosition(at.x+add.x, at.y+add.y);
		janela.draw(p);
	}
}

void lerGrafoArquivo(tgui::EditBox::Ptr arq, GraphDisplay *GD, int *biggest) {
	ifstream inFile(arq->getText().toAnsiString());
	if (!inFile) {
		// TODO: Erro direito
		cout << "Erro: arquivo zoado" << endl;
		return;
	}

	int n, m;
	inFile >> n >> m;
	vector<string> label(n);
	for (auto &i : label) inFile >> i;

	*biggest = 0;
	for (int i = 0; i < n; ++i)
		if(label[i].length() > *biggest)
			*biggest = label[i].length();
	//printf(" ler grafo arq = %d\n", *biggest); 	//maior length no grafo

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

	bool temDir = GD->temDir;
	*GD = GraphDisplay(G, GD->X, GD->Y, GD->raio);
	GD->temDir = temDir;
	GD->temPeso = temPeso;
	if (GD->temPeso) GD->peso = peso;

	GD->good(max(10, 100 - GD->G.n), max(10, 100 - GD->G.m));

	inFile.close();
}

void mudaDir(GraphDisplay *GD) {
	(GD->temDir) ^= 1;
}

void centraliza(GraphDisplay *GD) {
	(GD->centr) ^= 1;
}

void loadWidgets(tgui::Gui &gui, GraphDisplay *GD, int *biggest) {
	tgui::Theme tema{"assets/TransparentGrey.txt"};
	//tgui::ButtonRenderer(tema.getRenderer("button")).setBackgroundColor(sf::Color::Blue);
	tgui::Theme::setDefault(&tema);

	// Caixa de texto para o arquivo
	auto textoArquivo = tgui::EditBox::create();
	textoArquivo->setSize(200.f, 20.f);
	textoArquivo->setPosition(820.f, 200.f);
	textoArquivo->setDefaultText("Nome do arquivo");
	gui.add(textoArquivo);

	// Lista de tipos de grafos
	auto lista = tgui::ListBox::create();
	lista->setSize(150.f, 55.f);
	lista->setPosition(1030.f, 200.f);
	lista->setItemHeight(20);
	lista->addItem(L"Grafo generico");
	lista->addItem(L"Cordal generico");
	lista->addItem(L"Arvore");
	gui.add(lista);

	// Check box de se tem peso ou não
	auto check = tgui::CheckBox::create("Direcionado");
	check->setSize(20.f, 20.f);
	check->setPosition(820.f, 235.f);
	gui.add(check);

	// Botao pra ler arquivo
	auto botaoArquivo = tgui::Button::create("Importar");
	botaoArquivo->setSize(75.f, 20.f);
	botaoArquivo->setPosition(930.f, 235.f);
	gui.add(botaoArquivo);

	// botao pra centralizar grafo
	auto botaoCenter = tgui::Button::create("Centralizar");
	botaoCenter->setSize(75.f, 20.f);
	botaoCenter->setPosition(930.f, 260.f);
	gui.add(botaoCenter);

	// Chama a função de importar arquivo
	botaoArquivo->connect(
			"pressed", lerGrafoArquivo, textoArquivo, GD, biggest);

	check->connect(
			"checked", mudaDir, GD);
	check->connect(
			"unchecked", mudaDir, GD);

	botaoCenter->connect(
			"pressed", centraliza, GD);
}

// muitos ifs
void handleClique(sf::RenderWindow &janela, GraphDisplay &GD) {
	static Vector dif;
	static int clique = -2;
	static Vector ini;
	static int aresta = -1;

	auto position = sf::Mouse::getPosition(janela);
	Vector positionV(position.x, position.y);

	// desenha aresta pela metade
	if (aresta > -1 and GD.draw) drawAresta(janela, GD, positionV, aresta);

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

void drawStuff(sf::RenderWindow &janela, sf::Font &fonte) {
	// Limpa tela e coloca branco
	janela.clear(sf::Color::White);

	// Parte cinza
	sf::RectangleShape menu(
			sf::Vector2f(400.f,600.f));
	menu.setFillColor(sf::Color(192,192,192));
	menu.setPosition(800.f, 0.f);
	janela.draw(menu);

	// Divisão entre o canvas e o menu
	sf::Vertex linha1[] =
	{
		sf::Vertex(sf::Vector2f(800,0),
				sf::Color::Black),

		sf::Vertex(sf::Vector2f(800,600),
				sf::Color::Black)
	};
	janela.draw(linha1, 2, sf::Lines);

	// Divisão entre instruções e import
	sf::Vertex linha2[] =
	{
		sf::Vertex(sf::Vector2f(830,170),
				sf::Color(130,130,130)),

		sf::Vertex(sf::Vector2f(1170,170),
				sf::Color(130,130,130))
	};
	janela.draw(linha2, 2, sf::Lines);

	// Divisão entre import e algoritmos
	sf::Vertex linha3[] =
	{
		sf::Vertex(sf::Vector2f(830,285),
				sf::Color(130,130,130)),

		sf::Vertex(sf::Vector2f(1170,285),
				sf::Color(130,130,130))
	};
	janela.draw(linha3, 2, sf::Lines);

	// Instruções
	sf::Text instr;
	instr.setFont(fonte);
	instr.setString(L"Instruções:");
	instr.setCharacterSize(32);
	instr.setFillColor(sf::Color::Black);
	instr.setPosition(830, 5);
	janela.draw(instr);

	// Instruções de fato...
	instr.setString(L"1) ...\n2) ...\n3) ...");
	instr.setCharacterSize(18);
	instr.setFillColor(sf::Color(130,130,130));
	instr.setPosition(820, 55);
	janela.draw(instr);
}

void displayTeste(int X, int Y) {

	// Carrega a fonte Consola Bold (Gosto dela)
	sf::Font fonte;
	if (!fonte.loadFromFile("assets/CONSOLAB.TTF")) {
		// TODO: Erro direito
		return;
	}

	// Antialiasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Cria a janela
	sf::RenderWindow janela(sf::VideoMode(X, Y), "graphODA", sf::Style::Close, settings);
	janela.setKeyRepeatEnabled(false);
	tgui::Gui gui(janela);

	// GraphDisplay
	GraphDisplay GD(Graph(), X*2/3, Y, 15);

	int biggest = 0; //maior string

	// Tenta importar os widgets da gui
	try {
		loadWidgets(gui, &GD, &biggest);
	} catch (const tgui::Exception &e) {
		// TODO: mensagem de erro
		return;
	}
	// "Main Loop"
	// Roda o programa enquanto a janela estiver aberta

	while (janela.isOpen()) {
		// Checa se algum evento aconteceu
		sf::Event evento;
		while (janela.pollEvent(evento)) {
			// Se pediu pra fechar
			if(evento.type == sf::Event::Closed)
				janela.close();

			// Cria os widgets da GUI
			gui.handleEvent(evento);

			// testa se apertou ctrl
			if (evento.type == sf::Event::KeyPressed and
						evento.key.code == sf::Keyboard::LControl) {
				GD.draw ^= 1;
			}
		}

		drawStuff(janela, fonte);

		// olha se a pessoa ta mexendo no vertice
		handleClique(janela, GD);

		// faz mais iteracoes da mola e printa o grafo
		GD.itera();
		if (GD.temPeso) printPesos(janela, fonte, GD);
		if (GD.temDir) printSetas(janela, GD);
		printGrafo(janela, fonte, GD, biggest);
	
		gui.draw();

		// Termina iteração e atualiza janela
		janela.display();
	}
}
