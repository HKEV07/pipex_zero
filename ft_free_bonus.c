/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:04:32 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/05 00:26:42 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
	free(str);
}

void	ft_free_pipe(t_pipex *ppx)
{
	close(ppx->infile);
	close(ppx->outfile);
	if (ppx->here_doc == 1)
		unlink("/tmp/temp_heredoc");
	free(ppx->pipend);
	write (1, "Env erorr\n", 11);
	exit (0);
}

void	ft_free_child(t_pipex *ppx)
{
	free(ppx->cmd_path);
	free(ppx->pipend);
	while (*ppx->path_str)
	{
		free(ppx->path_str);
		ppx->path_str++;
	}
}

void	ft_free_perent(t_pipex *ppx)
{
	close(ppx->infile);
	close(ppx->outfile);
	if (ppx->here_doc == 1)
		unlink("/tmp/temp_heredoc");
	free(ppx->cmd_path);
	free(ppx->pipend);
}
