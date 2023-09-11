/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:32 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/11 19:05:04 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*ft_merge_param(t_list **text);
t_list	*ft_merge_redi(t_list **text);
char	*ft_merge_text(t_list **text);

t_list	*ft_merge(t_list *text)
{
	t_list	*list;
	t_list	*node;

	list = NULL;
	while (text)
	{
		ft_skip_space(&text);
		if (text == NULL)
			break ;
		else if (ft_txttypeis(text, "text"))
			node = ft_merge_param(&text);
		else if (ft_txttypeis(text, "redi"))
			node = ft_merge_redi(&text);
		if (node == NULL)
		{
			ft_txtclear(&list);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
	}
	return (list);
}

t_list	*ft_merge_param(t_list **text)
{
	char	*path;
	t_list	*param;

	path = ft_merge_text(text);
	if (path == NULL)
		return (NULL);
	param = ft_txtnew("param", path);
	if (param == NULL)
	{
		free(path);
		return (NULL);
	}
	return (param);
}

t_list	*ft_merge_redi(t_list **text)
{
	t_list	*temp;
	char	*path;
	t_list	*redi;

	temp = *text;
	*text = (*text)->next;
	path = ft_merge_text(text);
	if (path == NULL)
		return (NULL);
	redi = NULL;
	if (ft_txttypeis(temp, ">"))
		redi = ft_txtnew(path, "outfile");
	else if (ft_txttypeis(temp, "<"))
		redi = ft_txtnew(path, "infile");
	else if (ft_txttypeis(temp, ">>"))
		redi = ft_txtnew(path, "append");
	else if (ft_txttypeis(temp, "<<"))
		redi = ft_txtnew(path, "here_doc");
	if (redi == NULL)
	{
		free(path);
		return (NULL);
	}
	return (redi);
}

char	*ft_merge_text(t_list **text)
{
	t_redi	*redi;
	char	*join;
	char	*temp;

	join = ft_strdup("");
	if (join == NULL)
		return (NULL);
	while (*text)
	{
		redi = (t_redi *)((*text)->content);
		if (ft_strcmp(redi->type, "space") == 0)
			break ;
		temp = join;
		join = ft_strjoin(join, redi->path);
		free(temp);
		if (join == NULL)
			return (NULL);
		*text = (*text)->next;
	}
	return (join);
}
