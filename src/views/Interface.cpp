#include "Interface.hpp"

void lerGrafoArquivoAux(tgui::EditBox::Ptr arq, GraphCanvas *GC)
{
	auto i = lerGrafoArquivo(arq->getText().toAnsiString());
	GC->setGraph(i);
}

void mudaDir(GraphCanvas *GC) { (GC->GD.temDir) ^= 1; }

void centraliza(GraphCanvas *GC) { (GC->GD.centr) ^= 1; }

void loadWidgets(tgui::Gui &gui, GraphCanvas *GC) {
	tgui::Theme tema{"assets/TransparentGrey.txt"};
	// tgui::ButtonRenderer(tema.getRenderer("button")).setBackgroundColor(sf::Color::Blue);
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

	// Botão de help
	auto botaoHelp = tgui::Button::create("Help");
	botaoHelp->setSize(75.f,20.f);
	botaoHelp->setPosition(930.f, 290.f);
	gui.add(botaoHelp);

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
	botaoArquivo->connect("pressed", lerGrafoArquivoAux, textoArquivo, GC);

	check->connect("checked", mudaDir, GC);
	check->connect("unchecked", mudaDir, GC);

	botaoCenter->connect("pressed", centraliza, GC);
}

void drawStuff(sf::RenderWindow &janela, sf::Font &fonte) {
	// Limpa tela e coloca branco
	janela.clear(sf::Color::White);

	// Parte cinza
	sf::RectangleShape menu(sf::Vector2f(400.f, 700.f));
	menu.setFillColor(sf::Color(192, 192, 192));
	menu.setPosition(800.f, 0.f);
	janela.draw(menu);

		//Menu superior
	sf::RectangleShape superior(sf::Vector2f(800.f,100.f));	//larg x alt
	superior.setFillColor(sf::Color(255,0,0));
	superior.setPosition(0.f, 600.f);
	janela.draw(superior);

	//Divisão entre o canvas e o superior
	sf::Vertex linha0[] = {sf::Vertex(sf::Vector2f(0,600), sf::Color(130, 130, 130)),

		sf::Vertex(sf::Vector2f(1200, 600), sf::Color(130, 130, 130))};
	janela.draw(linha0, 2, sf::Lines);

	// Divisão entre o canvas e o menu
	sf::Vertex linha1[] = {sf::Vertex(sf::Vector2f(800, 0), sf::Color::Black),

		sf::Vertex(sf::Vector2f(800, 700), sf::Color::Black)};
	janela.draw(linha1, 2, sf::Lines);

	// Divisão entre instruções e import
	sf::Vertex linha2[] = {
		sf::Vertex(sf::Vector2f(830, 170), sf::Color(130, 130, 130)),

		sf::Vertex(sf::Vector2f(1170, 170), sf::Color(130, 130, 130))};
	janela.draw(linha2, 2, sf::Lines);

	// Divisão entre import e algoritmos
	sf::Vertex linha3[] = {
		sf::Vertex(sf::Vector2f(830, 285), sf::Color(130, 130, 130)),

		sf::Vertex(sf::Vector2f(1170, 285), sf::Color(130, 130, 130))};
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
	instr.setFillColor(sf::Color(130, 130, 130));
	instr.setPosition(820, 55);
	janela.draw(instr);
}

void drawDrawMode(sf::RenderWindow &janela, sf::Font &fonte, int X) {
	sf::Text draw;
	draw.setFont(fonte);
	draw.setString("D");
	draw.setCharacterSize(32);
	draw.setFillColor(sf::Color::Red);
	draw.setPosition(X - 32, 0);
	janela.draw(draw);
}

