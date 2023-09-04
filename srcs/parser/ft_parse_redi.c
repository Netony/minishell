/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:48:23 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/04 18:52:20 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*ft_parse_type_set(const char *s, int *i);

t_list	*ft_parse_redi_list(t_info *info, const char *s, int *i)
{
	t_list	*list;
	t_list	*node;

	list = NULL;
	while (1)
	{
		*i += ft_duplen(s, *i, " ");
		if (s[*i] == '\0' || s[*i] == '|')
			break ;
		node = ft_parse_redi_node(info, s, i);
		if (node == NULL)
		{
			ft_lstclear(&list, ft_redidel);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
	}
	return (list);
}

t_list	*ft_parse_redi_node(t_info *info, const char *s, int *i)
{
	t_list	*node;
	t_redi	*redi;
	char	*type;
	char	*text;

	type = ft_parse_type(s, i);
	if (type == NULL)
		return (NULL);
	text = ft_parse_path(info, s, i);
	if (text == NULL)
	{
		free(type);
		return (NULL);
	}
	redi = ft_redinew(type, text);
	if (redi == NULL)
	{
		free(type);
		free(text);
		return (NULL);
	}
	node = ft_lstnew(redi);
	if (node == NULL)
		ft_redidel(redi);
	return (node);
}

char	*ft_parse_path(t_info *info, const char *s, int *i)
{
	char	*path;
	t_list	*text_list;

	text_list = ft_parse_text_list(info, s, i);
	if (text_list == NULL)
		return (NULL);
	path = ft_lstjoin(text_list);
	ft_lstclear(&text_list, free);
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*ft_parse_type(const char *s, int *i)
{
	char	*type;

	type = ft_parse_type_set(s, i);
	if (type == NULL)
		return (NULL);
	if (s[*i] == '\0' || ft_isin(s[*i], "<>|"))
	{
		ft_error("newline");
		free(type);
		return (NULL);
	}
	return (type);
}

static char	*ft_parse_type_set(const char *s, int *i)
{
	char	*type;

	if (ft_duplen(s, *i, "<") == 1)
	{
		*i += 1;
		type = ft_strdup("infile");
	}
	else if (ft_duplen(s, *i, ">") == 1)
	{
		*i += 1;
		type = ft_strdup("outfile");
	}
	else if (ft_duplen(s, *i, "<") > 1)
	{
		*i += 2;
		type = ft_strdup("here_doc");
	}
	else if (ft_duplen(s, *i, ">") > 1)
	{
		*i += 2;
		type = ft_strdup("append");
	}
	else
		type = ft_strdup("param");
	return (type);
}
