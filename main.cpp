#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <bits/stdc++.h> // por agora nao quero preocupar com isso
using namespace std;

vector<int> vertices;
vector<pair<int, int> > ares;

// TODO: Receber e plotar um grafo qualquer

// TODO: Receber um grafo na classe bonitinha
void printGrafoPoligono(sf::RenderWindow &janela, sf::Font &fonte)
{

	int n = vertices.size(), m = ares.size();

	const float raio = 15;
	const float raioGrafo = 250;
	pair<float, float> centro = {400, 300};
	// angulo = 360/n
	const double theta = 2*acos(-1.0)/n;

	// numero impar de vertices tem que arredar um pouco
	if (n % 2 == 1) {
		float falta = raioGrafo - raioGrafo*cos(theta/2);
		centro.second += falta/2;
	}

	vector<pair<int, int> > pos(n);
	for (int i = 0; i < n; i++)
		pos[i] = {centro.first+sin(i*theta+theta/2)*raioGrafo,
			centro.second+cos(i*theta+theta/2)*raioGrafo};

	// Cria as arestas
	for(int i = 0; i < m; i++)
	{
		// Arestas sem largura, por isso vetores
		sf::Vertex linha[] =
		{
			sf::Vertex(sf::Vector2f(
				pos[ares[i].first].first, pos[ares[i].first].second),
					sf::Color::Black),

			sf::Vertex(sf::Vector2f(
				pos[ares[i].second].first, pos[ares[i].second].second),
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
		v.setPosition(pos[i].first-raio+1, pos[i].second-raio+1);
		janela.draw(v);

		// Coloca texto dentro da bola
		sf::Text label;
		label.setFont(fonte);
		label.setString(to_string(vertices[i]));
		label.setCharacterSize(24);
		label.setFillColor(sf::Color::Black);
		label.setPosition(pos[i].first+9-15, pos[i].second-15);
		janela.draw(label);
	}

}

void lerGrafoArquivo(tgui::EditBox::Ptr arq)
{
	ifstream inFile(arq->getText().toAnsiString());
	if (!inFile) {
		cout << "Erro: arquivo zoado" << endl;
		return;
	}

	int n, m;
	inFile >> n >> m;
	vertices.resize(n), ares.resize(m);
	for (int &i : vertices) inFile >> i;
	for (auto &i : ares) inFile >> i.first >> i.second;
	inFile.close();
}

void printArquivo(tgui::EditBox::Ptr arq, tgui::ListBox::Ptr lista, tgui::CheckBox::Ptr check)
{
	cout << "Nome do arquivo: " << arq->getText().toAnsiString() << endl;

	cout << lista->getSelectedItem().toAnsiString();

	if(check->isChecked())
		cout << " com peso." << endl;
	else
		cout << "." << endl;

	cout << endl;
}


void loadWidgets(tgui::Gui &gui)
{
	tgui::Theme tema{"temas/TransparentGrey.txt"};
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
	botaoArquivo->connect(
			"pressed", lerGrafoArquivo, textoArquivo);
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

		printGrafoPoligono(janela, fonte);

		gui.draw();

		// Termina iteração e atualiza janela
		janela.display();
	}

	return 0;
}
