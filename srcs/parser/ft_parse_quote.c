/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:17:48 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/10 21:17:49 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_parse_quote_error(const char *s, int i);

t_list	*ft_parse_quote(const char *s, int *i)
{
	t_list	*node;

	*i += 1;
	node = ft_parse_token(s, i, "\'");
	if (node == NULL)
		return (NULL);
	if (ft_parse_quote_error(s, *i) < 0)
	{
		ft_txtclear(&node);
		return (NULL);
	}
	*i += 1;
	return (node);
}

int	ft_parse_quote_error(const char *s, int i)
{
	if (s[i] == '\0')
	{
		ft_error("newline");
		return (-1);
	}
	return (0);
}
