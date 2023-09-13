/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:48:27 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/13 12:22:14 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		ft_isnone(t_list *node);
t_list	*ft_parse_node(t_info *info, const char *s, int *i);
t_list	*ft_parse_text(t_info *info, const char *s, int *i);
t_list	*ft_nonenew(void);

t_list	*ft_parse_cmd(t_info *info, const char *s, int *i)
{
	t_list	*text;
	t_list	*cmd;

	text = ft_parse_text(info, s, i);
	if (text == NULL)
		return (NULL);
	cmd = ft_merge(text);
	ft_txtclear(&text);
	return (cmd);
}

t_list	*ft_parse_text(t_info *info, const char *s, int *i)
{
	t_list	*list;
	t_list	*node;

	*i += ft_duplen(s, *i, " ");
	list = NULL;
	while (1)
	{
		if (s[*i] == '\0' || s[*i] == '|')
			break ;
		node = ft_parse_node(info, s, i);
		if (node == NULL)
		{
			ft_txtclear(&list);
			return (NULL);
		}
		if (ft_isnone(node) == 0)
			ft_lstadd_back(&list, node);
		else
			ft_txtclear(&node);
	}
	return (list);
}

t_list	*ft_parse_node(t_info *info, const char *s, int *i)
{
	t_list	*node;

	if (s[*i] == ' ')
		node = ft_parse_space(s, i);
	else if (ft_isin(s[*i], "<>"))
		node = ft_parse_redi(info, s, i);
	else if (s[*i] == '$')
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

int	ft_isnone(t_list *node)
{
	t_redi	*redi;

	redi = (t_redi *)node->content;
	if (ft_strcmp(redi->type, "none") == 0)
		return (1);
	return (0);
}

t_list	*ft_parse_text_redi(t_info *info, const char *s, int *i)
{
	t_list	*list;
	t_list	*node;

	*i += ft_duplen(s, *i, " ");
	list = NULL;
	while (1)
	{
		if (s[*i] == '\0' || ft_isin(s[*i], " <>|"))
			break ;
		node = ft_parse_node(info, s, i);
		if (node == NULL)
		{
			ft_txtclear(&list);
			return (NULL);
		}
		if (ft_isnone(node) == 0)
			ft_lstadd_back(&list, node);
		else
			ft_txtclear(&node);
	}
	if (list == NULL)
		list = ft_nonenew();
	return (list);
}
