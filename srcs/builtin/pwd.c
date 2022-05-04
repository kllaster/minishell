#include "minishell.h"

int	pwd_builtin(void *p)
{
	char	*path;

	(void)p;
	path = get_working_directory();
	if (path)
	{
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		free(path);
	}
	else
	{
		ms_print_cmd_error("pwd", strerror(errno));
		return (1);
	}
	return (0);
}
