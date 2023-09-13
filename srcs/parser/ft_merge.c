/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:37:32 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/13 11:22:37 by dajeon           ###   ########.fr       */
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
	if (ft_txtpathis(temp, ">"))
		redi = ft_txtnew("outfile", path);
	else if (ft_txtpathis(temp, "<"))
		redi = ft_txtnew("infile", path);
	else if (ft_txtpathis(temp, ">>"))
		redi = ft_txtnew("append", path);
	else if (ft_txtpathis(temp, "<<"))
		redi = ft_txtnew("here_doc", path);
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
	ft_skip_space(text);
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
