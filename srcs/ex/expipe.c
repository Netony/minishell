/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:05:07 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/11 18:46:36 by seunghy2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argfree(t_exnode *arg)
{
	if (arg->read != 0)
		close(arg->read);
	if (arg->write != 1)
		close(arg->write);
	free(arg);
}

void	pidsig(pid_t pid)
{
	if (pid == 0)
	{
		ft_termunset();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

pid_t	nodepipefork(t_cmd origin, int fd[2], t_exnode *arg, pid_t *pid)
{
	pid_t	past;

	past = *pid;
	exnodeset(arg, origin, fd[0]);
	if (pipe(fd) == -1)
	{
		exnodeclose(arg);
		errormsg(MS_ERRNO, 0);
		return (past);
	}
	*pid = fork();
	if (*pid == -1)
	{
		exnodeclose(arg);
		close(fd[0]);
		close(fd[1]);
		errormsg(MS_ERRNO, 0);
		return (past);
	}
	pidsig(*pid);
	return (0);
}

pid_t	expipe(t_exnode *arg, t_cmd *lst, int size, t_env **envlst)
{
	int			fd[2];
	pid_t		pid;
	int			i;
	pid_t		expid;

	i = 0;
	fd[0] = 0;
	pid = -1;
	expid = nodepipefork(lst[i], fd, &(arg[i]), &pid);
	if (expid)
		return (expid);
	while (pid && i < size - 1)
	{
		close(fd[1]);
		exnodeclose(&(arg[i]));
		i++;
		expid = nodepipefork(lst[i], fd, &(arg[i]), &pid);
		if (expid)
			return (expid);
	}
	close(fd[0]);
	if (!pid)
		exreal(&(arg[i]), envlst, size - i - 1, fd[1]);
	exnodeclose(&(arg[i]));
	return (pid);
}

void	piping(t_cmd *lst, int size, t_info *info)
{
	t_exnode	*exlst;
	pid_t		pid;
	int			i;

	info->lastpid = -1;
	exlst = (t_exnode *)malloc(sizeof(t_exnode) * size);
	if (!exlst)
		errormsg(MS_MALLOC, 0);
	i = 0;
	while (i < size && (exlst[i - 1]).here_doc != -2)
	{
		(exlst[i]).here_doc = heredocfd(lst[i]);
		(exlst[i]).command = (lst[i]).command;
		i++;
	}
	if (i == size && (exlst[i - 1]).here_doc != -2)
		info->lastpid = expipe(exlst, lst, size, &(info->envlst));
	exlstfree(exlst, i);
	if (info->lastpid > 0)
		waitpid(info->lastpid, &g_status, 0);
	ft_sigputend(g_status);
	pid = 1;
	while (pid != -1)
		pid = waitpid(0, 0, WNOHANG);
	ft_termset();
}
