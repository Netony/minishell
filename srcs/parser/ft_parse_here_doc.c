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

t_list	*ft_parse_here_doc_base(t_info *info, const char *s);

t_list	*ft_parse_here_doc(t_info *info, const char *s)
{
	t_list	*text;
	char	*merge;

	text = ft_parse_here_doc_base(info, s);
	if (text == NULL)
		return (NULL);
	merge = ft_lstjoin_here_doc(text);
	ft_txtclear(&text);
	if (merge == NULL)
		return (NULL);
	return (merge);
}

t_list	*ft_parse_here_doc_base(t_info *info, const char *s)
{
	t_list	*list;
	t_list	*node;
	int		i;

	list = ft_emptynew();
	if (list == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			node = ft_parse_env(info, s, &i);
		else if (s[i] == '\\')
			node = ft_parse_escape(s, &i, "$");
		else
			node = ft_parse_token(s, &i, "$");
		if (node == NULL)
		{
			ft_txtclear(&list);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
	}
	return (list);
}

char	*ft_lstjoin_here_doc(t_list *list)
{
	t_redi	*redi;
	char	*join;
	char	*temp;

	join = ft_strdup("");
	if (join == NULL)
		return (NULL);
	while (list)
	{
		redi = (t_redi *)(list->content);
		if (ft_txttypeis(list, "none"))
		{
			list = list->next;
			continue ;
		}
		temp = join;
		join = ft_strjoin(join, redi->path);
		free(temp);
		if (join == NULL)
			return (NULL);
		list = list->next;
	}
	return (join);
}
