/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:58:22 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/05 14:14:46 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		pipend[2];
	int		infile;
	pid_t	pr;
	int		outfile;
	char	*cmd0;
	char	**cmd1;
	char	**cmd2;
	char	*str_path_join;
	char	**path_str;
	char	*cmd_path;
}t_pipex;

char	*ft_strnstr(const char *s1, const char *s2, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_find_path(char **env);
char	*ft_check_path(char **path_str, char *cmd0);
void	ft_free_child(t_pipex *ppx);
void	ft_free_perent(t_pipex *ppx);
void	ft_free_ppx(t_pipex *ppx);
void	ft_exit_nf(int i);
#endif