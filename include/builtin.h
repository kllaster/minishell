#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

enum e_options {
	ZERO_OPTION = 0,
	FIND_OPTION = 1,
	NOT_OPTION = 2
};

enum e_exit_ret {
	SUCCESS = 0,
	ER_COUN_ARG = 1

};

enum e_cd_options {
	NO_FLAGS = 0,
	FAIL_CD = 1,
	SUCCESS_CD = 0,
	MINUS = 2
};

int		cd_builtin(char *argv[]);
int		exit_builtin(char *argv[]);
void	echo_builtin(char *argv[]);
void	pwd_builtin(void);
void	env_builtin();

#endif
