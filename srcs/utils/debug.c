#include "minishell.h"

void	ms_print_lexem(void *str)
{
	ft_putstr_fd("---> ", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}
