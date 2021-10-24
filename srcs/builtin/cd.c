#include "minishell.h"

int	check_key(char *env, char *key)
{
	int	i;

	i = 0;
	while (env[i] != '=')
		++i;
	if (i != ft_strlen(key))
		return (0);
	return (1);
}

static char	*cut_pwd(char *pwd)
{
	int		i;
	char	*res;

	i = ft_strlen(pwd) - 1;
	while (pwd[i] && pwd[i] != '/')
		--i;
	if (pwd[i])
	{
		if (pwd[i] == '/' && i == 0)
			res = ft_strdup("/");
		else
			res = ft_substr(pwd, 0, i);
		return (res);
	}
	return (NULL);
}

static char	*make_valid_string(char **dirs, char *pwd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (dirs[i])
	{
		if (!ft_strncmp(dirs[i], "..", ft_strlen(dirs[i])))
		{
			tmp = cut_pwd(pwd);
			if (tmp)
			{
				free(pwd);
				pwd = tmp;
			}
		}
		else if (!ft_strncmp(dirs[i], ".", ft_strlen(dirs[i])))
		{
			++i;
			continue ;
		}
		else
			pwd = ft_strjoin(ft_strjoin(pwd, ft_strdup("/")), dirs[i]);
		++i;
	}
	return (pwd);
}

static int	got_to_path(int setting, char *way)
{
	char	*path;
	char	*pwd;
	char	**dirs;

	pwd = get_env("PWD");
	if (setting == TOHOME)
	{
		path = get_env("HOME");
		if (path == NULL)
		{
			ms_print(STDERR_FILENO, COLOR_RED, "minishell: cd: HOME not set");
			return (FAIL_CD);
		}
		return (chdir_check(path, pwd));
	}
	else if (setting == HAVEWAY)
	{
		dirs = ft_split(way, '/');
		path = make_valid_string(dirs, ft_strdup(&pwd[4]));
		return (chdir_check(path, pwd));
	}
	return (SUCCESS_CD);
}

int	cd_builtin(char *argv[])
{
	if (!argv[1])
		return (got_to_path(TOHOME, argv[1]));
	else if (argv[1])
		return (got_to_path(HAVEWAY, argv[1]));
	return (0);
}
