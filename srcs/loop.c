#include "minishell.h"

void	run_line(char *line)
{
	t_dlst	*tokens;

	tokens = parse_tokens(line);
	if (tokens == NULL)
		return ;
	tokens = loop_vars(tokens);
	if (tokens == NULL)
		return ;
	ft_putstr_fd("tokens valid: \n", STDOUT_FILENO);
	ms_print_tokens(tokens);
	ft_putchar_fd('\n', STDOUT_FILENO);
	dlst_loop(tokens);
	dlst_map(tokens, free_token);
	dlst_free(tokens);
}

int	check_syntax(char *line)
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

void	loop(void)
{
	int		i;
	char	*line;
	char	*trimmed_line;
	char	**cmds;

	line = NULL;
	ms_put_tag();
	while (get_next_line(0, &line) > 0)
	{
		trimmed_line = ft_strtrim(line, "\t ");
		free(line);
		line = trimmed_line;
		if (line[0] && check_syntax(line) == 0)
		{
			cmds = ft_split(line, ';');
			i = -1;
			while (cmds[++i])
				run_line(cmds[i]);
			kl_free_arr(cmds);
		}
		ms_put_tag();
		free(line);
	}
}
