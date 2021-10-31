#include "minishell.h"

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

static char	*make_absolute_path_iterator(char *dir, char *path)
{
	char	*tmp;

	if (ft_strncmp(dir, ".", ft_strlen(dir)) == 0)
		path = kl_strjoin_free(path, ft_strdup("/./"));
	else if (ft_strncmp(dir, "..", ft_strlen(dir)) == 0)
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
		path = ft_strjoin(tmp, dir);
		free(tmp);
	}
	return (path);
}

char	*make_absolute_path(char **dirs, char *pwd)
{
	int		i;
	char	*path;

	i = -1;
	path = pwd;
	if (dirs[0] && dirs[0][0] == '\0')
		path = ft_strdup("/");
	while (dirs[++i])
		path = make_absolute_path_iterator(dirs[i], path);
	return (path);
}
