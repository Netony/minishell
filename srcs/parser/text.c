/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:18:13 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/11 16:50:41 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "redi.h"

t_redi	*ft_txtbase(char *type, char *path);

void	ft_txtclear(t_list **text)
{
	ft_lstclear(text, ft_txtdel);
}

t_list	*ft_txtnew(char *type, char *path)
{
	t_redi	*redi;
	t_list	*node;

	redi = ft_txtbase(type, path);
	if (redi == NULL)
		return (NULL);
	node = ft_lstnew(redi);
	if (node == NULL)
	{
		ft_txtdel(redi);
		return (NULL);
	}
	return (node);
}

t_redi	*ft_txtbase(char *type, char *path)
{
	t_redi	*text;

	text = (t_redi *)malloc(sizeof(t_redi));
	if (text == NULL)
		return (NULL);
	text->type = ft_strdup(type);
	text->path = path;
	if (text->type == NULL)
	{
		ft_txtdel(text);
		return (NULL);
	}
	text->path = path;
	return (text);
}

void	ft_txtdel(void *param)
{
	t_redi	*redi;

	redi = (t_redi *)param;
	free(redi->type);
	free(redi->path);
	free(redi);
}
