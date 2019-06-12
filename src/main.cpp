#include "Interface.hpp"
#include "Repl.hpp"

int main(int argc, char **argv) {
  if (argc > 1) repl::run(1000, 700);
  else interface::display(1000, 700);
  return 0;
}
