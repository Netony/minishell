/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exfree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:52:43 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/09 21:11:57 by seunghy2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exnodeclose(t_exnode *arg)
{
	if (arg->read > 2)
		close(arg->read);
	if (arg->write > 2)
		close(arg->write);
}

void	exlstfree(t_exnode *exlst, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		twodfree((exlst[i]).command);
		i++;
	}
	free(exlst);
}
