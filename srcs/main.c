#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_exit = 0;
	g_exit_code = 0;
	g_envp = create_envp(envp, NULL);
	ms_print_welcome();
	loop();
	if (g_envp)
		kl_free_arr(g_envp);
	return (g_exit_code);
}
