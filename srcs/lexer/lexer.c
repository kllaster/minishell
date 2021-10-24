#include "minishell.h"

int	add_fd(t_lexer *lexer, int fd, char *file, int flags)
{
	int		fd_new;
	char	*error;

	fd_new = open(file, flags, 0644);
	if (fd_new == -1)
	{
		error = kl_strjoin_free(ft_strdup("no such file or directory: "),
				ft_strdup(file));
		ms_print(STDERR_FILENO, COLOR_RED, error);
		free(error);
		return (errno);
	}
	lexer->cmd_now->fd[fd] = fd_new;
	lexer->fd_edited[fd] = 1;
	return (0);
}

char	*get_filename(t_dlst *tokens)
{
	t_operator	token_type;
	char		*error;

	tokens = tokens->prev;
	if (tokens == NULL)
		return (NULL);
	token_type = ((t_token *)tokens->content)->type;
	if (token_type == STR)
		return (((t_token *)tokens->content)->str);
	error = kl_strjoin_free(ft_strdup("syntax error near unexpected token "),
			ft_strdup((char *)&token_type));
	ms_print(STDERR_FILENO, COLOR_RED, error);
	free(error);
	return (NULL);
}

void	create_cmd(t_lexer *lexer, t_dlst **lexemes, char *str)
{
	if (lexer->cmd_now != NULL && lexer->stop_parse_str == 1)
	{
		dlst_add_front(lexemes, dlst_new(lexer->cmd_now));
		lexer->cmd_now = NULL;
	}
	if (lexer->cmd_now == NULL)
	{
		lexer->cmd_now = kl_calloc(1, sizeof(t_cmd));
		lexer->cmd_now->fd[0] = STDIN_FILENO;
		lexer->cmd_now->fd[1] = STDOUT_FILENO;
		lexer->stop_parse_str = 0;
		if (lexer->pipe)
			lexer->cmd_now->fd[STDIN_FILENO] = lexer->fd_pipe[STDIN_FILENO];
		lexer->pipe = 0;
	}
	if (str)
	{
		lexer->cmd_now->cmd
			= (char **)kl_add_to_arr((void **)lexer->cmd_now->cmd, str);
	}
}

int	lexer__iterator(t_dlst **lexemes, t_dlst *tokens, t_lexer *lexer)
{
	t_operator	token_type;
	char		*file;

	token_type = ((t_token *)tokens->content)->type;
	if (token_type == L_REDIR)
	{
		lexer->stop_parse_str = 1;
		file = get_filename(tokens);
		if (file == NULL)
			return (1);
		lexer->fd_edited[STDIN_FILENO] = 1;
		if (add_fd(lexer, STDIN_FILENO, file, O_RDONLY) != 0)
			return (2);
		return (-1);
	}
	else if (token_type == R_REDIR)
	{
		lexer->stop_parse_str = 1;
		file = get_filename(tokens);
		if (file == NULL)
			return (1);
		lexer->fd_edited[STDOUT_FILENO] = 1;
		if (add_fd(lexer, STDOUT_FILENO, file,
				O_CREAT | O_WRONLY | O_TRUNC) != 0)
			return (2);
		return (-1);
	}
	else if (token_type == R_HEREDOC)
	{
		lexer->stop_parse_str = 1;
		file = get_filename(tokens);
		if (file == NULL)
			return (1);
		lexer->fd_edited[STDOUT_FILENO] = 1;
		if (add_fd(lexer, STDOUT_FILENO, file,
				O_CREAT | O_WRONLY | O_APPEND) != 0)
			return (2);
		return (-1);
	}
	else if (token_type == L_HEREDOC)
	{
		lexer->stop_parse_str = 1;
		// file = heredoc();
		// lexer->fd_edited[STDIN_FILENO] = 1;
		// if (add_fd(lexer, STDIN_FILENO, file, O_RDONLY) != 0)
		// 	return (2);
		return (-1);
	}
	else if (token_type == STR)
	{
		if (lexer->stop_parse_str == 1)
			create_cmd(lexer, lexemes, ((t_token *)tokens->content)->str);
		else
		{
			lexer->cmd_now->cmd
				= (char **)kl_add_to_arr((void **)lexer->cmd_now->cmd,
					ft_strdup(((t_token *)tokens->content)->str));
		}
		return (0);
	}
	else if (token_type == PIPE)
	{
		lexer->pipe = 1;
		lexer->stop_parse_str = 1;
		if (pipe(lexer->fd_pipe) == -1)
			kl_end("pipe()", errno);
		lexer->cmd_now->fd[STDOUT_FILENO] = lexer->fd_pipe[STDOUT_FILENO];
		return (0);
	}
	return (3);
}

t_dlst	*lexer(t_dlst *tokens)
{
	int		iteration;
	t_lexer	*lexer;
	t_dlst	**lexemes;
	t_dlst	*lexemes_res;

	lexer = kl_calloc(1, sizeof(t_lexer));
	lexemes = kl_malloc(sizeof(t_dlst **));
	*lexemes = NULL;
	create_cmd(lexer, lexemes, NULL);
	while (tokens)
	{
		iteration = lexer__iterator(lexemes, tokens, lexer);
		if (iteration > 0)
		{
			tokens = dlst_last_node(tokens);
			dlst_loop(tokens);
			dlst_map(tokens, free_token);
			dlst_free(tokens);
			*lexemes = dlst_last_node(*lexemes);
			if (*lexemes)
			{
				dlst_loop(*lexemes);
				dlst_map(*lexemes, free_cmd);
				dlst_free(*lexemes);
			}
			free(lexemes);
			free(lexer);
			return (NULL);
		}
		else if (iteration == -1)
			tokens = tokens->prev;
		if (tokens)
			tokens = tokens->prev;
	}
	if (lexer->cmd_now != NULL)
		dlst_add_front(lexemes, dlst_new(lexer->cmd_now));
	lexemes_res = dlst_last_node(*lexemes);
	free(lexemes);
	free(lexer);
	return (lexemes_res);
}
