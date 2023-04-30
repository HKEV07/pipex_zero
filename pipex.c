/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:33:01 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/03 19:51:04 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_find_path(char **env, char *cmd0, t_pipex *ppx)
{
	char		*new_path;

	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", 5))
		{
			new_path = *env;
			new_path += 5;
			ppx->path_str = ft_split(new_path, ':');
			break ;
		}
		env++;
	}
	while (*ppx->path_str)
	{
		ppx->cmd_path = ft_strjoin(*ppx->path_str, "/");
		ppx->cmd_path = ft_strjoin(ppx->cmd_path, cmd0);
		if (access(ppx->cmd_path, X_OK | F_OK) == 0)
			break ;
		ppx->path_str++;
	}
}

void	ft_excmd1(t_pipex *ppx, char **env)
{
	close(ppx->pipend[0]);
	dup2(ppx->pipend[1], STDOUT_FILENO);
	dup2(ppx->infile, STDIN_FILENO);
	close(ppx->pipend[1]);
	ppx->cmd0 = ppx->cmd1[0];
	printf("path == %s",ppx->cmd0);
	ft_find_path(env, ppx->cmd0, ppx);
	if(execve(ppx->cmd_path, ppx->cmd1, env) < 0)
		perror("Invalid input");
}

void ft_excmd2(t_pipex *ppx, char **env)
{
    close(ppx->pipend[1]);
	dup2(ppx->pipend[0], STDIN_FILENO);
	dup2(ppx->outfile, STDOUT_FILENO);
	close(ppx->pipend[0]);
	ppx->cmd0 = ppx->cmd2[0];
	printf("path == %s",ppx->cmd_path);
	ft_find_path(env, ppx->cmd0, ppx);
	if(execve(ppx->cmd_path, ppx->cmd2, env) < 0)
		perror("Invalid input");
}

void	ft_excmd(t_pipex *ppx, char **env)
{
	ppx->pr =fork();
    if(ppx->pr < 0)
		perror("fork");
    else if(ppx->pr == 0)
    	ft_excmd1(ppx, env);
    else
        ft_excmd2(ppx, env);
}

int	main(int ac, char **av, char **env)
{
	t_pipex ppx;

	if (ac == 5)
	{
		ppx.infile = open(av[1], O_RDONLY ,0777);
		ppx.outfile = open(av[4], O_CREAT | O_WRONLY , 0777);
		if (ppx.outfile < 0 || ppx.infile < 0)
			perror("Invalid file descriptor");
		ppx.cmd1 = ft_split(av[2], ' ');
		ppx.cmd2 = ft_split(av[3], ' ');
		if(pipe(ppx.pipend) < 0)
			perror("pipe field");
		ft_excmd(&ppx, env);
	}else
		write(1, "Invalid Input\n",15);
}
