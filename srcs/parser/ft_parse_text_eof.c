#include "parser.h"

int		ft_parse_dquote_error(const char *s, int i);
t_list	*ft_dquote_eof_merge(t_list *list);
t_list	*ft_parse_dquote_eof_base(const char *s, int *i);
t_list	*ft_parse_node_eof(const char *s, int *i);

t_list	*ft_parse_text_eof(const char *s)
{
	t_list	*list;
	t_list	*node;
	char	*merge;

	*i += ft_duplen(s, *i, " ");
	list = NULL;
	while (1)
	{
		if (s[*i] == '\0' || ft_isin(s[*i], " <>|"))
			break ;
		node = ft_parse_node_eof(info, s, i);
		if (node == NULL)
		{
			ft_txtclear(&list);
			return (NULL);
		}
		if (ft_isnone(node) == 0)
			ft_lstadd_back(&list, node);
		else
			ft_txtclear(&node);
	}
	return (list);
}

t_list	*ft_parse_node_eof(const char *s, int *i)
{
	t_list	*node;

	else if (s[*i] == '\"')
		node = ft_parse_dquote_eof(s, i);
	else if (s[*i] == '\'')
		node = ft_parse_quote(s, i);
	else if (s[*i] == '\\')
		node = ft_parse_escape(s, i, NULL);
	else
		node = ft_parse_token(s, i, "\"\'\\ <|>");
	return (node);
}

t_list	*ft_parse_dquote_eof(const char *s, int *i)
{
	t_list	*text;
	t_list	*merge;

	*i += 1;
	text = ft_parse_dquote_eof_base(s, i);
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

t_list	*ft_parse_dquote_eof_base(const char *s, int *i)
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
}

t_list	*ft_dquote_eof_merge(t_list *list)
{
	char	*join;
	char	*temp;
	t_list	*node;

	join = ft_strdup("");
	if (join == NULL)
		return (NULL);
	while (list)
	{
		temp = join;
		join = ft_strjoin(join, redi->path);
		free(temp);
		if (join == NULL)
			return (NULL);
		list = list->next;
	}
	node = ft_txtnew("text",join);
	if (node == NULL)
	{
		free(join);
		return (NULL);
	}
	return (node);
}
