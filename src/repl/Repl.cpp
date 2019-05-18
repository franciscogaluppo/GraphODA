#include "Repl.hpp"

class TYPE {
	public:
		Graph G;
		Bipartite B;
		Chordal C;
		Dag D;
		Tree T;

		int type;
};

string getType(int i) {
	if (i == 0) return "Graph";
	if (i == 1) return "Bipartite";
	if (i == 2) return "Chordal";
	if (i == 3) return "Dag";
	if (i == 4) return "Tree";
}

void runRepl() {
	cout << "GraphODA" << endl;

	map<string, int> vars;
	vector<TYPE> graphs;

	while (1) {
		cout << ">>> ";

		// le a linha
		string l;
		getline(cin, l);
		// acabou
		if (!cin) {
			cout << endl;
			break;
		}

		stringstream ss(l);
		string var;
		char c;
		int atribuicao = -1;
		while (ss >> c) {
			if (c == '=') {
				atribuicao = 1;
				break;
			}
			if (c == '>') {
				atribuicao = 0;
				break;
			}
			var += c;
		}
		if (atribuicao == -1) {
			cout << "ERRO: seu comando ta na Disney" << endl;
			continue;
		}

		// coloca no map
		if (!vars.count(var)) {
			if (!atribuicao) {
				cout << "ERRO: " << var << " nao definido" << endl;
				continue;
			}
			vars[var] = graphs.size();
			TYPE new_;
			new_.G = Graph();
			new_.type = 0;
			graphs.push_back(new_);
		}

		int i = vars[var];
		if (atribuicao) {
			string com;
			ss >> com;

			if (com == "import") {
				string file;
				ss >> file;
				auto j = lerGrafoArquivo(file);
				graphs[i].G = j;
				graphs[i].type = 0;
			} else if (com == "mst") {
				string var2;
				ss >> var2;
				if (!vars.count(var2)) {
					cout << "ERRO: " << var2 << " nao definido" << endl;
					continue;
				}
				if (graphs[vars[var2]].type != 0) {
					cout << "ERRO: " << var2 << " eh do tipo " <<
						getType(graphs[vars[var2]].type) << endl;
					cout << "\tesperava tipo " << getType(0) << endl;
					continue;
				}
				graphs[i].T = graphs[vars[var2]].G.mst();
				graphs[i].type = 4;
			} else {
				// a = b
				if (!vars.count(com)) {
					cout << "ERRO: " << com << " nao definido" << endl;
					continue;
				}
				graphs[i].type = graphs[vars[com]].type;
				if (graphs[i].type == 0) graphs[i].G = graphs[vars[com]].G;
				if (graphs[i].type == 1) graphs[i].B = graphs[vars[com]].B;
				if (graphs[i].type == 2) graphs[i].C = graphs[vars[com]].C;
				if (graphs[i].type == 3) graphs[i].D = graphs[vars[com]].D;
				if (graphs[i].type == 4) graphs[i].T = graphs[vars[com]].T;
			}
		} else {
			string com;
			ss >> com;

			if (com == "display") {
				Graph G;
				if (graphs[i].type == 0) G = Graph(graphs[i].G);
				if (graphs[i].type == 1) G = Graph(graphs[i].B);
				if (graphs[i].type == 2) G = Graph(graphs[i].C);
				if (graphs[i].type == 3) G = Graph(graphs[i].D);
				if (graphs[i].type == 4) G = Graph(graphs[i].T);
				displayTeste(1200, 600, G);
			} else if (com == "edit") {
				Graph G;
				if (graphs[i].type == 0) G = Graph(graphs[i].G);
				if (graphs[i].type == 1) G = Graph(graphs[i].B);
				if (graphs[i].type == 2) G = Graph(graphs[i].C);
				if (graphs[i].type == 3) G = Graph(graphs[i].D);
				if (graphs[i].type == 4) G = Graph(graphs[i].T);
				
				graphs[i].G = displayTeste(1200, 600, G);
				graphs[i].type = 0;
			} else if (com == "type")
				cout << "Type of " << var << ": " << getType(graphs[i].type) << endl;
		}
	}
}
