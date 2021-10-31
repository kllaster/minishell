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
	lexeme->type = next->type;
	if (lexeme->str)
		free(lexeme->str);
	lexeme->str = join;
	free_lexeme(next);
	dlst_remove_node(dlts_item->next);
}

void	join_lexeme_str(t_lexeme *lexeme, t_dlst *dlts_item)
{
	t_lexeme	*next;

	if (dlts_item->next == NULL)
		return ;
	next = dlts_item->next->content;
	if (next->type == SET_VAR || next->type == S_QUOTE || next->type == STR)
		crossing_w_next_lexeme(lexeme, dlts_item);
	else if (next->type == SPACE && dlts_item->next->next)
	{
		next = dlts_item->next->next->content;
		if (next->type == S_QUOTE || next->type == STR
			|| next->type == SET_VAR)
		{
			free_lexeme(dlts_item->next->content);
			dlst_remove_node(dlts_item->next);
		}
	}
}

t_dlst	*parse__var(t_lexeme *lexeme, t_dlst *dlts_item)
{
	t_dlst	*prev;

	prev = dlts_item->next;
	g_envp = create_envp(g_envp, lexeme->str);
	free_lexeme(lexeme);
	dlst_remove_node(dlts_item);
	return (prev);
}
