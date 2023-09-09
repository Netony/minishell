/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghy2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:08:09 by seunghy2          #+#    #+#             */
/*   Updated: 2023/09/09 21:13:46 by seunghy2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parser.h"
# include "execute_env.h"
# include "execute_ex.h"
# include "execute_util.h"
# include "error.h"
# include "../libft/incs/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>

int		status;

int		ft_terminit(t_info *info, char **envp);
int		ft_termexit(t_info *info);

int		ft_termset(void);
int		ft_termunset(void);

int		ft_infoinit(t_info *info, char **envp);

void	main_sigint_handler(int signum);
void	sigquit_handler(int sigquit);
void	sigint_handler(int sigint);
void	sigint_handler_here_doc(int sigint);

#endif