Graph displayTeste(int X, int Y, Graph G) {
	// Carrega a fonte Consola Bold (Gosto dela)
	sf::Font fonte;
	if (!fonte.loadFromFile("assets/CONSOLAB.TTF")) {
		// TODO: Erro direito
		return G;
	}

	// Antialiasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	// Cria a janela
	sf::RenderWindow janela(sf::VideoMode(X, Y), "graphODA", sf::Style::Close,
			settings);
	janela.setKeyRepeatEnabled(false);
	tgui::Gui gui(janela);

	// GraphCanvas
	GraphCanvas GC(janela, fonte, X * 2 / 3, Y * 6/7, 15);
	GC.setGraph(G);
	bool editing;
	tgui::EditBox::Ptr edit;

	// Tenta importar os widgets da gui
	try {
		loadWidgets(gui, &GC);
	} catch (const tgui::Exception &e) {
		// TODO: mensagem de erro
		return G;
	}
	// "Main Loop"
	// Roda o programa enquanto a janela estiver aberta

	while (janela.isOpen()) {
		// se janela nao ta ativa, espera
		if (!janela.hasFocus()) continue;

		// Checa se algum evento aconteceu
		sf::Event evento;
		while (janela.pollEvent(evento)) {
			// Se pediu pra fechar
			if (evento.type == sf::Event::Closed) janela.close();

			// Cria os widgets da GUI
			gui.handleEvent(evento);

			// apertou alguma coisa no teclado
			if (evento.type == sf::Event::KeyPressed) {
				// ctrl -> toggle draw mode
				if (evento.key.code == sf::Keyboard::LControl and !editing)
					GC.GD.draw ^= 1;

				// esc -> sai da edicao dos pesos/labels
				if (evento.key.code == sf::Keyboard::Escape) {
					editing = 0;
					gui.remove(edit);
					GC.editLabel = GC.editWeight = -1;
				}

				// enter -> edita peso/label de fato
				if (evento.key.code == sf::Keyboard::Return and editing) {
					// label
					if (GC.editLabel > -1)
						GC.GD.G.label[GC.editLabel] = edit->getText().toAnsiString();

					// weight
					if (GC.editWeight > -1) {
						string s = edit->getText().toAnsiString();

						bool valid = 1;
						if (!s.size()) valid = 0;
						else if (!(s[0] == '-' or (s[0] >= '0' and s[0] <= '9'))) valid = 0;
						for (int i = 1; i < s.size(); i++) if (s[i] < '0' or s[i] > '9') valid = 0;

						if (valid) {
							Graph G(GC.GD.G.getN());
							G.label = GC.GD.G.label;
							int position = 0;
							auto adj = GC.GD.G.getAdj();
							for (int i = 0; i < GC.GD.G.getN(); i++)
								for (auto &j : adj[i]) {
									if (position++ == GC.editWeight)
										G.addEdge(i, j.first, stoi(edit->getText().toAnsiString()));
									else
										G.addEdge(i, j.first, j.second);
								}
							GC.GD.setGraphContinue(G);
						} else {
							// TODO: erro direito
							cout << "ERRO: peso invalido" << endl;
						}
					}

					editing = 0;
					gui.remove(edit);
					GC.editLabel = GC.editWeight = -1;
				}
			}
		}

		drawStuff(janela, fonte);
		if (GC.GD.draw) drawDrawMode(janela, fonte, X * 2 / 3);

		// olha se ta editando os pesos/labels
		if (GC.editLabel > -1 or GC.editWeight > -1) {
			if (!editing) {
				editing = 1;
				auto edg = GC.GD.G.getEdges();

				if (GC.editLabel > -1) {
					edit = tgui::EditBox::create();
					edit->setSize(GC.GD.raio * sqrt(2), GC.GD.raio * sqrt(2));
					edit->setPosition(
							GC.GD.pos[GC.editLabel].x - (GC.GD.raio - 1) / sqrt(2),
							GC.GD.pos[GC.editLabel].y - (GC.GD.raio - 1) / sqrt(2));
					edit->setText(GC.GD.G.label[GC.editLabel]);
					gui.add(edit);
					edit->setFocused(true);
				}

				if (GC.editWeight > -1) {
					edit = tgui::EditBox::create();
					Vector size(GC.GD.raio * sqrt(2), GC.GD.raio * sqrt(2));
					edit->setSize(size.x, size.y);

					// acha posicao
					Vector ini = GC.GD.pos[edg[GC.editWeight].first],
					fim = GC.GD.pos[edg[GC.editWeight].second];
					Vector pos = ini + (fim - ini) * GC.GD.posPeso[GC.editWeight];

					// arestas paralelas
					Vector add(0, 0);
					if (GC.GD.isParal[GC.editWeight]) {
						add = fim - ini;
						if (add.norm()) {
							add = add * (1 / add.norm());
							add = add.rotate(acos(-1.0) / 2);
							add = add * (GC.GD.raio / 3.0);
						}
					}
					pos = pos + add;

					edit->setPosition(pos.x - size.x / 2, pos.y - size.y / 2);
					int peso, position = 0;
					auto adj = GC.GD.G.getAdj();
					for (int i = 0; i < GC.GD.G.getN(); i++)
						for (auto j : adj[i])
							if (position++ == GC.editWeight) peso = j.second;
					edit->setText(to_string(peso));
					gui.add(edit);
					edit->setFocused(true);
				}
			}
		} else
			GC.handleClique();

		// views do grafo
		GC.display();

		gui.draw();

		// Termina iteração e atualiza janela
		janela.display();
	}

	return GC.GD.G;
}
