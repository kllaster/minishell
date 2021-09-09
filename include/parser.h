#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

enum e_operators
{
	S_QUOTE,
	D_QUOTE,
	L_REDIR,
	R_REDIR,
	DL_REDIR,
	DR_REDIR,
	PIPE
};

enum e_operands
{
	PROG,
	FILE,
	FD,
	ARG
};

#endif