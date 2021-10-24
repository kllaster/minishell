#include "minishell.h"

int	pwd_builtin(t_cmd *s_cmd)
{
	char	*path;

	(void)s_cmd;
	path = get_env("PWD");
	if (path)
	{
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
	{
		ms_print(STDERR_FILENO, COLOR_RED, "pwd: environment variable is not set");
		return (1);
	}
	return (0);
}
