#include "minishell.h"

void	free_token(void *p)
{
	t_token	*token;

	token = p;
	if (token->str)
		free(token->str);
	free(token);
}

t_token	*new_token(t_operator type, char *str)
{
	t_token	*token;

	token = kl_malloc(sizeof(t_token));
	token->type = type;
	token->str = str;
	return (token);
}

static void	crossing_w_next_token(t_token *token, t_dlst *dlts_item)
{
	char		*join;
	t_token	*next;

	next = dlts_item->next->content;
	join = ft_strjoin(next->str, token->str);
	token->type = next->type;
	if (token->str)
		free(token->str);
	token->str = join;
	free_token(next);
	dlst_remove_node(dlts_item->next);
}

void	join_token_str(t_token *token, t_dlst *dlts_item)
{
	t_token	*next;

	if (dlts_item->next == NULL)
		return ;
	next = dlts_item->next->content;
	if (next->type == SET_VAR || next->type == S_QUOTE || next->type == STR)
		crossing_w_next_token(token, dlts_item);
	else if (next->type == SPACE && dlts_item->next->next)
	{
		next = dlts_item->next->next->content;
		if (next->type == S_QUOTE || next->type == STR
			|| next->type == SET_VAR)
		{
			free_token(dlts_item->next->content);
			dlst_remove_node(dlts_item->next);
		}
	}
}

t_dlst	*parse__var(t_token *token, t_dlst *dlts_item)
{
	t_dlst	*prev;
	char	**new_envp;

	prev = dlts_item->next;
	new_envp = create_envp(g_envp, token->str);
	kl_free_arr(g_envp);
	g_envp = new_envp;
	free_token(token);
	dlst_remove_node(dlts_item);
	return (prev);
}
