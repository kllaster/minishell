#include "minishell.h"

void	run_line(char *line)
{
	t_dlst	*dlst_lexemes;

	dlst_lexemes = parse_lexem(line);
	dlst_lexemes = validation_lexemes(dlst_lexemes);
	ft_putstr_fd("lexemes valid: \n", 2);
	ms_print_lexem(dlst_lexemes);
	dlst_loop(&dlst_lexemes);
	dlst_map(dlst_lexemes, free);
}

int	check_duplicate_char(const char *line, char c)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != c)
			break ;
	}
	if (line[i] == '\0')
		return (1);
	return (0);
}

int	check_syntax(char *line)
{
	if (ft_strnstr(line, "|", 1) != 0)
	{
		ms_print(STDERR_FILENO, COLOR_RED,
			"syntax error near unexpected token '|'");
		return (1);
	}
	else if (ft_strnstr(line, ";", 1) != 0)
	{
		ms_print(STDERR_FILENO, COLOR_RED,
			"syntax error near unexpected token ';'");
		return (1);
	}
	else if (check_duplicate_char(line, ' '))
		return (1);
	return (0);
}

void	loop(void)
{
	int		i;
	char	*line;
	char	**cmds;

	line = NULL;
	ms_put_tag();
	while (get_next_line(0, &line) > 0)
	{
		if (check_syntax(line) == 0)
		{
			cmds = ft_split(line, ';');
			i = -1;
			while (cmds[++i])
				run_line(cmds[i]);
			kl_free_arr(cmds);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		ms_put_tag();
		free(line);
	}
}
