#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_envp = envp;
	loop();
	return (0);
}
