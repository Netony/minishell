/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:47:49 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/12 21:16:57 by dajeon           ###   ########.fr       */
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

int	env_getkey(char **key, const char *s, int *i)
{
	int		len;

	*i += 1;
	len = ft_toklen(s, *i, "\"\'\\ <|>?!$.");
	if (len == 0)
	{
		if (s[*i] == '\0' || ft_isin(s[*i], " <|>."))
		{
			*key = NULL;
			return (0);
		}
		else if (ft_isin(s[*i], "\"\'"))
			*key = ft_substr(s, *i, 0);
		else if (ft_isin(s[*i], "!?$"))
			*key = ft_substr(s, *i, 1);
		*i += 1;
	}
	else
	{
		*key = ft_substr(s, *i, len);
		*i += len;
	}
	if (*key == NULL)
		return (-1);
	return (0);
}

t_list	*env_getval(t_info *info, char *key)
{
	char	*val;
	t_list	*list;
	t_list	*node;
	int		i;

	i = 0;
	val = env_getval_base(info, key);
	if (val == NULL)
		return (NULL);
	list = NULL;
	while (val[i])
	{
		if (val[i] == ' ')
			node = ft_parse_space(val, &i);
		else
			node = ft_parse_token(val, &i, " ");
		if (node == NULL)
		{
			free(val);
			ft_txtclear(&list);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
	}
	if (val[0] == '\0')
		list = ft_nonenew();
	free(val);
	return (list);
}

char	*env_getval_base(t_info *info, char *key)
{
	if (key == NULL)
		return (ft_strdup("$"));
	else if (key[0] == '\0')
		return (ft_strdup(""));
	else if (ft_strcmp(key, "$") == 0)
		return (ft_strdup(""));
	else if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(ft_status(g_status)));
	else if (ft_strcmp(key, "!") == 0)
		return (ft_itoa(info->lastpid));
	else
		return (env_getfrominfo(info, key));
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
