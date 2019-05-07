#include "Repl.hpp"

void runRepl() {
	cout << "GraphODA" << endl;

	map<string, int> vars;
	vector<Graph> graphs;

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
		bool atribuicao = 0;
		while (ss >> c) {
			if (c == '=') {
				atribuicao = 1;
				break;
			}
			if (c == '>') break;
			var += c;
		}

		// coloca no map
		if (!vars.count(var)) {
			if (!atribuicao) {
				cout << "ERRO: " << var << " nao definido" << endl;
				continue;
			}
			vars[var] = graphs.size();
			graphs.push_back(Graph());
		}

		int i = vars[var];
		if (atribuicao) {
			string type;
			ss >> type;

			if (type == "import") {
				string file;
				ss >> file;
				auto j = lerGrafoArquivo(file);
				graphs[i] = j;
			} else {
				if (!vars.count(type)) {
					cout << "ERRO: " << type << " nao definido" << endl;
					continue;
				}
				graphs[i] = graphs[vars[type]];
			}
		} else {
			graphs[i] = displayTeste(1200, 600, graphs[i]);
		}
	}
}
