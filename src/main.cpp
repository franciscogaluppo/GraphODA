#include "Interface.hpp"
#include "Repl.hpp"

int main(int argc, char **argv) {
  if (argc > 1)
    runRepl();
  else
    displayTeste(1200, 600);
  return 0;
}
