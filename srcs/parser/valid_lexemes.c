#include "minishell.h"

void	crossing_w_next_lexeme(t_lexeme *lexeme, t_dlst *dlts_item)
{
	char		*join;
	t_lexeme	*next;

	next = dlts_item->prev->content;
	join = ft_strjoin(lexeme->str, next->str);
	free(lexeme->str);
	free(next->str);
	free(next);
	lexeme->str = join;
	dlst_remove_node(dlts_item->prev);
}

void	valid__str(t_lexeme *lexeme, t_dlst *dlts_item)
{
	t_lexeme	*next;

	if (dlts_item->prev == NULL)
		return ;
	next = dlts_item->prev->content;
	if (next->type == S_QUOTE)
		crossing_w_next_lexeme(lexeme, dlts_item);
}

t_dlst	*validation_lexemes(t_dlst *dlst_lexemes)
{
	t_dlst		*item;
	t_dlst		*node;

	item = dlst_lexemes;
	while (item)
	{
		if (((t_lexeme *)item->content)->validate)
			((t_lexeme *)item->content)->validate(item->content, item);
		node = item;
		item = item->prev;
	}
	node = dlst_last_node(node);
	return (node);
}
