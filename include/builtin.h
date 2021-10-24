#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <string.h>

enum e_options {
	ZERO_OPTION = 0,
	FIND_OPTION = 1,
	NOT_OPTION = 2
};

int	cd_builtin(t_cmd *s_cmd);
int	exit_builtin(t_cmd *s_cmd);
int	echo_builtin(t_cmd *s_cmd);
// void	pwd_builtin(t_cmd *s_cmd);
// void	env_builtin(t_cmd *s_cmd);
// char	**unset_builtin(t_cmd *s_cmd);
// int		export_builtin(t_cmd *s_cmd);

int		change_dir_env(char *key, char *value, int len);
int		check_key(char *env, char *key);
char	**add_last_to_2d_array(char **args, char *new_arg);
int		len_of_2d_array(char **arr);
char	**copy_2d_array(char **arr);
void	free_2d_array(char **arr);

#endif
