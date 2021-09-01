#include "minishell.h"

int	parse__spaces(t_dlst **s_lexems, char *line, int i)
{
	while (line[++i])
	{
		if (line[i] != SPACE)
			break ;
	}
	if (*s_lexems != NULL)
		dlst_add_front(s_lexems, dlst_new(ft_strdup(" ")));
	if (line[i])
		return (i - 1);
	return (i - 2);
}

int	parse__str(t_dlst **s_lexems, char *line, int i)
{
	int		start;
	char	*str;

	start = i;
	while (line[++i])
	{
		if (line[i] == S_QUOTE || line[i] == D_QUOTE
			|| line[i] == SPACE || line[i] == ARG)
			break ;
	}
	str = kl_strdup_len(&line[start], i - start);
	dlst_add_front(s_lexems, dlst_new(str));
	if (line[i])
		return (i);
	return (i - 1);
}

int	parse__quote(t_dlst **s_lexems, char *line, int i,
					enum e_operators OPERATOR)
{
	int		start;
	char	*str;

	start = i + 1;
	while (line[++i])
	{
		if (line[i] == (int)OPERATOR)
			break ;
	}
	if (line[i])
	{
		str = kl_strdup_len(&line[start], i - start);
		dlst_add_front(s_lexems, dlst_new(str));
		return (i);
	}
	return (i - 1);
}

t_dlst	*parse_line_lexem(char *line)
{
	int		i;
	t_dlst	*s_lexems;

	i = -1;
	s_lexems = NULL;
	while (line[++i])
	{
		if (line[i] == SPACE)
			i = parse__spaces(&s_lexems, line, i);
		else if (line[i] == S_QUOTE)
			i = parse__quote(&s_lexems, line, i, S_QUOTE);
		else if (line[i] == D_QUOTE)
			i = parse__quote(&s_lexems, line, i, D_QUOTE);
		else
			i = parse__str(&s_lexems, line, i);
	}
	return (s_lexems);
}
