#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

enum e_options {
	ZERO_OPTION = 0,
	FIND_OPTION = 1,
	NOT_OPTION = 2
};

void	echo_builtin(char *argv[]);

#endif