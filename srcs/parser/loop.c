#include "minishell.h"

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
	char	*msg;

	msg = NULL;
	if (ft_strnstr(line, "|", 1) != 0)
	{
		msg = ft_strdup("syntax error near unexpected token '|'");
		ms_print(STDERR_FILENO, COLOR_RED, msg);
		free(msg);
	}
	else if (ft_strnstr(line, ";", 1) != 0)
	{
		msg = ft_strdup("syntax error near unexpected token ';'");
		ms_print(STDERR_FILENO, COLOR_RED, msg);
		free(msg);
	}
	else if (check_duplicate_char(line, ' '))
		msg = "0";
	if (msg != NULL)
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
	char	*line;

	line = NULL;
	ms_put_tag();
	while (get_next_line(0, &line) > 0)
	{
		if (check_syntax(line) == 0)
			parse_line_tokens(line);
		ms_put_tag();
		free(line);
	}
}
