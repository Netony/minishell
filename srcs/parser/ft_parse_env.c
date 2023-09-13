/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:47:49 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/13 10:58:03 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishell.h"

int		env_getkey(char **key, const char *s, int *i);
t_list	*env_getval(t_info *info, char *key);
char	*env_getval_base(t_info *info, char *key);
char	*env_getfrominfo(t_info *info, char *key);
t_list	*ft_nonenew(void);

t_list	*ft_parse_env(t_info *info, const char *s, int *i)
{
	t_list	*val;
	char	*key;

	if (env_getkey(&key, s, i) < 0)
		return (NULL);
	val = env_getval(info, key);
	free(key);
	if (val == NULL)
		return (NULL);
	return (val);
}

char	*env_getfrominfo(t_info *info, char *key)
{
	t_env	*node;

	if (key == NULL)
		return (ft_strdup(""));
	else if (key[0] == '\0')
		return (ft_strdup(""));
	node = envsearch(info->envlst, key);
	if (node == NULL || node->value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(node->value));
}
