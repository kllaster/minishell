#include "minishell.h"

void	run_line(char *line)
{
	t_dlst	*s_lexems;

	s_lexems = parse_line_lexem(line);
	dlst_end(&s_lexems);
	ft_putstr_fd("Lexems: \n", 2);
	dlst_map(s_lexems, ms_print_lexem);
	dlst_map(s_lexems, free);
}

int	check_duplicate_char(char *line, char c)
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

void	ms_put_tag(void)
{
	ft_putstr_fd(COLOR_RED_B, STDERR_FILENO);
	ft_putstr_fd("➜ ", STDERR_FILENO);
	ft_putstr_fd(COLOR_CYAN_B, STDERR_FILENO);
	ft_putstr_fd("minishell ", STDERR_FILENO);
	ft_putstr_fd(COLOR_YELLOW_B, STDERR_FILENO);
	ft_putstr_fd("✗ ", STDERR_FILENO);
	ft_putstr_fd(COLOR_RESET, STDERR_FILENO);
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
