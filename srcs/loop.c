#include "minishell.h"

static void	run_line(char *line)
{
	t_dlst	*lexemes;
	t_dlst	*tokens;

	lexemes = parse_lexemes(line);
	if (lexemes == NULL)
		return ;
	lexemes = loop_vars(lexemes);
	if (lexemes == NULL)
		return ;
	tokens = tokenize(lexemes);
	if (tokens == NULL)
		return ;
	run_cmds(tokens);
	dlst_loop(lexemes);
	dlst_map(lexemes, free_lexeme);
	dlst_free(lexemes);
	dlst_loop(tokens);
	dlst_map(tokens, free_cmd);
	dlst_free(tokens);
}

static int	check_syntax(char *line)
{
	if (ft_strnstr(line, "|", 1) != 0)
	{
		if (ft_strnstr(line, "||", 2) != 0)
			ms_print(STDERR_FILENO, COLOR_RED,
				"syntax error near unexpected token '||'");
		else
			ms_print(STDERR_FILENO, COLOR_RED,
				"syntax error near unexpected token '|'");
		return (1);
	}
	else if (ft_strnstr(line, ";", 1) != 0)
	{
		if (ft_strnstr(line, ";;", 2) != 0)
			ms_print(STDERR_FILENO, COLOR_RED,
				"syntax error near unexpected token ';;'");
		else
			ms_print(STDERR_FILENO, COLOR_RED,
				"syntax error near unexpected token ';'");
		return (1);
	}
	return (0);
}

static void	parse_line(char *line)
{
	int		i;
	char	**cmds;

	line = ft_strtrim(line, "\t ");
	if (line && check_syntax(line) == 0)
	{
		cmds = ft_split(line, ';');
		i = -1;
		while (cmds[++i])
		{
			run_line(cmds[i]);
			if (g_exit)
				break ;
		}
		kl_free_arr(cmds);
	}
	free(line);
}

void	loop(void)
{
	char	**line;

	line = kl_malloc(sizeof(char *));
	ms_put_tag();
	while (get_next_line(0, line) > 0)
	{
		if (**line == '\0')
		{
			ms_put_tag();
			free(*line);
			continue ;
		}
		parse_line(*line);
		free(*line);
		if (g_exit)
			break ;
		ms_put_tag();
	}
	free(line);
}
