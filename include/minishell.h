#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "get_next_line.h"
# include "utils.h"
# include "parser.h"
# include "builtin.h"

enum	e_errors {
	ERROR_PARSE = 1,
	ERROR_SYSTEM = 2
};

# define COLOR_RED      "\x1b[31m"
# define COLOR_RED_B    "\x1b[1;31m"
# define COLOR_GREEN    "\x1b[32m"
# define COLOR_YELLOW   "\x1b[33m"
# define COLOR_YELLOW_B "\x1b[1;33m"
# define COLOR_BLUE     "\x1b[34m"
# define COLOR_MAGENTA  "\x1b[35m"
# define COLOR_CYAN     "\x1b[36m"
# define COLOR_CYAN_B   "\x1b[1;36m"
# define COLOR_RESET    "\x1b[0m"

char	**g_envp;

void	loop(void);

#endif //MINISHELL_H
