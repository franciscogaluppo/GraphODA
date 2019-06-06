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

	// aux

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
		throw REPLVertexNotFoundException(s);
	}

	// errors

	void fileNotFoundError(string f) {
		cout << "ERROR: file '" << f << "' not found" << endl;
	}

	void undefinedVariableError(string var) {
		cout << "ERROR: undefined variable '" << var << "'" << endl;
	}

	void wrongTypeError(string var, int exp) {
		cout << "ERROR: " << var << " has type '"
			<< getType(graphs[vars[var]].type) << "'" << endl;
		cout << "\texpected '" << getType(exp) << "'" << endl;
	}

	void vertexNotFoundError(string v) {
		cout << "ERROR: vertex '" << v << "' not found" << endl;
	}

	void noPathError(string a, string b) {
		cout << "ERROR: no path from '" << a << "' to '" << b << "'" << endl;
	}

	void negativeCycleError() {
		cout << "ERROR: graph has a negative cycle" << endl;
	}

	// commands

	void import() {
		string file;
		if (!(ss >> file)) throw REPLInvalidCommandException();
		Graph j;
		try {
			j = lerGrafoArquivo(file);
		} catch (FileNotFoundException &e) {
			fileNotFoundError(file);
			return;
		}
		if (j.getN()) {
			graphs[at].G = j;
			graphs[at].type = 0;
		}
	}

	void mst() {
		string var2;
		if (!(ss >> var2)) throw REPLInvalidCommandException();
		if (!vars.count(var2)) {
			undefinedVariableError(var2);
			return;
		}
		if (graphs[vars[var2]].type != 0) {
			wrongTypeError(var2, 0);
			return;
		}
		graphs[at].T = graphs[vars[var2]].G.mst();
		graphs[at].type = 4;
	}

	void show() {
		displayTeste(1200, 700, getGraph());
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
		if (!(ss >> a >> b)) throw REPLInvalidCommandException();
		int aa, bb;
		try {
			aa = getVertex(G, a);
		} catch (REPLVertexNotFoundException &e) {
			vertexNotFoundError(a);
			return;
		}
		try {
			bb = getVertex(G, b);
		} catch (REPLVertexNotFoundException &e) {
			vertexNotFoundError(b);
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
		if (!(ss >> a >> b)) throw REPLInvalidCommandException();
		Graph G = getGraph();
		int aa, bb;
		try {
			aa = getVertex(G, a);
		} catch (REPLVertexNotFoundException &e) {
			vertexNotFoundError(a);
			return;
		}
		try {
			bb = getVertex(G, b);
		} catch (REPLVertexNotFoundException &e) {
			vertexNotFoundError(b);
			return;
		}
		try {
			cout << G.shortestPath(aa, bb) << endl;
		} catch (GraphNoPathException &e) {
			noPathError(a, b);
		} catch (GraphNegativeCycleException &e) {
			negativeCycleError();
		}
	}

	void coloring()
	{
		Graph H = getGraph();
		if(!H.isChordal())
		{
			cout << "Work in progess :p" << endl;
			return;
		}	

		Chordal G(H);
		cout << "Coloring" << endl << endl;
		vector<int> cores = G.coloring();
		for(int i = 0; i < G.getN(); i++)
			cout << G.label[i] << ": " << cores[i] << endl;
	}

	void chromaticNumber()
	{
		Graph H = getGraph();
		if(!H.isChordal())
		{
			cout << "Work in progess :p" << endl;
			return;
		}	
	
		Chordal G(H);
		cout << "Chromatic number: " << G.chromaticNumber() << endl;
	}

	void greedyColoring()
	{
		Graph G = getGraph();
		cout << "Coloring" << endl << endl;
		vector<int> cores = G.greedyColoring();
		for(int i = 0; i < G.getN(); i++)
			cout << G.label[i] << ": " << cores[i] << endl;
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
					undefinedVariableError(var);
					continue;
				}
				vars[var] = graphs.size();
				TYPE new_;
				new_.G = Graph();
				new_.type = 0;
				graphs.push_back(new_);
			}

			at = vars[var];
			try {
				if (atribuicao) {
					string com;
					ss >> com;

					if (com == "import") import();
					else if (com == "mst") mst();
					else {
						// a = b
						if (!vars.count(com)) {
							undefinedVariableError(com);
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
					else if (com == "coloring") coloring();
					else if (com == "chromatic_number") chromaticNumber();
					else if (com == "greedy_coloring") greedyColoring();
				}
			} catch (REPLInvalidCommandException &e) {
				cout << "ERROR: invalid command" << endl;	
			}
		}
	}
}
