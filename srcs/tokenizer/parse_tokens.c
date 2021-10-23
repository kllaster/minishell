#include "minishell.h"

int	parse__operator(t_dlst **tokens, int i, t_operator type)
{
	t_dlst	*temp;
	t_token	*token;

	if (*tokens && ((t_token *)(*tokens)->content)->type == SPACE)
	{
		temp = (*tokens)->next;
		free_token((*tokens)->content);
		dlst_remove_node(*tokens);
		*tokens = temp;
	}
	token = new_token(type, NULL);
	dlst_add_front(tokens, dlst_new(token));
	return (i);
}

int	parse__spaces(t_dlst **tokens, const char *line, int i)
{
	t_token		*token;
	t_operator	type;

	type = 0;
	token = NULL;
	while (line[++i])
	{
		if (line[i] != SPACE)
			break ;
	}
	if (*tokens != NULL)
		type = ((t_token *)(*tokens)->content)->type;
	if (line[i] && type != 0 && type != PIPE
		&& type != R_REDIR && type != R_HEREDOC
		&& type != L_REDIR && type != L_HEREDOC)
	{
		token = new_token(SPACE, NULL);
		dlst_add_front(tokens, dlst_new(token));
	}
	return (i - 1);
}

int	parse__str(t_dlst **tokens, const char *line, int i)
{
	int		start;
	char	*str;
	t_token	*token;

	start = i;
	while (line[++i])
	{
		if (line[i] == S_QUOTE || line[i] == D_QUOTE
			|| line[i] == SPACE || line[i] == PIPE
			|| line[i] == L_REDIR || line[i] == R_REDIR)
			break ;
	}
	str = kl_strdup_len(&line[start], (i - start));
	start = ft_strichr(str, VAR);
	if (ft_strchr(str, SET_VAR))
		token = new_token(SET_VAR, str);
	else if (start != -1)
		token = join_var(str, start);
	else
		token = new_token(STR, str);
	dlst_add_front(tokens, dlst_new(token));
	join_token_str((*tokens)->content, *tokens);
	return (i - 1);
}

void	parse__dquote(t_dlst **tokens, const char *line, int start, int end)
{
	int		start_var;
	t_token	*token;

	start_var = ft_strichr((char *)line + start, VAR);
	if (start_var != -1 && start_var < end)
		token = join_var(kl_strdup_len(&line[start], end - start), start_var);
	else
		token = new_token(STR,
				kl_strdup_len(&line[start], end - start));
	dlst_add_front(tokens, dlst_new(token));
}

int	parse__quote(t_dlst **tokens, const char *line, int i, t_operator type)
{
	int		start;
	t_token	*token;

	start = i + 1;
	while (line[++i])
	{
		if (line[i] == (int)type)
			break ;
	}
	if (line[i])
	{
		if (type == S_QUOTE)
		{
			token = new_token(STR, kl_strdup_len(&line[start], i - start));
			dlst_add_front(tokens, dlst_new(token));
		}
		else
			parse__dquote(tokens, line, start, i);
		join_token_str((*tokens)->content, *tokens);
		return (i);
	}
	return (i - 1);
}
