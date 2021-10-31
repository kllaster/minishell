#include "minishell.h"

static t_list_var	loop_vars__iterator(t_dlst *lexemes, t_dlst *prev)
{
	t_dlst		*temp;
	t_list_var	list;

	list.var2 = prev;
	if (((t_lexeme *)lexemes->content)->type == STR
		&& ((t_lexeme *)lexemes->content)->str[0] == '\0')
	{
		temp = lexemes->next;
		free_lexeme(lexemes->content);
		dlst_remove_node(lexemes);
		list.var1 = temp;
	}
	else
	{
		list.var2 = lexemes;
		list.var1 = lexemes->next;
	}
	return (list);
}

t_dlst	*loop_vars(t_dlst *lexemes)
{
	t_dlst		*prev;
	t_list_var	list;

	prev = NULL;
	while (lexemes)
	{
		if (((t_lexeme *)lexemes->content)->type == SET_VAR)
		{
			lexemes = parse__var(lexemes->content, lexemes);
			prev = lexemes;
		}
		else
		{
			list = loop_vars__iterator(lexemes, prev);
			lexemes = list.var1;
			prev = list.var2;
		}
	}
	lexemes = dlst_last_node(prev);
	return (lexemes);
}

static char	*join_var_str(char *str, int end_var, char *res)
{
	char	*value;
	char	end_symb;

	end_symb = str[end_var];
	str[end_var] = '\0';
	value = get_env(str);
	if (value)
		res = kl_strjoin_free(res, value);
	str[end_var] = end_symb;
	return (res);
}

static void	join_var__iterator(char *str, t_join_var *s_jv)
{
	char	*temp;

	if (s_jv->end_prev_var != s_jv->start_var)
	{
		str[s_jv->start_var] = '\0';
		temp = s_jv->res;
		s_jv->res = ft_strjoin(s_jv->res, str + s_jv->end_prev_var);
		free(temp);
		str[s_jv->start_var] = VAR;
	}
	s_jv->end_var = s_jv->start_var + 1;
	while (str[s_jv->end_var] && str[s_jv->end_var] != VAR
		&& str[s_jv->end_var] != SPACE)
		++s_jv->end_var;
	s_jv->res
		= join_var_str(str + s_jv->start_var + 1,
			s_jv->end_var - s_jv->start_var - 1,
			s_jv->res);
	s_jv->end_prev_var = s_jv->end_var;
	s_jv->start_var = ft_strichr(str + s_jv->end_var, VAR);
	if (s_jv->start_var != -1)
		s_jv->start_var += s_jv->end_var;
}

t_lexeme	*join_var(char *str, int start_var)
{
	char		*temp;
	t_join_var	*s_jv;

	s_jv = kl_malloc(sizeof(t_join_var));
	ft_bzero(s_jv, sizeof(t_join_var));
	s_jv->res = ft_strdup("");
	s_jv->start_var = start_var;
	while (s_jv->start_var >= 0)
		join_var__iterator(str, s_jv);
	if (str[s_jv->end_var])
	{
		temp = s_jv->res;
		s_jv->res = ft_strjoin(s_jv->res, str + s_jv->end_var);
		free(temp);
	}
	free(str);
	return (new_lexeme(STR, s_jv->res));
}
