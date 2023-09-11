/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 15:29:44 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/11 15:43:31 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_status(int status)
{
	unsigned char	exit;
	unsigned char	sig;

	exit = status >> 8;
	sig = status;
	if (sig > 0)
		return (128 + sig);
	return (exit);
}

int	ft_sigputend(int status)
{
	if (ft_status(status) == 130)
		ft_putendl_fd("", 1);
	if (ft_status(status) == 131)
		ft_putendl_fd("Quit: 3", 1);
	return (0);
}
