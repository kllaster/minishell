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

int	char_iterator(char *str, int flag)
{
	if (str[0] == '-' && flag != 2
		&& check_not_n(str) == 0)
	{
		flag = 1;
	}
	else
	{
		if (flag == 2)
			ft_putchar_fd(' ', STDOUT_FILENO);
		if (flag == 0)
			flag = 2;
		ft_putstr_fd(str, STDOUT_FILENO);
	}
	return (flag);
}

int	echo_builtin(void *p)
{
	int		i;
	int		flag;
	t_cmd	*s_cmd;

	i = 0;
	flag = 0;
	s_cmd = p;
	while (s_cmd->cmd[++i])
		flag = char_iterator(s_cmd->cmd[i], flag);
	if (flag != 1)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
