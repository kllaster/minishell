#include "builtin.h"

static int	check_not_n(char *str)
{
	int	i;

	i = 0;
	while(str[++i])
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

int	echo_builtin(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!argv[i])
	{
		write(1, '\n', 1);
		return (0);
	}
	while (argv[i])
	{
		if (argv[i][1] == '-' && !check_not_n(argv[i]))
		{
			return (0);
		}
	}
	return (0);
}
