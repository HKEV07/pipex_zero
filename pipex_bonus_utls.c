/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus_utls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:36:39 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/05 00:11:00 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_check_inp(char **av)
{
	if (access(av[1], F_OK) < 0)
	{
		write(1, "Infile not fond\n", 17);
		exit(0);
	}
}

void	ft_duplicate(int out, int in)
{
	dup2(out, STDOUT_FILENO);
	dup2(in, STDIN_FILENO);
}

char	*ft_check_path(t_pipex *ppx, char *cmd0)
{
	char		*path;

	while (*ppx->path_str)
	{
		ppx->cmd_path = ft_strjoin(*ppx->path_str, "/");
		path = ft_strjoin(ppx->cmd_path, cmd0);
		if (access(path, X_OK | F_OK) == 0)
			return (path);
		free(ppx->cmd_path);
		free(path);
		ppx->path_str++;
	}
	return (cmd0);
}

char	*ft_find_path(char **env, char *cmd0)
{
	char		*new_path;
	t_pipex		ppx;

	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", 5))
		{
			new_path = *env;
			new_path += 5;
			ppx.path_str = ft_split(new_path, ':');
			break ;
		}
		env++;
	}
	return (ft_check_path(&ppx, i, cmd0));
}

void	ft_close_pipe(t_pipex *ppx)
{
	int		i;

	i = 0;
	while (i < 2 * (ppx->nbrcmd - 1))
	{
		close(ppx->pipend[i]);
		i++;
	}
}
