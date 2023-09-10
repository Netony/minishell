/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:32:20 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/10 21:43:40 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*ft_merge_text_base(char *type, t_list **text);
int		ft_skip_space(t_list **text);
char	*ft_merge_lstjoin(t_list **text);

t_list	*ft_merge_text(char *type, t_list *text)
{
	t_list	*list;
	t_list	*node;

	list = NULL;
	while (text)
	{
		ft_skip_space(&text);
		if (text == NULL)
			break ;
		node = ft_merge_text_base(type, &text);
		if (node == NULL)
		{
			ft_txtclear(&list);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
	}
	return (list);
}

t_list	*ft_merge_text_base(char *type, t_list **text)
{
	t_list	*param;
	char	*join;

	join = ft_merge_lstjoin(text);
	if (type == NULL)
		param = ft_txtnew("param", join);
	else
		param = ft_redi_node(type, join);
	if (param == NULL)
		free(join);
	return (param);
}

char	*ft_merge_lstjoin(t_list **text)
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

int	ft_skip_space(t_list **text)
{
	t_redi	*redi;

	while (*text)
	{
		redi = (t_redi *)((*text)->content);
		if (ft_strcmp(redi->type, "text") == 0)
			break ;
		(*text) = (*text)->next;
	}
	return (0);
}
