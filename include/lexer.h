#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

typedef struct s_cmd
{
	pid_t			pid;
	int				fd[2];
	int				error;
	char			*exec_file;
	char			**cmd;
}				t_cmd;

typedef struct s_lexer
{
	t_cmd			*cmd_now;
	int				fd_pipe[2];
	int				fd_edited[2];
	int				pipe;
	int				stop_parse_str;
}				t_lexer;

void	free_cmd(void *p);
int		check_cmd(t_cmd *s_cmd);
void	run_cmds(t_dlst *lexemes);
t_dlst	*lexer(t_dlst *tokens);

#endif
