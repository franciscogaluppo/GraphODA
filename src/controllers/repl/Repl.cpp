#include "Repl.hpp"

namespace repl {

	class TYPE {
		public:
			Graph G;
			Bipartite B;
			Chordal C;
			Dag D;
			Tree T;

			int type;
	};

	vector<TYPE> graphs;
	map<string, int> vars;
	stringstream ss;
	string var;
	int at;

	string getType(int i) {
		if (i == 0) return "Graph";
		if (i == 1) return "Bipartite";
		if (i == 2) return "Chordal";
		if (i == 3) return "Dag";
		if (i == 4) return "Tree";
	}

	Graph getGraph() {
		Graph G;
		if (graphs[at].type == 0) G = Graph(graphs[at].G);
		if (graphs[at].type == 1) G = Graph(graphs[at].B);
		if (graphs[at].type == 2) G = Graph(graphs[at].C);
		if (graphs[at].type == 3) G = Graph(graphs[at].D);
		if (graphs[at].type == 4) G = Graph(graphs[at].T);
		return G;
	}

	int getVertex(Graph& G, string s) {
		for (int i = 0; i < G.getN(); i++) if (G.label[i] == s) return i;
		return -1;
	}

	void import() {
		string file;
		ss >> file;
		Graph j;
		try {
			j = lerGrafoArquivo(file);
		} catch (FileNotFoundException &e) {
			cout << "ERROR: file not found" << endl;
			return;
		}
		if (j.getN()) {
			graphs[at].G = j;
			graphs[at].type = 0;
		}
	}

	void mst() {
		string var2;
		ss >> var2;
		if (!vars.count(var2)) {
			cout << "ERROR: undefined variable " << var2 << endl;
			return;
		}
		if (graphs[vars[var2]].type != 0) {
			cout << "ERROR: " << var2 << " has type "
				<< getType(graphs[vars[var2]].type) << endl;
			cout << "\texpected " << getType(0) << endl;
			return;
		}
		graphs[at].T = graphs[vars[var2]].G.mst();
		graphs[at].type = 4;
	}

	void show() {
		displayTeste(1200, 600, getGraph());
	}

	void edit() {
		graphs[at].G = displayTeste(1200, 600, getGraph());
		graphs[at].type = 0;
	}

	void describe() {
		Graph G = getGraph();
		cout << "Type of " << var << ": " << getType(graphs[at].type) << endl;
		cout << G.getN() << " vertices and " << G.getM() << " edges" << endl;
		cout << endl;

		cout << "bipartite:   ";
		if (G.isBipartite()) cout << "yes" << endl;
		else cout << " no" << endl;

		cout << "chordal:     ";
		if (G.isChordal()) cout << "yes" << endl;
		else cout << " no" << endl;

		cout << "dag:         ";
		if (G.isDag()) cout << "yes" << endl;
		else cout << " no" << endl;

		cout << "tree:        ";
		if (G.isTree()) cout << "yes" << endl;
		else cout << " no" << endl;
	}

	void reaches() {
		Graph G = getGraph();
		string a, b;
		ss >> a >> b;
		int aa = getVertex(G, a), bb = getVertex(G, b);
		if (aa == -1) {
			cout << "ERROR: vertex " << a << " not found" << endl;
			return;
		}
		if (bb == -1) {
			cout << "ERROR: vertex " << b << " not found" << endl;
			return;
		}

		if (G.reaches(aa, bb)) cout << "true" << endl;
		else cout << "false" << endl;
	}

	// O(n+m)
	void scc() {
		Graph G = getGraph();
		auto v = G.scc();
		int ma = 0;
		for (int i : v) ma = max(ma, i);
		cout << ma+1 << " strongly connected componentes" << endl << endl;

		vector<vector<int> > v2(ma+1);
		for (int i = 0; i < G.getN(); i++) v2[v[i]].push_back(i);
		for (int i = 0; i <= ma; i++) {
			cout << i+1 << ":";
			for (int j : v2[i]) cout << " " << G.label[j];
			cout << endl;
		}
	}

	void shortestPath() {
		string a, b;
		ss >> a >> b;
		Graph G = getGraph();
		int aa = getVertex(G, a), bb = getVertex(G, b);
		if (aa == -1) {
			cout << "ERROR: vertex " << a << " not found" << endl;
			return;
		}
		if (bb == -1) {
			cout << "ERROR: vertex " << b << " not found" << endl;
			return;
		}
		try {
			cout << G.shortestPath(aa, bb) << endl;
		} catch (GraphNoPathException &e) {
			cout << "ERROR: no path from " << a << " to " << b << endl;	
		}
	}

	void run() {
		cout << "GraphODA" << endl;

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

			ss = stringstream(l);
			var.clear();
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
				cout << "ERROR: what are you doing?" << endl;
				continue;
			}

			// coloca no map
			if (!vars.count(var)) {
				if (!atribuicao) {
					cout << "ERROR: undefined variable " << var << endl;
					continue;
				}
				vars[var] = graphs.size();
				TYPE new_;
				new_.G = Graph();
				new_.type = 0;
				graphs.push_back(new_);
			}

			at = vars[var];
			if (atribuicao) {
				string com;
				ss >> com;

				if (com == "import") import();
				else if (com == "mst") mst();
				else {
					// a = b
					if (!vars.count(com)) {
						cout << "ERROR: undefined variable " << com << endl;
						continue;
					}
					graphs[at].type = graphs[vars[com]].type;
					if (graphs[at].type == 0) graphs[at].G = graphs[vars[com]].G;
					if (graphs[at].type == 1) graphs[at].B = graphs[vars[com]].B;
					if (graphs[at].type == 2) graphs[at].C = graphs[vars[com]].C;
					if (graphs[at].type == 3) graphs[at].D = graphs[vars[com]].D;
					if (graphs[at].type == 4) graphs[at].T = graphs[vars[com]].T;
				}
			} else {
				string com;
				ss >> com;

				if (com == "show") show();
				else if (com == "edit") edit();
				else if (com == "describe") describe();
				else if (com == "reaches") reaches();
				else if (com == "scc") scc();
				else if (com == "shortestPath") shortestPath();
			}
		}
	}
}
