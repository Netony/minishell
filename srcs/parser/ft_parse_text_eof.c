t_list	*ft_parse_text_eof(t_info *info, const char *s, int *i)
{
	t_list	*list;
	t_list	*node;

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
