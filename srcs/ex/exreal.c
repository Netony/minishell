/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exreal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:05:17 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/13 12:55:23 by seunghy2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

void	exerror(char *cmdpath, char **cmd, char **envp)
{
	DIR	*temp;

	if (!(ft_strchr(cmdpath, '/')))
	{
		errormsg(MS_MANUAL, "minishell: ");
		errormsg(MS_MANUAL, cmdpath);
		errorend(MS_MANUAL, ": command not found\n", 127);
	}
	if (access(cmdpath, F_OK) == -1)
		errorend(MS_ERRNO, cmdpath, 127);
	temp = opendir(cmdpath);
	if (!temp)
	{
		execve(cmdpath, cmd, envp);
		errorend(MS_ERRNO, cmdpath, 126);
	}
	closedir(temp);
	errormsg(MS_MANUAL, "minishell: ");
	errormsg(MS_MANUAL, cmdpath);
	errorend(MS_MANUAL, ": is a directory\n", 126);
}

char	**pathsplit(t_env *envlst)
{
	t_env	*pathnode;
	char	**result;

	pathnode = envsearch(envlst, "PATH");
	if (!pathnode)
	{
		result = (char **)malloc(sizeof(char *));
		*result = NULL;
	}
	else
		result = ft_split(pathnode->value, ':');
	return (result);
}

char	**pathset(t_env *envlst)
{
	char	**result;
	char	*temp;
	int		i;

	result = pathsplit(envlst);
	if (!result)
		return (0);
	i = -1;
	while (result[++i])
	{
		temp = result[i];
		result[i] = ft_strjoin(temp, "/");
		if (!result[i])
		{
			result[i] = temp;
			twodfree(result);
			return (0);
		}
		free(temp);
	}
	return (result);
}

char	*pathmkr(char *origin, t_env *envlst)
{
	char	**path;
	char	*result;
	int		i;

	path = pathset(envlst);
	if (!path)
		return (0);
	result = ft_strdup(origin);
	if (!result)
		return (0);
	if (!(ft_strlen(result)) || ft_strchr(result, '/'))
		return (result);
	i = -1;
	while (path[++i] && access(result, F_OK))
	{
		free(result);
		result = ft_strjoin(path[i], origin);
		if (!result)
			return (0);
	}
	twodfree(path);
	if (!(access(result, F_OK)))
		return (result);
	free(result);
	return (ft_strdup(origin));
}

void	exreal(t_exnode *arg, t_env **envlst, int noend, int outpipe)
{
	int		well;
	char	*cmdpath;
	char	**envp;

	if (arg->read == -1 || arg->write == -1)
		exit (1);
	if (builtincheck((arg->command)[0]))
		exit(exbuiltin(arg, envlst, noend, outpipe));
	cmdpath = pathmkr((arg->command)[0], *envlst);
	if (!cmdpath)
		errorend(MS_MALLOC, 0, 1);
	dup2(arg->read, 0);
	if (arg->write != 1)
		dup2(arg->write, 1);
	else if (noend)
		dup2(outpipe, 1);
	envp = envpmkr(*envlst);
	if (!envp)
		errorend(MS_MALLOC, 0, 1);
	well = execve(cmdpath, arg->command, envp);
	if (well == -1)
		exerror(cmdpath, arg->command, envp);
}
