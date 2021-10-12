#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_envp = create_envp(envp, NULL);
	loop();
	if (g_envp)
		kl_free_arr(g_envp);
	return (0);
}
