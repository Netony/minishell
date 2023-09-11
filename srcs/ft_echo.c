/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:03:09 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/11 16:24:15 by seunghy2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **command)
{
	int	i;

	i = 1;
	if (!(ft_strcmp(command[i], "-n")))
		i++;
	while (command[i])
	{
		printf("%s", command[i]);
		i++;
		if (command[i])
			printf(" ");
	}
	if (!(command[1]) || ft_strcmp(command[1], "-n"))
		printf("\n");
	return (0);
}
