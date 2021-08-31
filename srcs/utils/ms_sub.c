#include "minishell.h"

void	ms_print(int fd, char *color, char *str)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(color, fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd(COLOR_RESET, fd);
}
