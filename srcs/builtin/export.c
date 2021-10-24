#include "minishell.h"

static int	not_valid_identifier(char *str)
{
	ms_print(STDERR_FILENO, COLOR_RED, "export");
	ms_print(STDERR_FILENO, COLOR_RED, str);
	ms_print(STDERR_FILENO, COLOR_RED, "not a valid identifier");
	return (1);
}

static void	sort_2d_array(char **arr)
{
	char	*temp;
	int		len;
	int		i;
	int		j;

	len = len_of_2d_array(arr);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - 1)
		{
			if (ft_strncmp(arr[j], arr[j + 1], strlen(arr[j])) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			++j;
		}
		++i;
	}
}

static void	print_with_declare(char **sorted_env)
{
	int	i;

	i = 0;
	while (*sorted_env != NULL)
	{
		write(1, "declare -x ", 12);
		i = 0;
		while ((*sorted_env)[i] != 0 && (*sorted_env)[i] != '=')
		{
			write(1, &(*sorted_env)[i], 1);
			i++;
		}
		if ((*sorted_env)[i] != '=')
		{
			write(1, "\n", 1);
			sorted_env++;
			continue ;
		}
		write(1, &(*sorted_env)[i++], 1);
		write(1, "\"", 1);
		while ((*sorted_env)[i])
			write(1, &(*sorted_env)[i++], 1);
		write(1, "\"\n", 2);
		sorted_env++;
	}
}

static int	export_no_args(char **env)
{
	char	**sorted_env;

	sorted_env = copy_2d_array(env);
	sort_2d_array(sorted_env);
	print_with_declare(sorted_env);
	free_2d_array(sorted_env);
	return (1);
}

int	export_builtin(char **args)
{
	char	**key_value;
	char	*env_str;

	if (!args[1])
		return (export_no_args(g_envp));
	if (args[1][0] == '=')
		return (not_valid_identifier(args[1]));
	key_value = ft_split(args[1], '=');
	if (key_value[0] && !key_value[1])
	{
		g_envp = add_last_to_2d_array(g_envp, key_value[0]);
		return (SUCCESS);
	}
	if (!change_dir_env(key_value[0], key_value[1], ft_strlen(key_value[0])))
	{
		env_str = ft_strjoin(key_value[0], ft_strdup("="));
		env_str = ft_strjoin(env_str, key_value[1]);
		g_envp = add_last_to_2d_array(g_envp, env_str);
		free(env_str);
		free(key_value[1]);
		free(key_value);
	}
	return (SUCCESS);
}
