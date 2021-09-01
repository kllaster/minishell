#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

enum e_operators
{
	ARG		= '$',
	SPACE	= ' ',
	S_QUOTE	= '\'',
	D_QUOTE = '"',
	L_REDIR = '<',
	R_REDIR = '>',
	DL_REDIR,
	DR_REDIR,
	PIPE	= '|'
};

typedef struct s_cmd
{
	pid_t			pid;
	int				fd[2];
	int				error;
	char			*exec_file;
	char			**cmd;
}				t_cmd;

t_dlst	*parse_line_lexem(char *line);

char	*get_env(char *key);

#endif //PARSER_H
