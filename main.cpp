#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "Graph.hpp"

#include <bits/stdc++.h> // por agora nao quero preocupar com isso
using namespace std;

float c1 = 20, c2 = 100, c3 = 10, c4 = 0.1;
bool SPRING;

// tamanho do retangulo onde renderiza o grafo
const int MAXX = 800, MAXY = 600;

void spring(Graph &G, vector<pair<float, float> > &pos, int it) {
	if (pos.size() != G.n) {
		// TODO: Erro direito
		cout << "Erro: posicoes zoadas" << endl;
		return;
	}

	// funcoes auxiliares
	auto sq = [](float x){return x*x;};
	auto dist = [sq](pair<float, float> a, pair<float, float> b) {
		return sqrt(sq(a.first-b.first) + sq(a.second-b.second));
	};

	// calcula matriz de adjacencia
	// TODO: classe Graph calcular isso
	vector<vector<int> > adj(G.n, vector<int>(G.n, 0));
	for (int i = 0; i < G.n; i++) for (int j : G.adj[i]) adj[i][j] = adj[j][i] = 1;

	// constantes do algoritmo
	//float c1 = 20, c2 = 100, c3 = 10, c4 = 1;
	
	// paredes como vertices artificiais
	vector<pair<float, float> > parede;
	for (int i = 0; i <= MAXX; i += 10) {
		parede.push_back({i, 0});
		parede.push_back({i, MAXY});
	}
	for (int i = 0; i <= MAXY; i += 10) {
		parede.push_back({0, i});
		parede.push_back({MAXX, i});
	}

	// numero de iteracoes
	while (it--) {

		// forca aplicada a cada vertice
		vector<pair<float, float> > forca;

		for (int i = 0; i < G.n; i++) {
			pair<float, float> f = {0.0, 0.0};

			for (int j = 0; j < G.n; j++) if (j != i) {

				// vetor unitario na direcao de i para j
				pair<float, float> unit = {pos[j].first-pos[i].first,
								pos[j].second-pos[i].second};
				float norma = dist(make_pair(0.0, 0.0), unit);
				unit.first /= norma, unit.second /= norma;

				float d = dist(pos[i], pos[j]);

				// computa forca de acordo com o algoritmo
				if (!adj[i][j]) {
//					f.first -= unit.first*c3/sqrt(d);
//					f.second -= unit.second*c3/sqrt(d);

					f.first -= unit.first*5000*c3/(d*d);
					f.second -= unit.second*5000*c3/(d*d);
				} else {
					f.first += unit.first*c1*log(d/c2);
					f.second += unit.second*c1*log(d/c2);
				}
			}

			// forca em relacao as paredes
			for (auto j : parede) {
				pair<float, float> unit = {j.first-pos[i].first,
								j.second-pos[i].second};
				float norma = dist(make_pair(0.0, 0.0), unit);
				unit.first /= norma, unit.second /= norma;

				float d = dist(pos[i], j);

				// repulsao
				f.first -= 100*unit.first*c3/(d*d);
				f.second -= 100*unit.second*c3/(d*d);
			}

			forca.push_back(f);
		}

		// atualiza posicoes
		for (int i = 0; i < G.n; i++) {
			pos[i].first += c4*forca[i].first;
			pos[i].second += c4*forca[i].second;
		}
	}
}

vector<pair<float, float> > getPoligono(Graph &G) {
	const float raioGrafo = (min(MAXX, MAXY)-100)/2;
	pair<float, float> centro = {MAXX/2, MAXY/2};
	// angulo = 360/n
	const double theta = 2*acos(-1.0)/G.n;

	// numero impar de vertices tem que arredar um pouco
	if (G.n % 2 == 1) {
		float falta = raioGrafo - raioGrafo*cos(theta/2);
		centro.second += falta/2;
	}

	vector<pair<float, float> > pos(G.n);
	for (int i = 0; i < G.n; i++)
		pos[i] = {centro.first+sin(i*theta+theta/2)*raioGrafo,
			centro.second+cos(i*theta+theta/2)*raioGrafo};
	
	return pos;
}

