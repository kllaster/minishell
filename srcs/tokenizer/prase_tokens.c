#include "minishell.h"

void	create_cmd(t_tokenizer *tknzer, t_dlst **tokens, char *str)
{
	if (tknzer->cmd_now != NULL && tknzer->stop_parse_str == 1)
	{
		dlst_add_front(tokens, dlst_new(tknzer->cmd_now));
		tknzer->cmd_now = NULL;
	}
	if (tknzer->cmd_now == NULL)
	{
		tknzer->cmd_now = kl_calloc(1, sizeof(t_cmd));
		tknzer->cmd_now->fd[0] = STDIN_FILENO;
		tknzer->cmd_now->fd[1] = STDOUT_FILENO;
		tknzer->stop_parse_str = 0;
	}
	if (str)
	{
		tknzer->cmd_now->cmd
			= (char **)arr_add_back((void **)tknzer->cmd_now->cmd, str);
	}
}

int	set_redirect_back(int flags, t_dlst *lexemes, t_cmd *s_cmd)
{
	char	*path;

	path = get_str_lexeme(lexemes);
	if (path == NULL)
		return (1);
	s_cmd->fd_redir_stdin = create_fd(path, flags);
	return s_cmd->fd_redir_stdin == 0 ? 1 : -1;
}

int	redirect(int fd, int flags, t_dlst *lexemes, t_tokenizer *tknzer)
{
	char    *path;

	tknzer->stop_parse_str = 1;
	path = get_str_lexeme(lexemes);
	if (path == NULL)
		return (1);
	if (add_fd(tknzer->cmd_now, fd, path, flags) != 0)
		return (2);
	return (-1);
}

int	heredoc(int fd, t_dlst *lexemes)
{
	char	*delimiter;

	delimiter = get_str_lexeme(lexemes);
	if (delimiter == NULL)
		return (1);
	multiline_put_in_file(ms_put_heredoc, delimiter, fd);
	close(fd);
	return (0);
}
