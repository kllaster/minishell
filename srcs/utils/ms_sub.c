#include "minishell.h"

void ms_print(int fd, char* color, char* str)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(color, fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n" COLOR_RESET, fd);
}

void ms_print_lexemes(t_dlst* dlst_item)
{
	t_lexeme* lexeme;

	while (dlst_item)
	{
		lexeme = dlst_item->content;
		ft_putstr_fd("---> ", STDERR_FILENO);
		ft_putchar_fd(lexeme->type, STDERR_FILENO);
		ft_putstr_fd(" <---> ", STDERR_FILENO);
		ft_putstr_fd("\\", STDERR_FILENO);
		if (lexeme->str)
			ft_putstr_fd(lexeme->str, STDERR_FILENO);
		else
			ft_putchar_fd(lexeme->type, STDERR_FILENO);
		ft_putstr_fd("/", STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		dlst_item = dlst_item->prev;
	}
}

void ms_put_tag(void)
{
	ft_putstr_fd(COLOR_RED_B "ϟ "
	             COLOR_CYAN_B "minishell"
	             COLOR_YELLOW_B " ∞ " COLOR_RESET,
		STDERR_FILENO);
}

void ms_put_heredoc(void)
{
	ft_putstr_fd(COLOR_BLUE "heredoc> " COLOR_RESET, STDERR_FILENO);
}

void ms_print_cmd_error(char* cmd_name, char* error_str)
{
	char* error;

	error = kl_strjoin_free(ft_strdup(cmd_name), ft_strdup(" - "));
	error = kl_strjoin_free(error, ft_strdup(error_str));
	ms_print(STDERR_FILENO, COLOR_RED, error);
	free(error);
}

void ms_print_welcome()
{
	ft_putstr_fd(COLOR_YELLOW_B
	             "\n"
	             "███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████╗ ██╗  ██╗ ███████╗ ██╗      ██╗     \n"
	             "████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════╝ ██║  ██║ ██╔════╝ ██║      ██║     \n"
	             "██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████╗ ███████║ █████╗   ██║      ██║     \n"
	             "██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██║ ██╔══██║ ██╔══╝   ██║      ██║     \n"
	             "██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████║ ██║  ██║ ███████╗ ███████╗ ███████╗\n"
	             "╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════╝ ╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n\n"
	             "The default interactive shell is now minishell.\n"
	             COLOR_RESET,
		STDERR_FILENO);
}
