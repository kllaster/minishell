#include "minishell.h"

int	parse__operator(t_dlst **lexemes, int i, t_operator type)
{
	t_lexeme	*lexeme;

	lexeme = new_lexeme(type, NULL, NULL);
	dlst_add_front(lexemes, dlst_new(lexeme));
	return (i);
}

int	parse__spaces(t_dlst **lexemes, const char *line, int i)
{
	t_lexeme	*lexeme;

	lexeme = NULL;
	while (line[++i])
	{
		if (line[i] != SPACE && line[i] != TAB)
			break ;
	}
	if (*lexemes != NULL)
	{
		lexeme = new_lexeme(SPACE, ft_strdup(" "), NULL);
		dlst_add_front(lexemes, dlst_new(lexeme));
	}
	if (line[i])
		return (i - 1);
	return (i - 2);
}

int	parse__str(t_dlst **lexemes, const char *line, int i)
{
	int			start;
	char		*str;
	t_lexeme	*lexeme;

	start = i;
	while (line[++i])
	{
		if (line[i] == S_QUOTE || line[i] == D_QUOTE
			|| line[i] == SPACE || line[i] == ARG || line[i] == PIPE
			|| line[i] == L_REDIR || line[i] == R_REDIR)
			break ;
	}
	str = kl_strdup_len(&line[start], i - start);
	lexeme = new_lexeme(STR, str, valid__str);
	dlst_add_front(lexemes, dlst_new(lexeme));
	return (i - 1);
}

int	parse__quote(t_dlst **lexemes, const char *line, int i, t_operator type)
{
	int			start;
	t_lexeme	*lexeme;

	start = i + 1;
	while (line[++i])
	{
		if (line[i] == (int)type)
			break ;
	}
	if (line[i])
	{
		lexeme = new_lexeme(type, kl_strdup_len(&line[start], i - start), NULL);
		dlst_add_front(lexemes, dlst_new(lexeme));
		return (i);
	}
	return (i - 1);
}
