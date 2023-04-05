/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenaait <ibenaait@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 21:18:50 by ibenaait          #+#    #+#             */
/*   Updated: 2023/04/01 00:12:42 by ibenaait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[i] == '\0')
		return ((char *)s1);
	if (size == 0)
		return (0);
	while (s1[i] && i < size)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s2[j] == s1[i + j] && j + i < size)
			{
				j++;
				if (!s2[j])
					return ((char *)(s1 + i));
			}
		}
		i++;
	}
	return (0);
}
