#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <string.h>
# include "libft.h"
# include "get_next_line.h"
# include "utils.h"
# include "tokenizer.h"
# include "lexer.h"
# include "builtin.h"

int		g_exit;
int		g_exit_code;
char	**g_envp;

void	loop(void);
void	run_cmds(t_dlst *tokens);

#endif
