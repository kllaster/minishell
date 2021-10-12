#include "minishell.h"

int	parse_lexem_other(t_dlst **lexemes, const char *line, int i)
{
	if (line[i] == R_REDIR)
	{
		if (line[i + 1] && line[i + 1] == R_REDIR)
			i = parse__operator(lexemes, i + 1, DR_REDIR);
		else
			i = parse__operator(lexemes, i, R_REDIR);
	}
	else if (line[i] == L_REDIR)
	{
		if (line[i + 1] && line[i + 1] == L_REDIR)
			i = parse__operator(lexemes, i + 1, DL_REDIR);
		else
			i = parse__operator(lexemes, i, L_REDIR);
	}
	else
		i = parse__str(lexemes, line, i);
	return (i);
}

t_dlst	*parse_lexeme(char *line)
{
	int		i;
	t_dlst	**lexemes;
	t_dlst	*lexemes_res;

	i = -1;
	lexemes = kl_malloc(sizeof(t_dlst **));
	*lexemes = NULL;
	while (line[++i])
	{
		if (line[i] == SPACE)
			i = parse__spaces(lexemes, line, i);
		else if (line[i] == S_QUOTE)
			i = parse__quote(lexemes, line, i, S_QUOTE);
		else if (line[i] == D_QUOTE)
			i = parse__quote(lexemes, line, i, D_QUOTE);
		else if (line[i] == PIPE)
			i = parse__operator(lexemes, i, PIPE);
		else
			i = parse_lexem_other(lexemes, line, i);
	}
	lexemes_res = dlst_last_node(*lexemes);
	free(lexemes);
	return (lexemes_res);
}
