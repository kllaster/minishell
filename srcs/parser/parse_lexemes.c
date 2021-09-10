#include "minishell.h"

int	parse__operator(t_dlst **lexemes, int i, t_operator type)
{
	t_dlst		*temp;
	t_lexeme	*lexeme;

	if (((t_lexeme *)(*lexemes)->content)->type == SPACE)
	{
		temp = (*lexemes)->next;
		free_lexeme((*lexemes)->content);
		dlst_remove_node(*lexemes);
		*lexemes = temp;
	}
	lexeme = new_lexeme(type, NULL);
	dlst_add_front(lexemes, dlst_new(lexeme));
	return (i);
}

int	parse__spaces(t_dlst **lexemes, const char *line, int i)
{
	t_lexeme	*lexeme;
	t_operator	type;

	type = 0;
	lexeme = NULL;
	while (line[++i])
	{
		if (line[i] != SPACE && line[i] != TAB)
			break ;
	}
	if (*lexemes != NULL)
		type = ((t_lexeme *)(*lexemes)->content)->type;
	if (line[i] && type != 0 && type != PIPE
		&& type != R_REDIR && type != DR_REDIR
		&& type != L_REDIR && type != DL_REDIR)
	{
		lexeme = new_lexeme(SPACE, NULL);
		dlst_add_front(lexemes, dlst_new(lexeme));
	}
	return (i - 1);
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
	str = kl_strdup_len(&line[start], (i - start));
	lexeme = new_lexeme(STR, str);
	dlst_add_front(lexemes, dlst_new(lexeme));
	join_lexeme_str((*lexemes)->content, *lexemes);
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
		lexeme = new_lexeme(type, kl_strdup_len(&line[start], i - start));
		dlst_add_front(lexemes, dlst_new(lexeme));
		if (type == S_QUOTE)
			join_lexeme_str((*lexemes)->content, *lexemes);
		return (i);
	}
	return (i - 1);
}
