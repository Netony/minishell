/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:48:56 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/10 21:43:49 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_max(int a, int b);

int	ft_toklen(const char *s, int start, const char *set)
{
	int	len;

	len = 0;
	while (s[start + len])
	{
		if (ft_isin(s[start + len], set))
			break ;
		len++;
	}
	return (len);
}

int	ft_toklen_zero(const char *s, int start, const char *set)
{
	int	len;

	len = 0;
	while (s[start + len])
	{
		if (ft_isin(s[start + len], set))
			return (len);
		len++;
	}
	return (-1);
}

int	ft_duplen(const char *s, int start, const char *set)
{
	int	len;

	len = 0;
	while (s[start + len])
	{
		if (!ft_isin(s[start + len], set))
			break ;
		len++;
	}
	return (len);
}

int	ft_isin(int a, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_lstjoin(t_list *lst)
{
	char	*join;
	char	*new;
	char	*temp;

	join = ft_strdup("");
	while (lst)
	{
		new = lst->content;
		temp = join;
		join = ft_strjoin(join, new);
		free(temp);
		if (join == NULL)
			return (NULL);
		lst = lst->next;
	}
	return (join);
}
