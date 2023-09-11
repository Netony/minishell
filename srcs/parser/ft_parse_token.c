/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:53:20 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/11 19:21:57 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*ft_parse_size(const char *s, int *i, int size)
{
	t_list	*node;
	char	*text;

	text = ft_substr(s, *i, size);
	if (text == NULL)
		return (NULL);
	*i += size;
	node = ft_txtnew("redi", text);
	if (node == NULL)
		return (NULL);
	return (node);
}

t_list	*ft_parse_token(const char *s, int *i, const char *set)
{
	t_list	*node;
	char	*text;
	int		len;

	len = ft_toklen(s, *i, set);
	text = ft_substr(s, *i, len);
	if (text == NULL)
		return (NULL);
	*i += len;
	node = ft_txtnew("text", text);
	if (node == NULL)
		return (NULL);
	return (node);
}

t_list	*ft_parse_space(const char *s, int *i)
{
	t_list	*node;
	char	*text;
	int		len;

	len = ft_duplen(s, *i, " ");
	text = ft_substr(s, *i, len);
	if (text == NULL)
		return (NULL);
	*i += len;
	node = ft_txtnew("space", text);
	if (node == NULL)
		return (NULL);
	return (node);
}

t_list	*ft_emptynew(void)
{
	char	*s;
	t_list	*node;

	s = ft_strdup("");
	if (s == NULL)
		return (NULL);
	node = ft_txtnew("text", s);
	if (node == NULL)
	{
		free(s);
		return (NULL);
	}
	return (node);
}

t_list	*ft_nonenew(void)
{
	t_list	*node;

	node = ft_txtnew("none", NULL);
	if (node == NULL)
		return (NULL);
	return (node);
}
