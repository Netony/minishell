/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:20:48 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/09 21:13:21 by seunghy2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_sigint_handler(int signum)
{
	(void)signum;
	ft_putendl_fd("minishell$ ", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sigquit_handler(int sigquit)
{
	(void)sigquit;
	ft_putendl_fd("Quit: 3", 1);
	status = 131 << 8;
}

void	sigint_handler(int sigint)
{
	(void)sigint;
	ft_putendl_fd("", 1);
	status = 130 << 8;
}

void	sigint_handler_here_doc(int sigint)
{
	(void)sigint;
	ft_putendl_fd("", 1);
}
