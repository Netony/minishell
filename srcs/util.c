/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:03:53 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/10 21:21:06 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	int		c;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return ((int)(((unsigned char)s2[0]) * (-1)));
	if (!s2)
		return ((unsigned char)s1[0]);
	while (s1[i] != 0 || s2[i] != 0)
	{
		c = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (c)
			return (c);
		i++;
	}
	return (0);
}

void	twodfree(char **twod)
{
	int	i;

	i = 0;
	while (twod[i])
	{
		free(twod[i]);
		i++;
	}
	free(twod);
}

void	freenull(char **str)
{
	free(*str);
	*str = NULL;
}
