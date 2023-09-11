/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 19:53:49 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/11 16:00:46 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum);

void	tmpstdinout(t_exnode *onebuilt, t_cmd *cmd_array, t_info *info)
{
	int	tmp_std[2];

	if (pipe(tmp_std) == -1)
	{
		errormsg(MS_ERRNO, 0);
		free(onebuilt);
		return ;
	}
	dup2(0, tmp_std[0]);
	dup2(1, tmp_std[1]);
	if (exnodeset(onebuilt, *cmd_array, 0))
		g_status = 1;
	else
	{
		if (!(ft_strcmp((cmd_array->command)[0], "exit")))
			ft_exit(onebuilt, info->envlst, 1);
		g_status = exbuiltin(onebuilt, &(info->envlst), 0, 1);
	}
	dup2(tmp_std[0], 0);
	dup2(tmp_std[1], 1);
	exnodeclose(onebuilt);
	exlstfree(onebuilt, 1);
}

void	ms_excuter(t_cmd *cmd_array, int cmd_size, t_info *info)
{
	t_exnode	*onebuilt;

	if (cmd_size != 1 || \
			!(builtincheck((cmd_array->command)[0])))
		piping(cmd_array, cmd_size, info);
	else
	{
		onebuilt = (t_exnode *)malloc(sizeof(t_exnode));
		if (!onebuilt)
		{
			errormsg(MS_MALLOC, 0);
			return ;
		}
		tmpstdinout(onebuilt, cmd_array, info);
	}
}

int	ft_execute(t_info *info, char *buf)
{
	t_list	*cmd_list;
	t_cmd	*cmd_array;
	int		cmd_size;

	cmd_list = parser(info, buf);
	if (cmd_list == NULL)
		return (0);
	cmd_size = ft_cmdsize(cmd_list);
	cmd_array = ft_convert(cmd_list);
	ft_lstclear(&cmd_list, ft_cmddel);
	if (cmd_array == NULL)
		return (0);
	ms_excuter(cmd_array, cmd_size, info);
	ft_cmdsdel(cmd_array, cmd_size);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*buf;

	(void)argv;
	if (argc != 1)
		return (1);
	ft_terminit(&info, envp);
	ft_termset();
	while (1)
	{
		buf = readline("minishell$ ");
		if (buf)
		{
			ft_execute(&info, buf);
			if (ft_strcmp(buf, "") != 0)
				add_history(buf);
			free(buf);
		}
		else
			break ;
	}
	ft_termexit(&info);
	return (0);
}
