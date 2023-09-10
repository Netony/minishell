/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:49:45 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/10 21:20:42 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_varsdel(char **vars, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(vars[i++]);
	free(vars);
	return (0);
}

int	ft_varsclear(char **vars)
{
	int	i;

	i = 0;
	while (vars[i])
		free(vars[i++]);
	free(vars);
	return (0);
}

int	ft_varslen(t_list *redi_list)
{
	t_redi	*redi;
	int		size;

	size = 0;
	while (redi_list)
	{
		redi = (t_redi *)(redi_list->content);
		if (ft_strcmp(redi->type, "param") == 0)
			size++;
		redi_list = redi_list->next;
	}
	return (size);
}
