#include "minishell.h"

int	parse__operator(t_dlst **lexemes, int i, t_operator type)
{
	t_dlst		*temp;
	t_lexeme	*lexeme;

	if (*lexemes && ((t_lexeme *)(*lexemes)->content)->type == SPACE)
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
		if (line[i] != SPACE)
			break ;
	}
	if (*lexemes != NULL)
		type = ((t_lexeme *)(*lexemes)->content)->type;
	if (line[i] && type != 0 && type != PIPE
		&& type != R_REDIR && type != DR_REDIR
		&& type != L_REDIR && type != DL_REDIR
		&& type != SEMICOLON)
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
			|| line[i] == SPACE || line[i] == PIPE
			|| line[i] == L_REDIR || line[i] == R_REDIR
			|| line[i] == SEMICOLON)
			break ;
	}
	str = kl_strdup_len(&line[start], (i - start));
	start = ft_strichr(str, VAR);
	if (ft_strchr(str, SET_VAR))
		lexeme = new_lexeme(SET_VAR, str);
	else if (start != -1)
		lexeme = join_var(str, start);
	else
		lexeme = new_lexeme(STR, str);
	dlst_add_front(lexemes, dlst_new(lexeme));
	join_lexeme_str((*lexemes)->content, *lexemes);
	return (i - 1);
}

void	parse__dquote(t_dlst **lexemes, const char *line, int start, int end)
{
	int			start_var;
	t_lexeme	*lexeme;

	start_var = ft_strichr((char *)line + start, VAR);
	if (start_var != -1 && start_var < end)
		lexeme = join_var(kl_strdup_len(&line[start], end - start), start_var);
	else
		lexeme = new_lexeme(STR, kl_strdup_len(&line[start], end - start));
	dlst_add_front(lexemes, dlst_new(lexeme));
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
		if (type == S_QUOTE)
		{
			lexeme = new_lexeme(STR, kl_strdup_len(&line[start], i - start));
			dlst_add_front(lexemes, dlst_new(lexeme));
		}
		else
			parse__dquote(lexemes, line, start, i);
		join_lexeme_str((*lexemes)->content, *lexemes);
		return (i);
	}
	return (i - 1);
}
