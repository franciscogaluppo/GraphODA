#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "Graph.hpp"
#include "Vector.hpp"

#include <bits/stdc++.h> // por agora nao quero preocupar com isso
using namespace std;

float c1 = 20, c2 = 100, c3 = 10, c4 = 0.1;
bool FDP1, FDP2;
int RANDOM, ITER = 100;

// tamanho do retangulo onde renderiza o grafo
const int MAXX = 800, MAXY = 600;

// Eades algorithm
void fdp1(Graph &G, vector<Vector> &pos, int it) {
	if (pos.size() != G.n) {
		// TODO: Erro direito
		cout << "Erro: posicoes zoadas" << endl;
		return;
	}

	// calcula matriz de adjacencia
	// TODO: classe Graph calcular isso
	vector<vector<int> > adj(G.n, vector<int>(G.n, 0));
	for (int i = 0; i < G.n; i++) for (int j : G.adj[i]) adj[i][j] = adj[j][i] = 1;

	// constantes do algoritmo
	//float c1 = 20, c2 = 100, c3 = 10, c4 = 1;
	
	// paredes como vertices artificiais
	vector<Vector> parede;
	for (int i = 0; i <= MAXX; i += 10) {
		parede.push_back(Vector(i, 0));
		parede.push_back(Vector(i, MAXY));
	}
	for (int i = 0; i <= MAXY; i += 10) {
		parede.push_back(Vector(0, i));
		parede.push_back(Vector(MAXX, i));
	}

	// numero de iteracoes
	while (it--) {

		// forca aplicada a cada vertice
		vector<Vector> forca;

		for (int i = 0; i < G.n; i++) {
			Vector f(0, 0);

			for (int j = 0; j < G.n; j++) if (j != i) {

				float d = dist(pos[i], pos[j]);

				// vetor unitario na direcao de i para j
				Vector unit = (pos[j] - pos[i])*(1/d);

				// computa forca de acordo com o algoritmo
				if (!adj[i][j])  f = f - unit*(5000*c3/(d*d));
				else             f = f + unit*(c1*log(d/c2));
			}

			// forca em relacao as paredes
			for (auto j : parede) {

				float d = dist(pos[i], j);
				Vector unit = (j - pos[i])*(1/d);

				// repulsao
				f = f - unit*(c3/(d*d));
			}

			forca.push_back(f);
		}

		// atualiza posicoes
		for (int i = 0; i < G.n; i++) pos[i] = pos[i] + forca[i]*c4;
	}
}

// Fruchterman algorithm
void fdp2(Graph &G, vector<Vector> &pos, int it) {
	if (pos.size() != G.n) {
		// TODO: Erro direito
		cout << "Erro: posicoes zoadas" << endl;
		return;
	}

	// calcula matriz de adjacencia
	// TODO: classe Graph calcular isso
	vector<vector<int> > adj(G.n, vector<int>(G.n, 0));
	for (int i = 0; i < G.n; i++) for (int j : G.adj[i]) adj[i][j] = adj[j][i] = 1;

	// constante do algoritmo
	float k = sqrt(MAXX*MAXY/float(G.n))/2;
	float t = min(MAXX, MAXY)/8;
	float delta = t/it;

	// paredes como vertices artificiais
	vector<Vector> parede;
	for (int i = 0; i <= MAXX; i += 10) {
		parede.push_back(Vector(i, 0));
		parede.push_back(Vector(i, MAXY));
	}
	for (int i = 0; i <= MAXY; i += 10) {
		parede.push_back(Vector(0, i));
		parede.push_back(Vector(MAXX, i));
	}

	while (it--) {

		// forca aplicada a cada vertice
		vector<Vector> forca;

		for (int i = 0; i < G.n; i++) {
			Vector f(0, 0);

			for (int j = 0; j < G.n; j++) if (j != i) {

				float d = dist(pos[i], pos[j]);

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

				// repulsao
				if (d < k) f = f - unit*(k*k/d);
			}

			// limitante das forcas
			float disp = f.norm();
			f = f*(1/disp);
			f = f*min(disp, t);

			forca.push_back(f);
		}

		// atualiza posicoes
		for (int i = 0; i < G.n; i++) pos[i] = pos[i] + forca[i];

		t = max((float)0, t-delta);
	}
}

vector<Vector> getPoligono(Graph &G) {
	const float raioGrafo = (min(MAXX, MAXY)-100)/2;
	Vector centro(MAXX/2, MAXY/2);
	// angulo = 360/n
	const double theta = 2*acos(-1.0)/G.n;

	// numero impar de vertices tem que arredar um pouco
	if (G.n % 2 == 1) {
		float falta = raioGrafo - raioGrafo*cos(theta/2);
		centro = centro + Vector(0, falta/2);
	}

	vector<Vector> pos(G.n, Vector(0, 0));
	for (int i = 0; i < G.n; i++)
		pos[i] = Vector(centro.x+sin(i*theta+theta/2)*raioGrafo,
			centro.y+cos(i*theta+theta/2)*raioGrafo);
	
	return pos;
}

// se os segmentos de reta interceptam
bool cruza(Vector a, Vector b, Vector c, Vector d) {
	if (cross(b-a, c-b)*cross(b-a, d-b) > 0) return 0;
	if (cross(d-c, a-d)*cross(d-c, b-d) > 0) return 0;
	return 1;
}

