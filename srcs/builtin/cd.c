#include "minishell.h"

char *get_working_directory()
{
	char *path;

	path = kl_malloc(PATH_MAX);
	return getcwd(path, PATH_MAX);
}

int change_dir(char *path)
{
	char *env;
	char *error;
	char *oldpwd;

	oldpwd = get_working_directory();
	if (oldpwd == NULL)
	{
		error = ft_strjoin(path, ": ");
		error = kl_strjoin_free(error, ft_strdup(strerror(errno)));
		ms_print_cmd_error("cd", error);
		free(error);
		return (1);
	}

	if (chdir(path) == -1)
	{
		error = ft_strjoin(path, ": ");
		error = kl_strjoin_free(error, ft_strdup(strerror(errno)));
		ms_print_cmd_error("cd", error);
		free(oldpwd);
		free(error);
		return (1);
	}

	env = kl_strjoin_free(ft_strdup("OLDPWD="), oldpwd);
	g_envp = create_envp(g_envp, env);
	free(env);

	path = get_working_directory();
	if (path == NULL)
	{
		error = kl_strjoin_free(path, ft_strdup(": "));
		error = kl_strjoin_free(error, ft_strdup(strerror(errno)));
		ms_print_cmd_error("cd", error);
		free(error);
		return (1);
	}
	env = ft_strjoin("PWD=", path);
	g_envp = create_envp(g_envp, env);
	free(env);
	return (0);
}

int cd_to_home()
{
	int res;
	char *path;

	path = get_env("HOME");
	if (path == NULL)
	{
		ms_print(STDERR_FILENO, COLOR_RED, "cd: HOME not set");
		return (1);
	}
	res = change_dir(path);
	free(path);
	return (res);
}

int cd_to_old()
{
	int res;
	char *path;

	path = get_env("OLDPWD");
	if (path == NULL)
	{
		ms_print(STDERR_FILENO, COLOR_RED, "cd: OLDPWD not set");
		return (1);
	}
	res = change_dir(path);
	free(path);
	return (res);
}

int	cd_builtin(void *p)
{
	t_cmd	*s_cmd;

	s_cmd = p;
	if (s_cmd->cmd[1] && s_cmd->cmd[2])
	{
		ms_print(STDERR_FILENO, COLOR_RED, "cd: too many arguments");
		return (255);
	}
	if (s_cmd->cmd[1] == NULL || kl_strcmp(s_cmd->cmd[1], "~") == 0)
		return (cd_to_home());
	else if (kl_strcmp(s_cmd->cmd[1], "-") == 0)
		return (cd_to_old());
	return change_dir(s_cmd->cmd[1]);
}
