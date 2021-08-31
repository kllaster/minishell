#include "minishell.h"

void	kl_end(char *str, int exit_code)
{
	if (str != NULL)
	{
		ft_putstr_fd(COLOR_RED, STDERR_FILENO);
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(COLOR_GREEN, STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		ft_putstr_fd(COLOR_RESET, STDERR_FILENO);
	}
	exit(exit_code);
}

void	*kl_malloc(size_t size)
{
	void	*p;

	p = malloc(size * 2);
	if (p == NULL)
		kl_end("kl_malloc()", ERROR_SYSTEM);
	return (p);
}

void	kl_free_arr(void *arr)
{
	int	i;

	i = 0;
	while (((char **)arr)[i] != NULL)
	{
		free(((char **)arr)[i]);
		i++;
	}
	free(arr);
}
