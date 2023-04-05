/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:58:35 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/04 01:23:03 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_read_from_temp(t_pipex *ppx)
{
	ppx->infile = open("/tmp/temp_heredoc", O_RDONLY, 0777);
	if (ppx->infile < 0)
		perror("Invalid file descriptor1");
}

int	ft_check_heredoc(char **av, t_pipex *ppx)
{
	if (ft_strnstr("here_doc", av[1], 9))
	{
		ppx->here_doc = 1;
		return (6);
	}
	else
	{
		ppx->here_doc = 0;
		return (5);
	}
}

void	ft_in_out_file(int ac, char **av, t_pipex *ppx)
{
	if (ac < ft_check_heredoc(av, ppx))
	{
		write(2, "Invalid Input\n", 15);
		exit(0);
	}
	else if (ppx->here_doc == 1)
		ft_here_doc(av, ppx);
}

void	ft_here_doc(char **av, t_pipex *ppx)
{
	char	*bufer;
	int		fd;

	fd = open("/tmp/temp_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	while (1)
	{
		write(1, "heredoc>", 9);
		bufer = get_next_line(STDIN_FILENO);
		if (ft_strnstr(bufer, av[2], ft_strlen(bufer)))
			break ;
		write(fd, bufer, ft_strlen(bufer));
		free(bufer);
	}
	ft_read_from_temp(ppx);
}
