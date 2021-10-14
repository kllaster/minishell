/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoyle <kdoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:21:07 by kdoyle            #+#    #+#             */
/*   Updated: 2021/10/14 00:44:20 by kdoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(void)
{
	char	*path;

	path = get_env("PWD");
	if (path)
	{
		ft_putstr_fd(path, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
		ms_print(STDERR_FILENO, COLOR_RED, "environment variable is not set");
}
