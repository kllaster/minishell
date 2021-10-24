#include "minishell.h"

void	env_builtin(void)
{
	int	i;

	i = -1;
	while (g_envp[++i] && g_envp[i + 1])
	{
		ft_putstr_fd(g_envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
