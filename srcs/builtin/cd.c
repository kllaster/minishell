#include "minishell.h"

static void	change_dir_env(char *path, char *pwd)
{
	
}

static int	got_to_path(int setting, char *way)
{
	char	*path;
	char	*pwd;
	char	**directories;

	path = get_env("HOME");
	pwd = get_env("PWD");
	if (setting == NO_FLAGS)
	{
		if (path == NULL)
		{
			ms_print(STDERR_FILENO, COLOR_RED, "minishell: cd: HOME not set");
			return(FAIL_CD);
		}
		
		return(SUCCESS_CD);
	}
	directories = ft_split(way, '/');
	return (SUCCESS_CD);
}

int	cd_builtin(char *argv[])
{
	if (!argv[1])
		return(got_to_path(NO_FLAGS, argv[1]));
	else if (argv[1][0] == '-')
		return(got_to_path(MINUS, argv[1]));
	return(0);
}