// numero de intersecoes de arestas
int inter(vector<Vector> &pos, Graph &G) {
	int ret = 0;
	for (auto &i : G.edges) for (auto &j : G.edges)
		if (cruza(pos[i.first], pos[i.second], pos[j.first], pos[j.second])) ret++;
	return ret;
}

int FindFontSize(int n, int font_size){	//acha o tamanho da fonte
	if (n<10){
		return font_size;
	}
	else if(n<100){
		return font_size-4;
	}
	else
		return font_size-6;
}

void printGrafo(sf::RenderWindow &janela, sf::Font &fonte, Graph &G, int &calc, int n)
{
	const float raio = 15;

	static vector<Vector> pos;
	if (calc) {
		// gera um monte de seed aleatoria e ver qual sai melhor
		if (RANDOM) {
			auto pos_best = pos;
			int best = 1000000000;
			for (int i = 0; i < RANDOM; i++) {
				pos.clear();
				for (int i = 0; i < G.n; i++)
					pos.push_back(Vector((rand()%(MAXX-100))+50,
								(rand()%(MAXY-100)+50)));
				if (FDP1) fdp1(G, pos, ITER);
				if (FDP2) fdp2(G, pos, ITER);

				int intersecoes = inter(pos, G);
				if (intersecoes < best) {
					pos_best = pos;
					best = intersecoes;
				}
			}
			pos = pos_best;
		} else {
			pos = getPoligono(G);
			if (FDP1) fdp1(G, pos, ITER);
			if (FDP2) fdp2(G, pos, ITER);
		}
		calc = 0;
	}

	// Cria as arestas
	for(int i = 0; i < G.m; i++)
	{
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
	for(int i = 0; i < G.n; i++)
	{
		// Cria um círculo
		sf::CircleShape v(raio);
		v.setFillColor(sf::Color::Red);
		v.setOutlineThickness(3.f);
		v.setOutlineColor(sf::Color::Black);
		v.setPosition(pos[i].x-raio+1, pos[i].y-raio+1);
		janela.draw(v);

		// Coloca texto dentro da bola
		sf::Text label;
		label.setFont(fonte);
		label.setString(G.label[i]);
		int font_size = FindFontSize(n, 24);	// font_size default = 24
		label.setCharacterSize(font_size); //tamanho fonte
		label.setFillColor(sf::Color::Black);
		label.setPosition(pos[i].x+9-15, pos[i].y-15);
		janela.draw(label);
	}
}

void lerGrafoArquivo(tgui::EditBox::Ptr arq, Graph *G, int *calc, int *n)
{
	ifstream inFile(arq->getText().toAnsiString());
	if (!inFile) {
		cout << "Erro: arquivo zoado" << endl;
		return;
	}

	*calc = 1;
	int m;
	inFile >> *n >> m;
	vector<string> label(*n);
	for (auto &i : label) inFile >> i;

	*G = Graph(*n, label);

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

void getSpring(tgui::CheckBox::Ptr c, tgui::CheckBox::Ptr cc, tgui::CheckBox::Ptr rnd,
		tgui::EditBox::Ptr t1, tgui::EditBox::Ptr t2, int *calc) {
	*calc = 1;

	if (rnd->isChecked() and t2->getText().toAnsiString().size()) RANDOM = stoi(t2->getText().toAnsiString());
	else RANDOM = 0;

	if (t1->getText().toAnsiString().size()) ITER = stoi(t1->getText().toAnsiString());
	else ITER = 300;

	if(c->isChecked()) FDP1 = 1;
	else FDP1 = 0;

	if(cc->isChecked()) FDP2 = 1;
	else FDP2 = 0;	
}


void loadWidgets(tgui::Gui &gui, Graph *G, int *calc, int *n)
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
			"pressed", lerGrafoArquivo, textoArquivo, G, calc, n);





	// Coisas pro cabra testar
	auto c = tgui::CheckBox::create("FDP1");
	c->setSize(20.f, 20.f);
	c->setPosition(820.f, 500.f);
	gui.add(c);


	auto cc = tgui::CheckBox::create("FDP2");
	cc->setSize(20.f, 20.f);
	cc->setPosition(900.f, 500.f);
	gui.add(cc);


	auto rnd = tgui::CheckBox::create("RANDOM");
	rnd->setSize(20.f, 20.f);
	rnd->setPosition(980.f, 500.f);
	gui.add(rnd);

	auto t1 = tgui::EditBox::create();
	t1->setSize(100.f, 20.f);
	t1->setPosition(820.f, 520.f);
	t1->setDefaultText("Iteracoes");
	gui.add(t1);

	auto t2 = tgui::EditBox::create();
	t2->setSize(100.f, 20.f);
	t2->setPosition(820.f, 540.f);
	t2->setDefaultText("Random it");
	gui.add(t2);
	
	auto b = tgui::Button::create("ativar");
	b->setSize(70.f, 20.f);
	b->setPosition(960.f, 520.f);
	gui.add(b);

	b->connect("pressed", getSpring, c, cc, rnd, t1, t2, calc);
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
	
	int calc = 1;
	int n = 0; //qtd de vértices

	// Tenta importar os widgets da gui
	try
	{
		loadWidgets(gui, &G, &calc, &n);
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

		printGrafo(janela, fonte, G, calc, n);

		gui.draw();

		// Termina iteração e atualiza janela
		janela.display();
	}

	return 0;
}
