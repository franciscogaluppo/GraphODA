#include "Interface.hpp"

void lerGrafoArquivo(tgui::EditBox::Ptr arq, GraphCanvas *GC) {
	GC->lerGrafoArquivo(arq->getText().toAnsiString());
}

void mudaDir(GraphCanvas *GC) {
	(GC->GD.temDir) ^= 1;
}

void centraliza(GraphCanvas *GC) {
	(GC->GD.centr) ^= 1;
}

void loadWidgets(tgui::Gui &gui, GraphCanvas *GC) {
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
			"pressed", lerGrafoArquivo, textoArquivo, GC);

	check->connect(
			"checked", mudaDir, GC);
	check->connect(
			"unchecked", mudaDir, GC);

	botaoCenter->connect(
			"pressed", centraliza, GC);
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

	// GraphCanvas
	GraphCanvas GC(janela, fonte, X*2/3, Y, 15);

	// Tenta importar os widgets da gui
	try {
		loadWidgets(gui, &GC);
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
				GC.GD.draw ^= 1;
			}
		}

		drawStuff(janela, fonte);

		// olha se a pessoa ta mexendo no grafo
		GC.handleClique();

		// display do grafo
		GC.display();
	
		gui.draw();

		// Termina iteração e atualiza janela
		janela.display();
	}
}
