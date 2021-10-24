#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include <string.h>

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
	TOHOME = 0,
	HAVEWAY = 3,
	FAIL_CD = 1,
	SUCCESS_CD = 0,
	MINUS = 2
};

int		cd_builtin(char *argv[]);
int		change_dir_env(char *key, char *value, int len);
int		chdir_check(char *path, char *pwd);
int		check_key(char *env, char *key);
int		exit_builtin(char *argv[]);
void	echo_builtin(char *argv[]);
void	pwd_builtin(void);
void	env_builtin(void);
char	**unset_builtin(char *key);
int		export_builtin(char **args);
char	**add_last_to_2d_array(char **args, char *new_arg);
int		len_of_2d_array(char **arr);
char	**copy_2d_array(char **arr);
void	free_2d_array(char **arr);

#endif