void printGrafo(sf::RenderWindow &janela, sf::Font &fonte, Graph &G)
{
	const float raio = 15;

	vector<pair<float, float> > pos = getPoligono(G);
	// algoritmo de Eades
	if (SPRING) spring(G, pos, 300);

	// Cria as arestas
	for(int i = 0; i < G.m; i++)
	{
		// Arestas sem largura, por isso vetores
		sf::Vertex linha[] =
		{
			sf::Vertex(sf::Vector2f(
				pos[G.edges[i].first].first, pos[G.edges[i].first].second),
					sf::Color::Black),

			sf::Vertex(sf::Vector2f(
				pos[G.edges[i].second].first, pos[G.edges[i].second].second),
					sf::Color::Black)
		};

		janela.draw(linha, 2, sf::Lines);
	}

	// Cria os vértices
	for(int i = 0; i < G.n; i++)
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
		label.setString(G.label[i]);
		label.setCharacterSize(24);
		label.setFillColor(sf::Color::Black);
		label.setPosition(pos[i].first+9-15, pos[i].second-15);
		janela.draw(label);
	}
}

void lerGrafoArquivo(tgui::EditBox::Ptr arq, Graph *G)
{
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

	inFile.close();
}

void printArquivo(tgui::EditBox::Ptr arq, tgui::ListBox::Ptr lista, tgui::CheckBox::Ptr check)
{
	cout << "Nome do arquivo: " << arq->getText().toAnsiString() << endl;

	cout << lista->getSelectedItem().toAnsiString();

	if(check->isChecked())
		cout << " com peso." << endl;

	cout << endl;
}

void getSpring(tgui::CheckBox::Ptr c, tgui::EditBox::Ptr C1, tgui::EditBox::Ptr C2, tgui::EditBox::Ptr C3, tgui::EditBox::Ptr C4)
{
	if(c->isChecked())
	{
		SPRING = 1;
		if (C1->getText().toAnsiString().size()) c1 = stoi(C1->getText().toAnsiString());
		if (C2->getText().toAnsiString().size()) c2 = stoi(C2->getText().toAnsiString());
		if (C3->getText().toAnsiString().size()) c3 = stoi(C3->getText().toAnsiString());
		if (C4->getText().toAnsiString().size()) c4 = stoi(C4->getText().toAnsiString());
	} else SPRING = 0;
}


void loadWidgets(tgui::Gui &gui, Graph *G)
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
			"pressed", lerGrafoArquivo, textoArquivo, G);





	// Coisas pro cabra testar
	auto c = tgui::CheckBox::create("Mola");
	c->setSize(20.f, 20.f);
	c->setPosition(820.f, 500.f);
	gui.add(c);

	auto t1 = tgui::EditBox::create();
	t1->setSize(50.f, 20.f);
	t1->setPosition(820.f, 520.f);
	t1->setDefaultText("c1");
	gui.add(t1);

	auto t2 = tgui::EditBox::create();
	t2->setSize(50.f, 20.f);
	t2->setPosition(890.f, 520.f);
	t2->setDefaultText("c2");
	gui.add(t2);

	auto t3 = tgui::EditBox::create();
	t3->setSize(50.f, 20.f);
	t3->setPosition(820.f, 540.f);
	t3->setDefaultText("c3");
	gui.add(t3);
	
	auto t4 = tgui::EditBox::create();
	t4->setSize(50.f, 20.f);
	t4->setPosition(890.f, 540.f);
	t4->setDefaultText("c4");
	gui.add(t4);

	auto b = tgui::Button::create("ativar");
	b->setSize(70.f, 20.f);
	b->setPosition(960.f, 520.f);
	gui.add(b);

	b->connect("pressed", getSpring, c, t1, t2, t3, t4);
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

	Graph G = Graph(0);

	// Tenta importar os widgets da gui
	try
	{
		loadWidgets(gui, &G);
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

		printGrafo(janela, fonte, G);

		gui.draw();

		// Termina iteração e atualiza janela
		janela.display();
	}

	return 0;
}
