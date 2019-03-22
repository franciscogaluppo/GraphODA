#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <iostream>
#include <string>

// TODO: Receber e plotar um grafo qualquer
// Função que plota um grafo
void printGrafo(sf::RenderWindow &janela, sf::Font &fonte)
{
	// Grafo fixo por enquanto
	const float raio = 15;
	const int n = 5, m = 6;	
	
	int ares[m][2] = 
	{
		{0, 1},
		{0, 4},
		{1, 2},
		{1, 4},
		{2, 4},
		{3, 4}
	};
	
	std::string nomes[n] = {"1", "2", "3", "4", "5"};

	// Precisamos automatizar as coordenadas
	float pos[n][2] =
	{
		{200.f,150.f},
		{200.f,450.f},
		{600.f,450.f},
		{600.f,150.f},
		{400.f,300.f}
	};
	
	// Cria as arestas
	for(int i = 0; i < m; i++)
	{
		// Arestas sem largura, por isso vetores
		sf::Vertex linha[] =
		{
			sf::Vertex(sf::Vector2f(
				pos[ares[i][0]][0], pos[ares[i][0]][1]),
					sf::Color::Black),

			sf::Vertex(sf::Vector2f(
				pos[ares[i][1]][0], pos[ares[i][1]][1]),
					sf::Color::Black)
		};

		janela.draw(linha, 2, sf::Lines);
	}

	// Cria os vértices
	for(int i = 0; i < n; i++)
	{
		// Cria um círculo
		sf::CircleShape v(raio);
		v.setFillColor(sf::Color::Red);
		v.setOutlineThickness(3.f);
		v.setOutlineColor(sf::Color::Black);
		v.setPosition(pos[i][0]-raio+1, pos[i][1]-raio+1);
		janela.draw(v);

		// Coloca texto dentro da bola
		sf::Text label;
		label.setFont(fonte);
		label.setString(nomes[i]);
		label.setCharacterSize(24);
		label.setFillColor(sf::Color::Black);
		label.setPosition(pos[i][0]+9-15, pos[i][1]-15);
		janela.draw(label);
	}

}

void printArquivo(tgui::EditBox::Ptr arq, tgui::ListBox::Ptr lista, tgui::CheckBox::Ptr check)
{
	std::cout << "Nome do arquivo: " << arq->getText().toAnsiString() << std::endl;
	
	std::cout << lista->getSelectedItem().toAnsiString();
	
	if(check->isChecked())
		std::cout << " com peso." << std::endl;
	else
		std::cout << "." << std::endl;

	std::cout << std::endl;
}


void loadWidgets(tgui::Gui &gui)
{
	tgui::Theme tema{"temaGUI/TransparentGrey.txt"};
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
	auto check = tgui::CheckBox::create("Com peso");
	check->setSize(20.f, 20.f);
	check->setPosition(820.f, 235.f);
	gui.add(check);

	// Botão pra ler arquivo
	auto botaoArquivo = tgui::Button::create("Importar");
	botaoArquivo->setSize(70.f, 20.f);
	botaoArquivo->setPosition(930.f, 235.f);
	gui.add(botaoArquivo);

	// Chama a função de importar arquivo
	botaoArquivo->connect(
		"pressed", printArquivo, textoArquivo,
		lista, check);
}





int main()
{
	// Carrega a fonte Consola Bold (Gosto dela)
	sf::Font fonte;
	if(!fonte.loadFromFile("fontes/CONSOLAB.TTF"))
	{
		// TODO: Mensagem de erro
		return 1; 
	}

	// Antialiasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	// Cria a janela
	sf::RenderWindow janela(
		sf::VideoMode(1200, 600), "InfoGraph");
    tgui::Gui gui(janela);

	// Tenta importar os widgets da gui
	try
	{
		loadWidgets(gui);
	}
	catch (const tgui::Exception &e)
	{
		// TODO: mensagem de erro
		return 1;
	}
	
	// "Main Loop"
	// Roda o programa enquanto a janela estiver aberta
	while(janela.isOpen())
	{
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

		printGrafo(janela, fonte);
		
		gui.draw();

		// Termina iteração e atualiza janela
		janela.display();
	}

	return 0;
}
