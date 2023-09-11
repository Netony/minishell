/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exheredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:41:11 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/11 13:21:22 by seunghy2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tmpheredoc(char *endline, int fd)
{
	char	*str;
	pid_t	pid;
	int		heredoc_status;

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
			ft_putendl_fd(str, fd);
			free(str);
		}
	}
	waitpid(pid, &heredoc_status, 0);
	signal(SIGINT, main_sigint_handler);
	return (heredoc_status);
}
