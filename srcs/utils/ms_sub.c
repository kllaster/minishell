#include "minishell.h"

void	ms_print(int fd, char *color, char *str)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(color, fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	ft_putstr_fd(COLOR_RESET, fd);
}

void	ms_print_tokens(t_dlst *dlst_item)
{
	t_token	*token;

	while (dlst_item)
	{
		token = dlst_item->content;
		ft_putstr_fd("---> ", STDOUT_FILENO);
		ft_putchar_fd(token->type, STDOUT_FILENO);
		ft_putstr_fd(" <---> ", STDOUT_FILENO);
		ft_putstr_fd("\\", STDOUT_FILENO);
		if (token->str)
			ft_putstr_fd(token->str, STDOUT_FILENO);
		else
			ft_putchar_fd(token->type, STDOUT_FILENO);
		ft_putstr_fd("/", STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		dlst_item = dlst_item->prev;
	}
}

void	ms_put_tag(void)
{
	ft_putstr_fd(COLOR_RED_B, STDERR_FILENO);
	ft_putstr_fd(" ϟ ", STDERR_FILENO);
	ft_putstr_fd(COLOR_CYAN_B, STDERR_FILENO);
	ft_putstr_fd("minishell", STDERR_FILENO);
	ft_putstr_fd(COLOR_YELLOW_B, STDERR_FILENO);
	ft_putstr_fd(" ∞ ", STDERR_FILENO);
	ft_putstr_fd(COLOR_RESET, STDERR_FILENO);
}
