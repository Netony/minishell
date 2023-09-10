/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_escape.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:17:42 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/10 21:17:43 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_parse_escape_text(const char *s, int *i, const char *set);
int		ft_parse_escape_error(const char *s, int i);

t_list	*ft_parse_escape(const char *s, int *i, const char *set)
{
	char	*text;
	t_list	*node;

	*i += 1;
	if (ft_parse_escape_error(s, *i) < 0)
		return (NULL);
	text = ft_parse_escape_text(s, i, set);
	if (text == NULL)
		return (NULL);
	node = ft_txtnew("text", text);
	if (node == NULL)
	{
		free(text);
		return (NULL);
	}
	*i += 1;
	return (node);
}

int	ft_parse_escape_error(const char *s, int i)
{
	if (s[i] == '\0')
	{
		ft_error("newline");
		return (-1);
	}
	return (0);
}

char	*ft_parse_escape_text(const char *s, int *i, const char *set)
{
	char	*text;

	if (set == NULL)
		text = ft_substr(s, *i, 1);
	else
	{
		if (ft_isin(s[*i], set))
			text = ft_substr(s, *i, 1);
		else
			text = ft_strdup("\\");
	}
	return (text);
}
