/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ex.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:19:57 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/11 13:17:52 by seunghy2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_EX_H
# define EXECUTE_EX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_exnode
{
	int		read;
	int		write;
	char	**command;
}	t_exnode;

void		piping(t_cmd *lst, int size, t_info *info);
int			exnodeset(t_exnode *arg, t_cmd node, int inpipe);
void		exreal(t_exnode *arg, t_env **envlst, int noend, int outpipe);
int			exbuiltin(t_exnode *arg, t_env **envlst, int noend, int outpipe);
int			builtincheck(char *command);
void		exnodeclose(t_exnode *arg);
void		exlstfree(t_exnode *exlst, int size);
int			tmpheredoc(char *endline, int fd);

int			ft_cd(char **command, t_env **envlst);
int			ft_echo(char **command);
int			ft_pwd(void);
int			ft_exit(t_exnode *arg, t_env *envlst, int free);

char		*get_next_line(int fd);

#endif
