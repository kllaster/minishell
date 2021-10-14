/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoyle <kdoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 00:38:30 by kdoyle            #+#    #+#             */
/*   Updated: 2021/10/14 08:34:04 by kdoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	change_dir_env(char *key, char *value, int len)
{
	char	*newway;
	int		i;

	i = -1;
	while (g_envp[++i])
	{
		if (!strncmp(g_envp[i], key, len))
		{
			if (check_key(g_envp[i], key))
			{
				newway = ft_strjoin(ft_strdup(key), ft_strdup("="));
				newway = ft_strjoin(ft_strdup(newway), ft_strdup(value));
				free(g_envp[i]);
				g_envp[i] = newway;
				return (SUCCESS_CD);
			}
		}
	}
	return (SUCCESS_CD);
}

int	chdir_check(char *path, char *pwd)
{
	int	ret;

	ret = chdir(path);
	if (ret != 0)
	{
		ms_print(STDERR_FILENO, COLOR_RED, strerror(errno));
		return (FAIL_CD);
	}
	change_dir_env("OLDPWD", &pwd[4], 6);
	change_dir_env("PWD", path, 3);
	return (ret);
}
