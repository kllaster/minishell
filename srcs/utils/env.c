#include "minishell.h"

char	*get_env(char *key)
{
	int	i;
	int	len;

	if (g_envp == NULL)
		return (NULL);
	i = -1;
	len = ft_strlen(key);
	while (g_envp[++i] != NULL)
	{
		if (ft_strncmp(g_envp[i], key, len) == 0)
			return (ft_strchr(g_envp[i], '=') + 1);
	}
	return (NULL);
}
