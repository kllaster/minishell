#include "minishell.h"

int	pwd_builtin(void *p)
{
	char	*path;

	(void)p;
	path = get_env("PWD");
	if (path)
	{
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
	{
		ms_print(STDERR_FILENO, COLOR_RED,
			"pwd: environment variable is not set");
		return (1);
	}
	return (0);
}
