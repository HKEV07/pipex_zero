/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:33:01 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/05 14:17:31 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_excmd1(t_pipex ppx, char **env)
{
	close(ppx.pipend[0]);
	dup2(ppx.pipend[1], STDOUT_FILENO);
	dup2(ppx.infile, STDIN_FILENO);
	close(ppx.pipend[1]);
	ppx.cmd0 = ppx.cmd1[0];
	ppx.path_str = ft_find_path(env);
	ppx.cmd_path = ft_check_path(ppx.path_str, ppx.cmd0);
	if (execve(ppx.cmd_path, ppx.cmd1, env) < 0)
	{
		write(2, "Invalid input cmd 1\n", 21);
		ft_free_ppx(&ppx);
	}
}

void	ft_excmd2(t_pipex ppx, char **env)
{
	close(ppx.pipend[1]);
	dup2(ppx.pipend[0], STDIN_FILENO);
	dup2(ppx.outfile, STDOUT_FILENO);
	close(ppx.pipend[0]);
	ppx.cmd0 = ppx.cmd2[0];
	ppx.path_str = ft_find_path(env);
	ppx.cmd_path = ft_check_path(ppx.path_str, ppx.cmd0);
	if (execve(ppx.cmd_path, ppx.cmd2, env) < 0)
	{
		write(2, "Invalid input cmd 2\n", 21);
		ft_free_ppx(&ppx);
	}
}

void	ft_excmd(t_pipex ppx, char **env)
{
	ppx.pr = fork();
	if (ppx.pr < 0)
		perror("fork");
	else if (ppx.pr == 0)
		ft_excmd1(ppx, env);
	else
		ft_excmd2(ppx, env);
}

int	main(int ac, char **av, char **env)
{
	t_pipex		ppx;

	if (ac == 5)
	{
		ppx.infile = open(av[1], O_RDONLY, 0777);
		if (ppx.infile < 0)
			ft_exit_nf(1);
		ppx.outfile = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		ppx.cmd1 = ft_split(av[2], ' ');
		ppx.cmd2 = ft_split(av[3], ' ');
		if (pipe(ppx.pipend) < 0)
		{
			ft_exit_nf(2);
		}
		ft_excmd(ppx, env);
	}
	else
		ft_exit_nf(3);
}
