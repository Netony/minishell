/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exheredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:41:11 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/10 21:20:36 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_doc_acting(char *endline, int fd)
{
	char	*str;
	pid_t	pid;
	int		heredocg_status;

	signal(SIGINT, sigint_handler_here_doc);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			str = readline("> ");
			if (!str || ft_strcmp(endline, str) == 0)
			{
				if (str)
					free(str);
				exit(0);
			}
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
			free(str);
		}
	}
	waitpid(pid, &heredocg_status, 0);
	signal(SIGINT, main_sigint_handler);
	return (heredocg_status);
}
