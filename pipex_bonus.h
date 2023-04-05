/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 17:17:18 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/05 00:10:08 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	pid_t	pr;
	int		*pipend;
	int		index;
	int		nbrcmd;
	char	**path_str;
	char	*cmd_path;
	int		here_doc;
}t_pipex;

char	*ft_strnstr(const char *s1, const char *s2, size_t size);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_find_path(char **env, char *cmd0);
void	ft_check_inp(char **av);
void	ft_close_pipe(t_pipex *ppx);
void	ft_duplicate(int one, int zero);
size_t	ft_strlen(char *s);
int		find_new_line(char *str);
char	*ft_get_line(char *remaining);
char	*ft_save_remaining(char *remaining, int *flag);
char	*get_next_line(int fd);
void	ft_here_doc(char **av, t_pipex *ppx);
int		ft_check_heredoc(char **av, t_pipex *ppx);
void	ft_in_out_file(int ac, char **av, t_pipex *ppx);
void	ft_free_pipe(t_pipex *ppx);
void	ft_free_perent(t_pipex *ppx);
void	ft_free_child(t_pipex *ppx);
void	ft_free(char **str);
#endif