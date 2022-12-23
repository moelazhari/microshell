/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:50:08 by mazhari           #+#    #+#             */
/*   Updated: 2022/12/23 15:00:17 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

void ft_cd(char *path)
{
    if (chdir(path) == -1)
    {
        write(2, "error: cd: cannot change directory to", 31);
        write(2, path, ft_strlen(path));
        write(2, "\n", 1);
    }
}

void exec(char **cmd, char **env)
{
    int pid;

    pid = fork();
    if (pid == -1)
        write(2, "error: fatal" , 12);
    else if (pid == 0)
    {
        if (execve(cmd[0], &cmd[0], env) == -1)
            {
                write(2, "error: cannot execute", 30);
                write(2, cmd[0], ft_strlen(cmd[0]));
                write(2, "\n", 1);
            }
    }
}

char **get_cmd(char **av, int n)
{
    int i;
    char **cmd;
    
    i = 0;
    if (!(cmd = malloc(sizeof(char *) * n + 2)))
         write(2, "error: fatal" , 12);
    while (i < n)
    {
        cmd[i] = strdup(av[i]);
        i++;
    }
    cmd[i] = NULL;
    return (cmd);
}

int main(int ac, char **av, char **env)
{
    int i;
    char **cmd;
    
    i = 0;
    av = av + 1;
    while (av[i])
    {
        if (strcmp(av[i], "|") == 0)
        {
            printf("%s\n", av[0]);
            cmd = get_cmd(av, i);
            exec(cmd ,env);
            av = av + i + 1;
            i = 0;
        }
        // if (strcmp(av[i], ";") == 0)
        // {
        //     dup2(tmp[0], STDIN_FILENO);
        //     dup2(tmp[1], STDOUT_FILENO);
        //     cmd = get_cmd(av, i);
        //     exec(cmd ,env);
        // }
        i++;
    } 
    return (0); 
}

