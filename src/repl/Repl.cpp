#include "Repl.hpp"

class TYPE {
	public:
		Graph G;
		Bipartite B;
		Chordal C;
		Dag D;
		Tree T;
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
	vector<int> type;

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
			graphs.push_back(new_);
			type.push_back(0);
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
				type[i] = 0;
			} else if (com == "mst") {
				string var2;
				ss >> var2;
				if (!vars.count(var2)) {
					cout << "ERRO: " << var2 << " nao definido" << endl;
					continue;
				}
				if (type[vars[var2]] != 0) {
					cout << "ERRO: " << var2 << " eh do tipo " <<
						getType(type[vars[var2]]) << endl;
					cout << "\tesperava tipo " << getType(0) << endl;
					continue;
				}
				graphs[i].T = mst(graphs[vars[var2]].G);
				type[i] = 4;
			} else {
				// a = b
				if (!vars.count(com)) {
					cout << "ERRO: " << com << " nao definido" << endl;
					continue;
				}
				type[i] = type[vars[com]];
				if (type[i] == 0) graphs[i].G = graphs[vars[com]].G;
				if (type[i] == 1) graphs[i].B = graphs[vars[com]].B;
				if (type[i] == 2) graphs[i].C = graphs[vars[com]].C;
				if (type[i] == 3) graphs[i].D = graphs[vars[com]].D;
				if (type[i] == 4) graphs[i].T = graphs[vars[com]].T;
			}
		} else {
			string com;
			ss >> com;

			if (com == "display") {
				if (type[i] == 0)
					graphs[i].G = displayTeste(1200, 600, graphs[i].G);
				if (type[i] == 1)
					graphs[i].G = displayTeste(1200, 600, graphs[i].B);
				if (type[i] == 2)
					graphs[i].G = displayTeste(1200, 600, graphs[i].C);
				if (type[i] == 3)
					graphs[i].G = displayTeste(1200, 600, graphs[i].D);
				if (type[i] == 4)
					graphs[i].G = displayTeste(1200, 600, graphs[i].T);
			}else if (com == "type")
				cout << "Type of " << var << ": " << getType(type[i]) << endl;
		}
	}
}
