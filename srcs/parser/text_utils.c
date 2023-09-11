#include "parser.h"

int	ft_skip_space(t_list **text)
{
	t_redi	*redi;

	while (*text)
	{
		redi = (t_redi *)((*text)->content);
		if (ft_strcmp(redi->type, "text") == 0)
			break ;
		(*text) = (*text)->next;
	}
	return (0);
}

int	ft_skip_text(t_list **text)
{
	t_redi	*redi;

	while (*text)
	{
		redi = (t_redi *)((*text)->content);
		if (ft_strcmp(redi->type, "space") == 0)
			break ;
		(*text) = (*text)->next;
	}
	return (0);
}

int	ft_txttypeis(t_list *text, char *a)
{
	t_redi	*redi;

	redi = (t_redi *)text->content;
	if (ft_strcmp(a, redi->type) == 0)
		return (1);
	return (0);
}

char	*ft_txtpath(t_list *text)
{
	t_redi	*redi;
	
	redi = (t_redi *)text->content;
	return (redi->path);
}
