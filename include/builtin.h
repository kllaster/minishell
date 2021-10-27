#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int	cd_builtin(t_cmd *s_cmd);
int	exit_builtin(t_cmd *s_cmd);
int	echo_builtin(t_cmd *s_cmd);
int	pwd_builtin(t_cmd *s_cmd);
int	env_builtin(t_cmd *s_cmd);
int	unset_builtin(t_cmd *s_cmd);

#endif
