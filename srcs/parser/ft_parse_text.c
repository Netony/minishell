/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:48:27 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/10 21:17:59 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*ft_parse_text_list(t_info *info, const char *s, int *i)
{
	t_list	*list;
	t_list	*node;

	*i += ft_duplen(s, *i, " ");
	list = NULL;
	while (1)
	{
		if (s[*i] == '\0' || ft_isin(s[*i], " <>|"))
			break ;
		node = ft_parse_text_node(info, s, i);
		if (node == NULL)
		{
			ft_lstclear(&list, free);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
	}
	return (list);
}

t_list	*ft_parse_text_node(t_info *info, const char *s, int *i)
{
	t_list	*node;

	if (s[*i] == '$')
		node = ft_parse_env(info, s, i);
	else if (s[*i] == '\"')
		node = ft_parse_dquote(info, s, i);
	else if (s[*i] == '\'')
		node = ft_parse_quote(s, i);
	else if (s[*i] == '\\')
		node = ft_parse_escape(s, i, NULL);
	else
		node = ft_parse_token(s, i, "$\"\'\\ <|>");
	return (node);
}
