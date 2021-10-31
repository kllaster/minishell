#include "minishell.h"

static int	tokenize__logic_pipe(t_tokenizer *tknzer)
{
	tknzer->pipe = 1;
	tknzer->stop_parse_str = 1;
	if (pipe(tknzer->fd_pipe) == -1)
	{
		ms_print(STDERR_FILENO, COLOR_RED, "error: creating pipe");
		return (4);
	}
	tknzer->fd_edited[STDOUT_FILENO] = 1;
	tknzer->cmd_now->fd[STDOUT_FILENO] = tknzer->fd_pipe[STDOUT_FILENO];
	tknzer->cmd_now->is_pipe = 1;
	return (0);
}

static int	tokenize__logic_str(t_dlst **tokens, t_dlst *lexemes,
								t_tokenizer *tknzer)
{
	if (tknzer->cmd_now == NULL || tknzer->stop_parse_str == 1)
	{
		create_cmd(tknzer, tokens,
			ft_strdup(((t_lexeme *)lexemes->content)->str));
	}
	else
	{
		tknzer->cmd_now->cmd
			= (char **)arr_add_back((void **)tknzer->cmd_now->cmd,
				ft_strdup(((t_lexeme *)lexemes->content)->str));
	}
	return (0);
}

static int	tokenize__logic_heredoc(t_dlst *lexemes, t_tokenizer *tknzer)
{
	tknzer->stop_parse_str = 1;
	if (heredoc(lexemes) != 0)
		return (1);
	if (add_fd(tknzer, STDIN_FILENO, ".heredoc", O_RDONLY) != 0)
		return (2);
	return (-1);
}

int	tokenize__logic(t_dlst **tokens, t_dlst *lexemes, t_tokenizer *tknzer)
{
	t_operator	lexeme_type;

	lexeme_type = ((t_lexeme *)lexemes->content)->type;
	if (lexeme_type == L_REDIR)
		return (redirect(STDIN_FILENO, O_RDONLY, lexemes, tknzer));
	else if (lexeme_type == R_REDIR)
	{
		return (redirect(STDOUT_FILENO,
				O_CREAT | O_WRONLY | O_TRUNC, lexemes, tknzer));
	}
	else if (lexeme_type == R_HEREDOC)
	{
		return (redirect(STDOUT_FILENO,
				O_CREAT | O_WRONLY | O_APPEND, lexemes, tknzer));
	}
	else if (lexeme_type == L_HEREDOC)
		return (tokenize__logic_heredoc(lexemes, tknzer));
	else if (lexeme_type == STR)
		return (tokenize__logic_str(tokens, lexemes, tknzer));
	else if (lexeme_type == PIPE)
		return (tokenize__logic_pipe(tknzer));
	return (3);
}
