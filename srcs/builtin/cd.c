#include "minishell.h"

static int	chdir_check(char *path, char *pwd, char *arg)
{
	int		res;
	char	*env;
	char	*error;

	res = chdir(path);
	if (res != 0)
	{
		error = kl_strjoin_free(ft_strdup("cd: "), ft_strdup(arg));
		error = kl_strjoin_free(error, ft_strdup(": "));
		error = kl_strjoin_free(error, ft_strdup(strerror(errno)));
		ms_print(STDERR_FILENO, COLOR_RED, error);
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

static char	*cut_path(char *path)
{
	int		i;
	char	*res;

	i = ft_strlen(path) - 1;
	while (path[i] && path[i] != '/')
		--i;
	if (path[i])
	{
		if (path[i] == '/' && i == 0)
			res = ft_strdup("/");
		else
			res = ft_substr(path, 0, i);
		return (res);
	}
	return (NULL);
}

static char	*make_absolute_path(char **dirs, char *pwd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = -1;
	path = pwd;
	if (dirs[0] && dirs[0][0] == '\0')
		path = ft_strdup("/");
	while (dirs[++i])
	{
		if (ft_strncmp(dirs[i], ".", ft_strlen(dirs[i])) == 0)
			path = kl_strjoin_free(path, ft_strdup("/./"));
		else if (ft_strncmp(dirs[i], "..", ft_strlen(dirs[i])) == 0)
		{
			tmp = cut_path(path);
			free(path);
			path = tmp;
		}
		else
		{
			tmp = path;
			if (path[ft_strlen(path) - 1] != '/')
				tmp = kl_strjoin_free(path, ft_strdup("/"));
			path = ft_strjoin(tmp, dirs[i]);
			free(tmp);
		}
	}
	return (path);
}

int	cd_builtin(t_cmd *s_cmd)
{
	char	*path;
	char	*pwd;
	char	**dirs;

	if (s_cmd->cmd[1] && s_cmd->cmd[2])
	{
		ms_print(STDERR_FILENO, COLOR_RED, "cd: too many arguments");
		return (255);
	}
	pwd = get_env("PWD");
	if (s_cmd->cmd[1] == NULL)
	{
		path = get_env("HOME");
		if (path == NULL)
		{
			free(pwd);
			ms_print(STDERR_FILENO, COLOR_RED, "cd: HOME not set");
			return (1);
		}
	}
	else
	{
		dirs = ft_split(s_cmd->cmd[1], '/');
		path = make_absolute_path(dirs, ft_strdup(pwd));
		kl_free_arr(dirs);
	}
	return (chdir_check(path, pwd, s_cmd->cmd[1]));
}
