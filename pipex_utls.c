/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:59:26 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/05 00:36:01 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_ppx(t_pipex *ppx)
{
	close(ppx->infile);
	close(ppx->outfile);
	free(ppx->cmd0);
	while (*ppx->path_str)
	{
		free(*ppx->path_str);
		ppx->path_str++;
	}
	exit(0);
}

char	*ft_check_path(char **path_str, char *cmd0)
{
	char		*path;
	char		*cmd_path;

	while (*path_str)
	{
		cmd_path = ft_strjoin(*path_str, "/");
		path = ft_strjoin(cmd_path, cmd0);
		if (access(path, X_OK | F_OK) == 0)
		{
			return (path);
		}
		free(cmd_path);
		free(path);
		path_str++;
	}
	return (cmd0);
}

char	**ft_find_path(char **env)
{
	char		*new_path;
	char		**path_str;

	path_str = NULL;
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", 5))
		{
			new_path = *env;
			new_path += 5;
			path_str = ft_split(new_path, ':');
			break ;
		}
		env++;
	}
	return (path_str);
}
