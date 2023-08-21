/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:42:16 by seunghy2          #+#    #+#             */
/*   Updated: 2023/08/21 15:01:24 by seunghy2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	ft_unset(char **command, t_env **envlst)
{
	int	i;

	i = 1;
	while (command[i])
	{
		envdelete(envlst, command[i]);
		i++;
	}
	return (0);
}
