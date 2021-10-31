#include "minishell.h"

static int	error_output(char *str)
{
	char	*error;

	error = kl_strjoin_free(ft_strdup("exit: "), ft_strdup(str));
	error = kl_strjoin_free(error, ft_strdup(": numeric argument required"));
	ms_print(STDERR_FILENO, COLOR_RED, error);
	free(error);
	return (255);
}

int	exit_builtin(void *p)
{
	int		i;
	t_cmd	*s_cmd;

	s_cmd = p;
	if (s_cmd->cmd[1] && s_cmd->cmd[2])
	{
		ms_print(STDERR_FILENO, COLOR_RED, "exit: too many arguments");
		return (1);
	}
	if (s_cmd->cmd[1])
	{
		i = -1;
		while (s_cmd->cmd[1][++i])
		{
			if (!ft_isdigit(s_cmd->cmd[1][i]))
				return (error_output(s_cmd->cmd[1]));
		}
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		return (ft_atoi(s_cmd->cmd[1]));
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	return (0);
}
