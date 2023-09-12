/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 21:17:20 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/12 21:17:21 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*ft_parse_here_doc(t_info *info, const char *s, int *i)
{
	t_list	*text;
	t_list	*merge;

	*i += 1;
	text = ft_parse_dquote_base(info, s, i);
	if (text == NULL)
		return (NULL);
	*i += 1;
	merge = ft_dquote_merge(text);
	ft_txtclear(&text);
	if (merge == NULL)
		return (NULL);
	return (merge);
}

t_list	*ft_parse_dquote_base(t_info *info, const char *s, int *i)
{
	t_list	*list;
	t_list	*node;

	list = ft_emptynew();
	if (list == NULL)
		return (NULL);
	while (s[*i])
	{
		if (s[*i] == '$')
			node = ft_parse_env(info, s, i);
		else if (s[*i] == '\\')
			node = ft_parse_escape(s, i, "$");
		else
			node = ft_parse_token(s, i, "$");
		if (node == NULL)
		{
			ft_txtclear(&list);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
	}
	return (list);
}
