#include "minishell.h"

int	unset_builtin(void *p)
{
	int		a;
	int		check_new;
	char	**new_envp;
	char	*key_name;
	t_cmd	*s_cmd;

	a = -1;
	s_cmd = p;
	while (s_cmd->cmd[++a])
	{
		key_name = kl_strjoin_free(ft_strdup(s_cmd->cmd[a]), ft_strdup("="));
		check_new = check_new_env(g_envp, key_name);
		free(key_name);
		if (check_new == -1)
			continue ;
		new_envp = (char **)arr_remove_el((void **)g_envp, check_new);
		g_envp = new_envp;
	}
	return (0);
}
