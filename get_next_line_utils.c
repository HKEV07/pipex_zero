/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:22:17 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/01 18:03:44 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	find_new_line(char *str)
{
	int		i;

	i = 0;
	if (str)
		while (str[i])
			if (str[i++] == '\n')
				return (1);
	return (0);
}

char	*ft_get_line(char *remaining)
{
	char	*line;
	int		i;

	i = 0;
	if (!remaining[i])
		return (0);
	while (remaining[i] && remaining[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (0);
	i = 0;
	while (remaining[i] && remaining[i] != '\n')
	{
		line[i] = remaining[i];
		i++;
	}
	if (remaining[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

char	*ft_save_remaining(char *remaining, int *flag)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (remaining[i] && remaining[i] != '\n')
		i++;
	if (!remaining[i])
	{
		free(remaining);
		return (0);
	}
	str = malloc(ft_strlen(remaining) + 1 - i);
	if (!str)
	{
		*flag = 1;
		free(remaining);
		return (0);
	}
	j = 0;
	while (remaining[++i])
		str[j++] = remaining[i];
	str[j] = 0;
	free(remaining);
	return (str);
}
