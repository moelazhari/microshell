#include "microshell.h"


int main(int ac, char **av, char **env)
{
    char *cmd[2] = {"/bin/ls", NULL};
    execve(cmd[0], &cmd[0], env);
}