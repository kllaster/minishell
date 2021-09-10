#include "minishell.h"

void	free_lexeme(void *p)
{
	t_lexeme	*lexeme;

	lexeme = p;
	if (lexeme->str)
		free(lexeme->str);
	free(lexeme);
}

t_lexeme	*new_lexeme(t_operator type, char *str)
{
	t_lexeme	*lexeme;

	lexeme = kl_malloc(sizeof(t_lexeme));
	lexeme->type = type;
	lexeme->str = str;
	return (lexeme);
}

static void	crossing_w_next_lexeme(t_lexeme *lexeme, t_dlst *dlts_item)
{
	char		*join;
	t_lexeme	*next;

	next = dlts_item->next->content;
	join = ft_strjoin(next->str, lexeme->str);
	if (lexeme->str)
		free(lexeme->str);
	free_lexeme(next);
	lexeme->str = join;
	dlst_remove_node(dlts_item->next);
}

void	join_lexeme_str(t_lexeme *lexeme, t_dlst *dlts_item)
{
	t_lexeme	*next;

	if (dlts_item->next == NULL)
		return ;
	next = dlts_item->next->content;
	if (next->type == S_QUOTE || next->type == STR)
		crossing_w_next_lexeme(lexeme, dlts_item);
	else if (next->type == SPACE && dlts_item->next->next)
	{
		next = dlts_item->next->next->content;
		if (next->type == S_QUOTE || next->type == STR)
		{
			free_lexeme(dlts_item->next->content);
			dlst_remove_node(dlts_item->next);
		}
	}
}
