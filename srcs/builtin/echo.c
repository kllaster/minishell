/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdoyle <kdoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:17:36 by kdoyle            #+#    #+#             */
/*   Updated: 2021/10/14 00:44:20 by kdoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_not_n(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

static void	output(int flag, char *str)
{
	if (flag == NOT_OPTION)
		write(1, " ", 1);
	ft_putstr_fd(str, STDOUT_FILENO);
}

void	echo_builtin(char *argv[])
{
	int	i;
	int	flag;

	flag = ZERO_OPTION;
	if (!argv[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	i = 0;
	while (argv[++i])
	{
		if (argv[i][0] == '-' && !check_not_n(argv[i]) && flag != NOT_OPTION)
		{
			flag = FIND_OPTION;
			continue ;
		}
		else
		{
			output(flag, argv[i]);
			flag = NOT_OPTION;
		}
	}
	if (flag == ZERO_OPTION)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
