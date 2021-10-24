#include "minishell.h"

static int	check_not_n(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

int	echo_builtin(t_cmd *s_cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (s_cmd->cmd[++i])
	{
		if (s_cmd->cmd[i][0] == '-' && flag != 2
			&& check_not_n(s_cmd->cmd[i]) == 0)
		{
			flag = 1;
			continue ;
		}
		else
		{
			if (flag == 2)
				write(1, " ", 1);
			flag = 2;
			ft_putstr_fd(s_cmd->cmd[i], STDOUT_FILENO);
		}
	}
	if (flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
