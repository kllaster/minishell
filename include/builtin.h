#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		cd_builtin(void *s_cmd);
int		exit_builtin(void *s_cmd);
int		echo_builtin(void *s_cmd);
int		pwd_builtin(void *s_cmd);
int		env_builtin(void *s_cmd);
int		unset_builtin(void *s_cmd);

char    *get_working_directory();

#endif
