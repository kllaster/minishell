#include "minishell.h"

static int	path_check(char *path, char *pwd, char *arg)
{
	int		res;
	char	*env;
	char	*error;

	res = chdir(path);
	if (res != 0)
	{
		error = kl_strjoin_free(ft_strdup(arg), ft_strdup(": "));
		error = kl_strjoin_free(error, ft_strdup(strerror(errno)));
		ms_print_cmd_error("cd", error);
		free(error);
		return (res);
	}
	env = kl_strjoin_free(ft_strdup("OLDPWD="), pwd);
	g_envp = create_envp(g_envp, env);
	free(env);
	env = kl_strjoin_free(ft_strdup("PWD="), path);
	g_envp = create_envp(g_envp, env);
	free(env);
	return (res);
}

static char	*get_path(char *arg, char *pwd)
{
	char	*path;
	char	**dirs;

	if (arg == NULL)
	{
		path = get_env("HOME");
		if (path == NULL)
		{
			free(pwd);
			ms_print(STDERR_FILENO, COLOR_RED, "cd: HOME not set");
			return (NULL);
		}
	}
	else
	{
		dirs = ft_split(arg, '/');
		path = make_absolute_path(dirs, ft_strdup(pwd));
		kl_free_arr(dirs);
	}
	return (path);
}

int	cd_builtin(void *p)
{
	char	*pwd;
	char	*path;
	t_cmd	*s_cmd;

	s_cmd = p;
	if (s_cmd->cmd[1] && s_cmd->cmd[2])
	{
		ms_print(STDERR_FILENO, COLOR_RED, "cd: too many arguments");
		return (255);
	}
	pwd = get_env("PWD");
	path = get_path(s_cmd->cmd[1], pwd);
	if (path == NULL)
		return (1);
	return (path_check(path, pwd, s_cmd->cmd[1]));
}
