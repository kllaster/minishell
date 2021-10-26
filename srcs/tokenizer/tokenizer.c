#include "minishell.h"

int	add_fd(t_tokenizer *tknzer, int fd, char *file, int flags)
{
	int		fd_new;
	char	*error;

	fd_new = open(file, flags, 0644);
	if (fd_new == -1)
	{
		if (errno == ENOENT)
		{
			error = kl_strjoin_free(ft_strdup("no such file or directory: "),
					ft_strdup(file));
		}
		else
			error = ft_strdup(strerror(errno));
		ms_print(STDERR_FILENO, COLOR_RED, error);
		free(error);
		return (errno);
	}
	if (tknzer->fd_edited[fd])
		close(tknzer->cmd_now->fd[fd]);
	tknzer->cmd_now->fd[fd] = fd_new;
	tknzer->fd_edited[fd] = 1;
	return (0);
}

char	*get_filename(t_dlst *lexemes)
{
	t_operator	lexeme_type;
	char		*error;

	lexemes = lexemes->prev;
	if (lexemes == NULL)
		return (NULL);
	lexeme_type = ((t_lexeme *)lexemes->content)->type;
	if (lexeme_type == STR)
		return (((t_lexeme *)lexemes->content)->str);
	error = kl_strjoin_free(ft_strdup("syntax error near unexpected token "),
			ft_strdup((char *)&lexeme_type));
	ms_print(STDERR_FILENO, COLOR_RED, error);
	free(error);
	return (NULL);
}

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
			tknzer->cmd_now->fd[STDIN_FILENO] = tknzer->fd_pipe[STDIN_FILENO];
		tknzer->pipe = 0;
	}
	if (str)
	{
		tknzer->cmd_now->cmd
			= (char **)arr_add_back((void **)tknzer->cmd_now->cmd, str);
	}
}

int	lexer__iterator(t_dlst **tokens, t_dlst *lexemes, t_tokenizer *tknzer)
{
	t_operator	lexeme_type;
	char		*file;

	lexeme_type = ((t_lexeme *)lexemes->content)->type;
	if (lexeme_type == L_REDIR)
	{
		tknzer->stop_parse_str = 1;
		file = get_filename(lexemes);
		if (file == NULL)
			return (1);
		if (add_fd(tknzer, STDIN_FILENO, file, O_RDONLY) != 0)
			return (2);
		return (-1);
	}
	else if (lexeme_type == R_REDIR)
	{
		tknzer->stop_parse_str = 1;
		file = get_filename(lexemes);
		if (file == NULL)
			return (1);
		if (add_fd(tknzer, STDOUT_FILENO, file,
				O_CREAT | O_WRONLY | O_TRUNC) != 0)
			return (2);
		return (-1);
	}
	else if (lexeme_type == R_HEREDOC)
	{
		tknzer->stop_parse_str = 1;
		file = get_filename(lexemes);
		if (file == NULL)
			return (1);
		if (add_fd(tknzer, STDOUT_FILENO, file,
				O_CREAT | O_WRONLY | O_APPEND) != 0)
			return (2);
		return (-1);
	}
	else if (lexeme_type == L_HEREDOC)
	{
		tknzer->stop_parse_str = 1;
		// file = heredoc();
		// if (add_fd(tknzer, STDIN_FILENO, file, O_RDONLY) != 0)
		// 	return (2);
		return (-1);
	}
	else if (lexeme_type == STR)
	{
		if (tknzer->stop_parse_str == 1)
			create_cmd(tknzer, tokens, ((t_lexeme *)lexemes->content)->str);
		else
		{
			tknzer->cmd_now->cmd
				= (char **)arr_add_back((void **)tknzer->cmd_now->cmd,
					ft_strdup(((t_lexeme *)lexemes->content)->str));
		}
		return (0);
	}
	else if (lexeme_type == PIPE)
	{
		tknzer->pipe = 1;
		tknzer->stop_parse_str = 1;
		if (pipe(tknzer->fd_pipe) == -1)
		{
			ms_print(STDERR_FILENO, COLOR_RED, "error: creating pipe");
			return (4);
		}
		tknzer->cmd_now->fd[STDOUT_FILENO] = tknzer->fd_pipe[STDOUT_FILENO];
		return (0);
	}
	return (3);
}

t_dlst	*tokenize(t_dlst *lexemes)
{
	int			iteration;
	t_dlst		*tokens_res;
	t_dlst		**tokens;
	t_tokenizer	*tknzer;

	tknzer = kl_calloc(1, sizeof(t_tokenizer));
	tokens = kl_malloc(sizeof(t_dlst **));
	*tokens = NULL;
	create_cmd(tknzer, tokens, NULL);
	while (lexemes)
	{
		iteration = lexer__iterator(tokens, lexemes, tknzer);
		if (iteration > 0)
		{
			lexemes = dlst_last_node(lexemes);
			dlst_loop(lexemes);
			dlst_map(lexemes, free_lexeme);
			dlst_free(lexemes);
			*tokens = dlst_last_node(*tokens);
			if (*tokens)
			{
				dlst_loop(*tokens);
				dlst_map(*tokens, free_cmd);
				dlst_free(*tokens);
			}
			free(tokens);
			if (tknzer->cmd_now)
				free(tknzer->cmd_now);
			free(tknzer);
			return (NULL);
		}
		else if (iteration == -1)
			lexemes = lexemes->prev;
		if (lexemes)
			lexemes = lexemes->prev;
	}
	if (tknzer->cmd_now != NULL)
		dlst_add_front(tokens, dlst_new(tknzer->cmd_now));
	tokens_res = dlst_last_node(*tokens);
	free(tokens);
	free(tknzer);
	return (tokens_res);
}
