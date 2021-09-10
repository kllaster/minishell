#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum e_operators
{
	ARG		= '$',
	SPACE	= ' ',
	TAB		= '\t',
	S_QUOTE	= '\'',
	D_QUOTE = '"',
	L_REDIR = '<',
	R_REDIR = '>',
	DL_REDIR,
	DR_REDIR,
	PIPE	= '|',
	STR
}			t_operator;

typedef struct s_lexeme
{
	t_operator	type;
	char		*str;
}				t_lexeme;

typedef struct s_cmd
{
	pid_t			pid;
	int				fd[2];
	int				error;
	char			*exec_file;
	char			**cmd;
}				t_cmd;

void		join_lexeme_str(t_lexeme *lexeme, t_dlst *dlts_item);

int			parse__str(t_dlst **lexemes, const char *line, int i);
int			parse__spaces(t_dlst **lexemes, const char *line, int i);
int			parse__operator(t_dlst **lexemes, int i, t_operator type);
int			parse__quote(t_dlst **lexemes, const char *line,
				int i, t_operator type);
t_dlst		*parse_lexeme(char *line);

t_lexeme	*new_lexeme(t_operator type, char *str);
void		free_lexeme(void *lexeme);

char		*get_env(char *key);

#endif
