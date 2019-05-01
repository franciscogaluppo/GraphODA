#include "display/Interface.hpp"

int main(int argc, char **argv, char **envp)
{
  for (char **env = envp; *env != 0; env++)
  {
    char *thisEnv = *env;
    printf("%s\n", thisEnv);
  }
  displayTeste(1200, 600);
  return 0;
}
