#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

typedef struct s_cmd
{
	pid_t			pid;
	int				fd[2];
	int				error;
	char			*exec_file;
	char			**cmd;
}				t_cmd;

typedef struct s_tokenizer
{
	t_cmd			*cmd_now;
	int				pipe;
	int				fd_pipe[2];
	int				fd_edited[2];
	int				stop_parse_str;
}				t_tokenizer;

void	free_cmd(void *p);
int		check_cmd(t_cmd *s_cmd);
void	run_cmds(t_dlst *tokens);
t_dlst	*tokenize(t_dlst *lexemes);

#endif
