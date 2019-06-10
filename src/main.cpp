#include "Interface.hpp"
#include "Repl.hpp"

int main(int argc, char **argv) {
	if (argc > 1)
		repl::run(1200, 700);
	else
		displayTeste(1200, 700);
	return 0;
}
