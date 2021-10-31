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
		if (ft_strncmp(g_envp[i], key, len) == 0 && g_envp[i][len] == '=')
			return (ft_strdup(ft_strchr(g_envp[i], '=') + 1));
	}
	return (NULL);
}

int	check_new_env(char **envp, char *item)
{
	int	i;
	int	check_new;
	int	len;

	i = 0;
	check_new = -1;
	if (item == NULL)
		return (-1);
	item[ft_strichr(item, '=')] = '\0';
	len = ft_strlen(item);
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], item, len) == 0 && g_envp[i][len] == '=')
		{
			check_new = i;
			break ;
		}
		++i;
	}
	item[len] = '=';
	return (check_new);
}

static char	**put_envp(char **envp, char **new_envp,
					int check_new, char *item)
{
	int	i;

	i = -1;
	while (envp && envp[++i] != NULL)
	{
		if (i == check_new)
			new_envp[i] = ft_strdup(item);
		else
			new_envp[i] = ft_strdup(envp[i]);
	}
	if (item && check_new == -1)
	{
		new_envp[i] = ft_strdup(item);
		new_envp[i + 1] = NULL;
	}
	else
		new_envp[i] = NULL;
	return (new_envp);
}

char	**create_envp(char **envp, char *item)
{
	int		i;
	int		check_new;
	char	**new_envp;

	i = 0;
	check_new = check_new_env(envp, item);
	while (envp && envp[i] != NULL)
		++i;
	if (item && check_new == -1)
		i += 1;
	new_envp = kl_malloc(sizeof(char *) * (i + 1));
	put_envp(envp, new_envp, check_new, item);
	if (item != NULL && envp)
		kl_free_arr(envp);
	return (new_envp);
}
