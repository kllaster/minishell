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
		ft_bzero(&tknzer->fd_edited, sizeof(int) * 2);
		tknzer->stop_parse_str = 0;
		if (tknzer->pipe)
		{
			tknzer->fd_edited[STDIN_FILENO] = 1;
			tknzer->cmd_now->fd[STDIN_FILENO] = tknzer->fd_pipe[STDIN_FILENO];
			tknzer->cmd_now->is_pipe = 1;
		}
		tknzer->pipe = 0;
	}
	if (str)
	{
		tknzer->cmd_now->cmd
			= (char **)arr_add_back((void **)tknzer->cmd_now->cmd, str);
	}
}

int	redirect(int fd, int falgs, t_dlst *lexemes, t_tokenizer *tknzer)
{
	char	*file;

	tknzer->stop_parse_str = 1;
	file = get_filename(lexemes);
	if (file == NULL)
		return (1);
	if (add_fd(tknzer, fd, file, falgs) != 0)
		return (2);
	return (-1);
}

int	heredoc(t_dlst *lexemes)
{
	int		fd;
	char	*delimiter;

	delimiter = get_filename(lexemes);
	if (delimiter == NULL)
		return (1);
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 755);
	if (fd == -1)
	{
		ms_print(STDERR_FILENO, COLOR_RED, "no such file .heredoc");
		return (errno);
	}
	multiline_put_in_file(ms_put_heredoc, delimiter, fd);
	close(fd);
	return (0);
}
