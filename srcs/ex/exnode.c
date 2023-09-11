/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exnode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:04:58 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/11 13:17:35 by seunghy2         ###   ########.fr       */
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

void	openclose(t_exnode *result, t_redi *content)
{
	int	fd;
	int	flag;

	flag = 0;
	if (++flag && !(ft_strcmp(content->type, "infile")))
		fd = open(content->path, O_RDONLY);
	else if (++flag && !(ft_strcmp(content->type, "here_doc")))
		fd = tmpfilefd(content->path);
	else if (++flag && !(ft_strcmp(content->type, "outfile")))
		fd = open(content->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (++flag && !(ft_strcmp(content->type, "append")))
		fd = open(content->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (flag == 1 || flag == 2)
	{
		if (result->read != 0)
			close(result->read);
		result->read = fd;
	}
	else if (flag == 3 || flag == 4)
	{
		if (result->write != 1)
			close(result->write);
		result->write = fd;
	}
}

int	exnodeset(t_exnode *arg, t_cmd node, int inpipe)
{
	t_list		*temp;

	arg->read = inpipe;
	arg->write = 1;
	temp = node.redilst;
	arg->command = node.command;
	while (temp)
	{
		openclose(arg, (t_redi *)(temp->content));
		if (arg->read == -2)
			return (9999);
		if (arg->read == -1 || arg->write == -1)
		{
			errormsg(MS_ERRNO, ((t_redi *)(temp->content))->path);
			return (MS_ERRNO);
		}
		temp = temp->next;
	}
	return (MS_SUCCESS);
}
