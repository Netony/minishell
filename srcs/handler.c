/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:20:48 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/11 15:44:27 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_sigint_handler(int signum)
{
	(void)signum;
	ft_putendl_fd("", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sigint_handler_here_doc(int sigint)
{
	(void)sigint;
	g_status = 1 << 8;
	ft_putendl_fd("", 1);
}
