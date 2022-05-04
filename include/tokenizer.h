#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "minishell.h"

typedef int	(*t_fbuiltin)(void *);

typedef struct s_cmd
{
	int             is_piped;
	int             pipe_fd;
	int             return_pipe_fd;
	int				fd[2];
	int				fd_redir_stdin;
	char			*exec_file;
	char			**cmd;
	t_fbuiltin		fbuiltin;
}				t_cmd;

typedef struct s_tokenizer
{
	t_cmd			*cmd_now;
	int				stop_parse_str;
}				t_tokenizer;

void	free_cmd(void *p);
void	create_cmd(t_tokenizer *tknzer, t_dlst **tokens, char *str);
void	multiline_put_in_file(void print_tag(void), char *delimiter, int fd);
void	free_tokenizer(t_dlst **tokens, t_dlst *lexemes, t_tokenizer *tknzer);
char	*get_str_lexeme(t_dlst *lexemes);
int		check_cmd(t_cmd *s_cmd);
int		heredoc(int fd, t_dlst *lexemes);

int     create_fd(char *path, int flags);
int		add_fd(t_cmd *s_cmd, int fd, char *path, int flags);
int		redirect(int fd, int flags, t_dlst *lexemes, t_tokenizer *tknzer);
int     set_redirect_back(int flags, t_dlst *lexemes, t_cmd *s_cmd);

int		tokenize__logic(t_dlst **tokens, t_dlst *lexemes, t_tokenizer *tknzer);
t_dlst	*tokenize(t_dlst *lexemes);

#endif
