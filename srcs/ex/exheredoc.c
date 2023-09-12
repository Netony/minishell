/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exheredoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 20:41:11 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/11 18:30:20 by seunghy2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*nonexitpath(void)
{
	char	*result;
	char	*temp;
	int		i;

	result = ft_strdup("./A");
	i = 2;
	while (result && !access(result, F_OK))
	{
		result[i]++;
		if (result[i] == 'z')
		{
			while (result[i] == 'z')
				result[i++] = 'A';
			if (!result[i])
			{
				temp = result;
				result = ft_strjoin(temp, "A");
				free(temp);
			}
			else
				result[i]++;
			i = 2;
		}
	}
	return (result);
}

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

int	tmpfilefd(char *endline)
{
	int		fd;
	char	*filepath;

	filepath = nonexitpath();
	fd = open(filepath, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (tmpheredoc(endline, fd))
	{
		close(fd);
		unlink(filepath);
		free(filepath);
		return (-2);
	}
	close(fd);
	fd = open(filepath, O_RDONLY);
	unlink(filepath);
	free(filepath);
	return (fd);
}

int	heredocfd(t_cmd node)
{
	t_list	*redilst;
	t_redi	*content;
	int		result;

	redilst = node.redilst;
	result = 0;
	while (redilst && result != -2)
	{
		content = (t_redi *)(redilst->content);
		if (!(ft_strcmp(content->type, "here_doc")))
			result = tmpfilefd(content->path);
		redilst = redilst->next;
	}
	return (result);
}
