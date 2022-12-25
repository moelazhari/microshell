/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mazhari <mazhari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 13:50:08 by mazhari           #+#    #+#             */
/*   Updated: 2022/12/25 19:13:47 by mazhari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int fd_in;

int print(char *string)
{
	while (*string)
		write(2, string++, 1);
	return 1;
}

int ft_cd(char **av, int i)
{
	if (i != 2)
		return print("error: cd: bad arguments\n");
	if (chdir(av[1]) == -1)
		return print("error: cd: cannot change directory to ") & print(av[1]) & print("\n");
	return 0;
}

int exec(char **av, int i, char **env)
{
	int p[2];
	int ispipe = (av[i] && !strcmp(av[i], "|"));
	
    if (!strcmp(*av, "cd"))
        return (ft_cd(av, i));
	if (ispipe)
        if (pipe(p) == -1)
		    return print("error: fatal\n");
	int pid = fork();
	if (pid == 0)
	{
		av[i] = NULL;
		if (dup2(fd_in, 0) == -1 || close(fd_in) == -1)
			return print("error: fatal\n");
        if (ispipe)
           if (dup2(p[1], 1) == -1 || close(p[1]) == -1 || close(p[0]) == -1)
				return print("error: fatal\n");
		execve(*av, av, env);
		return print("error: cannot execute ") & print(*av) & print("\n");
	}
    if (dup2(0, fd_in) == -1)
		return print("error: fatal\n");
    if (ispipe)
        if (dup2(p[0], fd_in) == -1 || close(p[0]) == -1 || close(p[1]) == -1)
			return print("error: fatal\n");
	return 0;
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	int i = 0;

	fd_in = dup(0);
	av += 1;
	while (av[i])
	{
		while (av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if (i)
			if (exec(av, i, env))
				return (1);
        if (!av[i])
            break ;
		av += i + 1;
		i = 0;
	}
	while (wait(NULL) > 0);
	if (dup2(fd_in, 0) == -1 || close(fd_in) == -1)
		print("error: fatal\n");
	return (0);
}