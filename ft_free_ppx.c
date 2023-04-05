/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ppx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:16:40 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/05 14:15:55 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_child(t_pipex *ppx)
{
	free(ppx->cmd_path);
	free(ppx->pipend);
	exit (0);
}

void	ft_exit_nf(int i)
{
	if (i == 1)
		write(1, "Infile not fond\n", 17);
	else if (i == 2)
		write(1, "pipe erorr\n", 12);
	else if (i == 3)
		write(1, "Invalid Input\n", 15);
	exit (0);
}

void	ft_free_perent(t_pipex *ppx)
{
	close(ppx->infile);
	close(ppx->outfile);
	free(ppx->cmd_path);
	free(ppx->pipend);
	exit (0);
}
