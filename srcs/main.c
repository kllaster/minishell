#include "minishell.h"

int main(int argc, char** argv, char** envp)
{
	(void)argc;
	(void)argv;
	if (read(0, NULL, 0) == -1)
		return (0);
	init_shell();
	signal(SIGINT, &signal_int);
	signal(SIGQUIT, &signal_quit);
	g_envp = create_envp(envp, NULL);
	ms_print_welcome();
	loop();
	if (g_envp)
		kl_free_arr(g_envp);
	return (get_shell_exit_code());
}
