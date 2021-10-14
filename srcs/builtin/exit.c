/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoyle <kdoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:21:01 by kdoyle            #+#    #+#             */
/*   Updated: 2021/10/14 00:52:01 by kdoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_output(char *str)
{
	ft_putstr_fd("exit: ", STDOUT_FILENO);
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd(": numeric argument required", STDOUT_FILENO);
	return (255);
}

int	exit_builtin(char *argv[])
{
	int	i;

	i = -1;
	if (argv[1] && argv[2])
	{
		ms_print(STDERR_FILENO, COLOR_RED, "bash: exit: too many arguments");
		return (ER_COUN_ARG);
	}
	while (argv[1][++i])
	{
		if (!ft_isdigit(argv[1][i]))
			return (error_output(argv[1]));
	}
	if (argv[1])
		return (ft_atoi(argv[1]));
	else
		return (SUCCESS);
}
