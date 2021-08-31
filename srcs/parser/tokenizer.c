#include "minishell.h"

void	parse_line_tokens(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		ft_putchar_fd(line[i], STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}
