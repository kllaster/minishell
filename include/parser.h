#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

enum e_operators
{
	S_QUOTE = '\'',
	D_QUOTE = '"',
	L_REDIR = '<',
	R_REDIR = '>',
	DL_REDIR,
	DR_REDIR,
	PIPE = '|'
};

enum e_operands
{
	T_PROG,
	T_FILE,
	T_FD,
	T_ARG
};

void	parse_line_tokens(char *line);

char	*get_env(char *key);

#endif //PARSER_H
