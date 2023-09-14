/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_redi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:48:23 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/13 11:20:24 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*ft_parse_redi_type(const char *s, int *i);
t_list	*ft_parse_redi_path(t_info *info, const char *s, int *i);
int		ft_path_size(t_list *node);
int		ft_check_redi(const char *s, int *i);
t_list	*ft_parse_text_redi(t_info *info, const char *s, int *i);

t_list	*ft_parse_redi(t_info *info, const char *s, int *i)
{
	t_list	*list;
	t_list	*node;

	list = ft_parse_redi_type(s, i);
	if (list == NULL)
		return (NULL);
	node = ft_parse_redi_path(info, s, i);
	if (node == NULL)
	{
		ft_txtclear(&list);
		return (NULL);
	}
	ft_lstadd_back(&list, node);
	return (list);
}

t_list	*ft_parse_redi_type(const char *s, int *i)
{
	t_list	*text;

	if (ft_duplen(s, *i, "<") == 1)
		text = ft_parse_size(s, i, 1);
	else if (ft_duplen(s, *i, ">") == 1)
		text = ft_parse_size(s, i, 1);
	else if (ft_duplen(s, *i, "<") > 1)
		text = ft_parse_size(s, i, 2);
	else if (ft_duplen(s, *i, ">") > 1)
		text = ft_parse_size(s, i, 2);
	else
		text = NULL;
	return (text);
}

t_list	*ft_parse_redi_path(char *type, t_info *info, const char *s, int *i)
{
	t_list	*node;
	int		temp;

	node = NULL;
	*i += ft_duplen(s, *i, " ");
	temp = *i;
	if (ft_check_redi(s, i) == 0)
		return (NULL);
	if (ft_strcmp(type, ">>") == 0)
		node = ft_parse_token(s, i, " ");
	else
		node = ft_parse_text_redi(info, s, i);
	if (node == NULL)
		return (NULL);
	if (ft_path_size(node) != 1)
	{
		ft_putstr_fd("minishell: ", 2);
		write(2, s + temp, *i - temp);
		ft_putendl_fd(": ambiguous redirect", 2);
		ft_txtclear(&node);
		return (NULL);
	}
	return (node);
}

int	ft_check_redi(const char *s, int *i)
{
	int	ret;

	ret = 0;
	if (s[*i] == '\0')
		ft_error("newline");
	else if (s[*i] == '|')
		ft_error("|");
	else if (s[*i] == '>')
		ft_error(">");
	else if (s[*i] == '<')
		ft_error("<");
	else
		ret = 1;
	return (ret);
}

int	ft_path_size(t_list *node)
{
	int		size;

	size = 0;
	if (ft_txttypeis(node, "none"))
		return (0);
	while (node)
	{
		ft_skip_space(&node);
		if (node == NULL)
			break ;
		size++;
		ft_skip_text(&node);
	}
	return (size);
}
