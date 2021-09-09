#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include "utils.h"
# include "parser.h"
# include "builtin.h"

char	**g_envp;

void	loop(void);

#endif
