#include "parser.h"

int		ft_parse_dquote_error(const char *s, int i);
char	*ft_dquote_lstjoin(t_list *list);
t_list	*ft_dquote_merge(t_list *list);
t_list	*ft_parse_base_eof(t_info *info, const char *s, int *i);

t_list	*ft_parse_eof(const char *s, int *i)
{
	t_list	*text;
	t_list	*merge;

	*i += 1;
	text = ft_parse_dquote_base(s, i);
	if (text == NULL)
		return (NULL);
	if (ft_parse_dquote_error(s, *i) < 0)
	{
		ft_txtclear(&text);
		return (NULL);
	}
	*i += 1;
	merge = ft_dquote_merge(text);
	ft_txtclear(&text);
	if (merge == NULL)
		return (NULL);
	return (merge);
}

t_list	*ft_parse_base_eof(const char *s, int *i)
{
	t_list	*list;
	t_list	*node;

	list = ft_emptynew();
	if (list == NULL)
		return (NULL);
	while (s[*i])
	{
		if (s[*i] == '\"')
			break ;
		else if (s[*i] == '\\')
			node = ft_parse_escape(s, i, "\"\\");
		else
			node = ft_parse_token(s, i, "\"\\");
		if (node == NULL)
		{
			ft_txtclear(&list);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
	}
	return (list);
