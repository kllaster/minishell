#include "minishell.h"

int	parse_token_other(t_dlst **tokens, const char *line, int i)
{
	if (line[i] == R_REDIR)
	{
		if (line[i + 1] && line[i + 1] == R_REDIR)
			i = parse__operator(tokens, i + 1, DR_REDIR);
		else
			i = parse__operator(tokens, i, R_REDIR);
	}
	else if (line[i] == L_REDIR)
	{
		if (line[i + 1] && line[i + 1] == L_REDIR)
			i = parse__operator(tokens, i + 1, DL_REDIR);
		else
			i = parse__operator(tokens, i, L_REDIR);
	}
	else
		i = parse__str(tokens, line, i);
	return (i);
}

t_dlst	*parse_tokens(char *line)
{
	int		i;
	t_dlst	**tokens;
	t_dlst	*tokens_res;

	i = -1;
	tokens = kl_malloc(sizeof(t_dlst **));
	*tokens = NULL;
	while (line[++i])
	{
		if (line[i] == SPACE)
			i = parse__spaces(tokens, line, i);
		else if (line[i] == S_QUOTE)
			i = parse__quote(tokens, line, i, S_QUOTE);
		else if (line[i] == D_QUOTE)
			i = parse__quote(tokens, line, i, D_QUOTE);
		else if (line[i] == PIPE)
			i = parse__operator(tokens, i, PIPE);
		else
			i = parse_token_other(tokens, line, i);
	}
	tokens_res = dlst_last_node(*tokens);
	free(tokens);
	return (tokens_res);
}
