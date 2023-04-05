/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:32:17 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/05 14:08:01 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_inp_out(t_pipex ppx)
{
	if (ppx.index == 0)
	{
		ft_duplicate(ppx.pipend[1], ppx.infile);
	}
	else if (ppx.index == ppx.nbrcmd - 1)
		ft_duplicate(ppx.outfile, ppx.pipend[2 * ppx.index - 2]);
	else
	{
		ft_duplicate(ppx.pipend[2 * ppx.index + 1], \
		ppx.pipend[2 * ppx.index - 2]);
	}
	ft_close_pipe(&ppx);
}

void	ft_child_proc(t_pipex ppx, char **env, char **cmd)
{
	char	*path;

	ppx.pr = fork();
	if (ppx.pr < 0)
		perror("fork");
	else if (!ppx.pr)
	{
		ft_inp_out(ppx);
		path = ft_find_path(env, cmd[0]);
		if (execve(path, cmd, env) < 0)
		{
			write(2, "Invalid input cmd\n", 19);
			ft_free_child(&ppx);
			exit(0);
		}
		waitpid(ppx.outfile, NULL, 0);
		waitpid(ppx.infile, NULL, 0);
	}
}

void	ft_creat_pipe(t_pipex ppx)
{
	int		l;

	l = 0;
	while (l < ppx.nbrcmd - 1)
	{
		if (pipe(ppx.pipend + 2 * l) < 0)
		{
			write(2, "pip error\n", 11);
			ft_free_pipe(&ppx);
			exit(0);
		}
		l++;
	}
}

void	ft_excute_cmd(t_pipex ppx, char **av, char **env)
{
	char	**cmd;
	int		i;

	i = 2 + ppx.here_doc;
	ppx.index = 0;
	while (ppx.index < ppx.nbrcmd)
	{
		cmd = ft_split(av[i], ' ');
		ft_child_proc(ppx, env, cmd);
		i++;
		ppx.index++;
		ft_free(cmd);
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipex		ppx;

	ft_in_out_file(ac, av, &ppx);
	if (ppx.here_doc == 0)
	{
		ppx.infile = open(av[1], O_RDONLY, 0777);
		ppx.outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (ppx.infile < 0)
			write(2, "infile not fond\n", 17);
		ft_check_inp(av);
	}
	else
	{
		ppx.outfile = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (ppx.outfile < 0)
			write(2, "infile not fond\n", 17);
	}
	ppx.nbrcmd = ac - 3 - ppx.here_doc;
	ppx.pipend = (int *)malloc(sizeof(int) * 2 * (ppx.nbrcmd - 1));
	ft_creat_pipe(ppx);
	ft_excute_cmd(ppx, av, env);
	waitpid(-1, NULL, 0);
	ft_free_perent(&ppx);
}
