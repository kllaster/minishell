/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoyle <kdoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:20:53 by kdoyle            #+#    #+#             */
/*   Updated: 2021/10/14 00:44:20 by kdoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(void)
{
	int	i;

	i = -1;
	while (g_envp[++i] && g_envp[i + 1])
	{
		ft_putstr_fd(g_envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
