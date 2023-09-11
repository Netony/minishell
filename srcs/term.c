/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:50:34 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/11 15:40:36 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_terminit(t_info *info, char **envp)
{
	info->envlst = envlist(envp);
	g_status = 0;
	return (0);
}

int	ft_termset(void)
{
	struct termios	term;

	signal(SIGINT, main_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}

int	ft_termunset(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (0);
}

int	ft_termexit(t_info *info)
{
	printf("\033[10C");
	printf("\033[1A");
	printf(" exit\n");
	envlstfree(info->envlst);
	return (0);
}
