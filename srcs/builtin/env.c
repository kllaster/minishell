#include "minishell.h"

int	env_builtin(t_cmd *s_cmd)
{
	int	i;

	(void)s_cmd;
	i = -1;
	while (g_envp[++i])
	{
		ft_putstr_fd(g_envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return (0);
}
