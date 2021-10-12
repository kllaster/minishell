#include "minishell.h"

void	pwd_builtin(void)
{
	char	*path;

	path = get_env("PWD");
	if (path)
	{
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
		ms_print(STDERR_FILENO, COLOR_RED, "environment variable is not set");
}
