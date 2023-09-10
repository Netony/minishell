/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_param_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dajeon <dajeon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:09:13 by dajeon            #+#    #+#             */
/*   Updated: 2023/09/10 21:39:07 by dajeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*ft_merge_text(char *type, t_list *text);
int		ft_redi_check(t_list *redi, const char *s, int start, int end);

t_list	*ft_param_new(t_info *info, const char *s, int *i)
{
	t_list	*param;
	t_list	*text;

	text = ft_parse_text_list(info, s, i);
	if (text == NULL)
		return (NULL);
	param = ft_merge_text(NULL, text);
	ft_txtclear(&text);
	return (param);
}

t_list	*ft_redirect_new(char *type, t_info *info, const char *s, int *i)
{
	t_list	*text;
	t_list	*redi;
	int		temp;

	temp = *i;
	text = ft_parse_text_list(info, s, i);
	if (text == NULL)
		return (NULL);
	redi = ft_merge_text(type, text);
	if (ft_redi_check(redi, s, temp, *i) == 0)
	{
		ft_txtclear(&text);
		return (NULL);
	}
	ft_txtclear(&text);
	if (redi == NULL)
		return (NULL);
	return (redi);
}

int	ft_redi_check(t_list *redi, const char *s, int start, int end)
{
	int	size;

	size = 0;
	while (redi)
	{
		size++;
		redi = redi->next;
	}
	if (size > 1)
	{
		write(2, "bash ", 5);
		write(2, s + start, end - start);
		ft_putendl_fd(": ambiguous redirect", 2);
		return (0);
	}
	return (1);
}
