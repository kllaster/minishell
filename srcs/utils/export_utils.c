/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoyle <kdoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 08:47:41 by kdoyle            #+#    #+#             */
/*   Updated: 2021/10/14 09:14:36 by kdoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**realloc_2d_array(char **arr, int start_from)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)ft_calloc(sizeof(char *), len_of_2d_array(arr) + 2);
	while (arr && arr[i])
	{
		new[i + start_from] = ft_strdup(arr[i]);
		++i;
	}
	new[i + start_from] = NULL;
	free_2d_array(arr);
	return (new);
}

static int	len_of_2d_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr || !arr[0])
		return (i);
	while (arr[i])
		++i;
	return (i);
}

char	**add_last_to_2d_array(char **args, char *new_arg)
{
	char	**new_args;
	int		len;

	len = len_of_2d_array(args);
	new_args = realloc_2d_array(args, 0);
	new_args[len] = ft_strdup(new_arg);
	return (new_args);
}
