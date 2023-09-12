/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 21:17:25 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/12 21:17:39 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_skip_space(t_list **text)
{
	t_redi	*redi;

	while (*text)
	{
		redi = (t_redi *)((*text)->content);
		if (ft_strcmp(redi->type, "space") != 0)
			break ;
		(*text) = (*text)->next;
	}
	return (0);
}

int	ft_skip_text(t_list **text)
{
	t_redi	*redi;

	while (*text)
	{
		redi = (t_redi *)((*text)->content);
		if (ft_strcmp(redi->type, "space") == 0)
			break ;
		(*text) = (*text)->next;
	}
	return (0);
}

int	ft_txttypeis(t_list *text, char *a)
{
	t_redi	*redi;

	redi = (t_redi *)text->content;
	if (ft_strcmp(a, redi->type) == 0)
		return (1);
	return (0);
}

char	*ft_txtpath(t_list *text)
{
	t_redi	*redi;

	redi = (t_redi *)text->content;
	return (redi->path);
}

int	ft_txtpathis(t_list *text, char *a)
{
	t_redi	*redi;

	redi = (t_redi *)text->content;
	if (ft_strcmp(a, redi->path) == 0)
		return (1);
	return (0);
}
