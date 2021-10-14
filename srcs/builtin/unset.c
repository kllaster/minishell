/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoyle <kdoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:21:14 by kdoyle            #+#    #+#             */
/*   Updated: 2021/10/14 09:06:19 by kdoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	symbol_position(char *str, int sym)
{
	int32_t	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == sym)
			return (i);
		++i;
	}
	return (-1);
}

static char	*find_envp_var(char *key, int len)
{
	int	i;
	int	sym;

	i = 0;
	while (g_envp[i])
	{
		if (!strncmp(g_envp[i], key, len))
		{
			if (check_key(g_envp[i], key))
			{
				sym = symbol_position(g_envp[i], '=');
				return (ft_substr(g_envp[i], sym + 1, ft_strlen(g_envp[i])));
			}
		}
		++i;
	}
	return (NULL);
}

static int	len_g_envp(void)
{
	int	i;

	i = 0;
	while (g_envp[i])
		i++;
	return (i);
}

char	**unset_builtin(char *key)
{
	char	**new;
	char	*find;
	int		i;
	int		j;

	i = 0;
	j = 0;
	find = find_envp_var(key, ft_strlen(key));
	if (!find)
		return (g_envp);
	new = (char **)ft_calloc(sizeof(char *), len_g_envp() + 1);
	while (g_envp[i])
	{
		if (!ft_strncmp(g_envp[i], key, ft_strlen(key))
			&& check_key(g_envp[i], key))
		{
			++i;
			continue ;
		}
		new[j] = ft_strdup(g_envp[i]);
		++i;
		++j;
	}
	return (new);
}
