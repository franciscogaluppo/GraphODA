#include "Interface.hpp"

int findFontSize(int n, int fontSize){	//acha o tamanho da fonte
	if (n < 10) return fontSize;
	else if (n < 100) return fontSize-4;
	else return fontSize-6;
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

void printGrafo(sf::RenderWindow &janela, sf::Font &fonte, Graph &G, vector<Vector> &pos, vector<int> &color, int raio) {

	// Cria as arestas
	for (int i = 0; i < G.m; i++) {
		// Arestas sem largura, por isso vetores
		sf::Vertex linha[] =
		{
			sf::Vertex(sf::Vector2f(
				pos[G.edges[i].first].x, pos[G.edges[i].first].y),
					sf::Color::Black),

			sf::Vertex(sf::Vector2f(
				pos[G.edges[i].second].x, pos[G.edges[i].second].y),
					sf::Color::Black)
		};

		janela.draw(linha, 2, sf::Lines);
	}

	// Cria os vértices
	for (int i = 0; i < G.n; i++) {
		// Cria um círculo
		sf::CircleShape v(raio);
		v.setFillColor(getColor(color[i]));
		v.setOutlineThickness(2.f);
		v.setOutlineColor(sf::Color::Black);
		v.setPosition(pos[i].x-raio+1, pos[i].y-raio+1);
		janela.draw(v);

		// Coloca texto dentro da bola
		sf::Text label;
		label.setFont(fonte);
		label.setString(G.label[i]);
		int fontSize = findFontSize(G.n, 24);	// fontSize default = 24
		label.setCharacterSize(fontSize); //tamanho fonte
		label.setFillColor(sf::Color::Black);
		label.setPosition(pos[i].x+9-15, pos[i].y-15);
		janela.draw(label);
	}
}

// eu sou mt bom com vetores
void printSetas(sf::RenderWindow &janela, Graph &G, vector<Vector> &pos, int raio) {
	const float pi = acos(-1.0);

	for (int i = 0; i < G.m; i++) {
		Vector fim = pos[G.edges[i].second];
		Vector v = fim - pos[G.edges[i].first];
		Vector unit = v*(1/v.norm());

		Vector pos = fim - unit*raio*1.6;

		// angulo que tem que rodar pra seta ficar certa
		float angle = v.angle()-pi/6;

		Vector delta = Vector(raio/2-1, raio/2-1).rotate(angle) - Vector(raio/2-1, raio/2-1);

		// cria triangulo na ponta da aresta
		sf::CircleShape tri(raio/2, 3);
		tri.setRotation((angle)*180/pi);
		tri.setFillColor(sf::Color::Black);
		tri.setPosition(pos.x-raio/2+1-delta.x, pos.y-raio/2+1-delta.y);
		janela.draw(tri);
	}
}

void lerGrafoArquivo(tgui::EditBox::Ptr arq, Graph *G, vector<Vector> *pos, vector<int> *color, int *X, int *Y) {
	ifstream inFile(arq->getText().toAnsiString());
	if (!inFile) {
		cout << "Erro: arquivo zoado" << endl;
		return;
	}

	int n, m;
	inFile >> n >> m;
	vector<string> label(n);
	for (auto &i : label) inFile >> i;

	*G = Graph(n, label);

	for (int i = 0; i < m; i++) {
		int a, b; inFile >> a >> b;
		G->addEdge(a, b);
	}

	*pos = getGood(*G, (*X)*2/3, *Y, max(10, 50-G->n), max(10, 100-G->m));
	*color = vector<int>(n, 0);

	inFile.close();
}

// encontra o vertice onde a pessoa clicou
int achaVertice(Vector at, vector<Vector> pos, float raio) {
	for (int i = 0; i < pos.size(); i++) if (dist(at, pos[i]) < raio) return i;
	return -1;
}

void mudaDir(int* dir) {
	(*dir) ^= 1;
}

vector<int> coloreDistancia(Graph &G, int at) {
	vector<int> color(G.n, 0);

	// BFS
	vector<int> vis(G.n, 0); vis[at] = 1;
	queue<pair<int, int> > q;
	q.push({at, 0});

	while (q.size()) {
		int u = q.front().first, d = q.front().second;
		q.pop();
		color[u] = (d%6)+1;
		
		for (int i : G.adj[u]) if (!vis[i]) {
			q.push({i, d+1});
			vis[i] = 1;
		}
	}

	return color;
}

void loadWidgets(tgui::Gui &gui, Graph *G, vector<Vector> *pos, vector<int> *color, int *X, int *Y, int* dir) {
	tgui::Theme tema{"src/temas/TransparentGrey.txt"};
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
	botaoArquivo->setSize(70.f, 20.f);
	botaoArquivo->setPosition(930.f, 235.f);
	gui.add(botaoArquivo);

	// Chama a função de importar arquivo
	botaoArquivo->connect(
			"pressed", lerGrafoArquivo, textoArquivo, G, pos, color, X, Y);

	check->connect(
			"checked", mudaDir, dir);
	check->connect(
			"unchecked", mudaDir, dir);
}

void displayTeste(int X, int Y) {

	// Carrega a fonte Consola Bold (Gosto dela)
	sf::Font fonte;
	if (!fonte.loadFromFile("src/fontes/CONSOLAB.TTF")) {
		// TODO: Erro direito
		return;
	}

	// Antialiasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Cria a janela
	sf::RenderWindow janela(sf::VideoMode(X, Y), "graphODA", sf::Style::Default, settings);
	tgui::Gui gui(janela);

	// TODO: tem que muder isso ae, talkei
	Graph G = Graph(0);
	vector<Vector> pos;
	vector<int> color;
	int clique = -1, dir = 0;
	Vector lastMousePos(0, 0);
	const float raioG = 15;

	// Tenta importar os widgets da gui
	try {
		loadWidgets(gui, &G, &pos, &color, &X, &Y, &dir);
	} catch (const tgui::Exception &e) {
		// TODO: mensagem de erro
		return;
	}

	// "Main Loop"
	// Roda o programa enquanto a janela estiver aberta
	
	while(janela.isOpen()) {
		// Checa se algum evento aconteceu
		sf::Event evento;
		while(janela.pollEvent(evento))
		{
			// Se pediu pra fechar
			if(evento.type == sf::Event::Closed)
				janela.close();

			// Cria os widgets da GUI
			gui.handleEvent(evento);
		}

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

		// se nao tiver posicoes, pega poligono
		if (!pos.size() and G.n) pos = getPoligono(G, X*2/3, Y);

		// faz mais iteracoes da mola
		fdp1(G, pos, 2, clique, X*2/3, Y, raioG);
		printGrafo(janela, fonte, G, pos, color, raioG);
		if (dir) printSetas(janela, G, pos, raioG);

		// testa clique
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (clique == -1) {
				auto position = sf::Mouse::getPosition(janela);
				Vector position_vec(position.x, position.y);
				clique = achaVertice(position_vec, pos, raioG);
				lastMousePos = position_vec;
			}
		} else clique = -1, color = vector<int>(color.size(), 0);

		// move vertice
		if (clique > -1) {
			auto position = sf::Mouse::getPosition(janela);
			Vector position_vec(position.x, position.y);
			pos[clique] = deixaDentro(pos[clique] + (position_vec - lastMousePos), X*2/3, Y, raioG);

			lastMousePos = position_vec;
			color = coloreDistancia(G, clique);
		}


		gui.draw();

		// Termina iteração e atualiza janela
		janela.display();
	}
}
