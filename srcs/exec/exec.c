#include "minishell.h"

static void close_cmd_fd(t_cmd* s_cmd)
{
	if (s_cmd->fd[STDIN_FILENO] != STDIN_FILENO)
	{
		if (close(s_cmd->fd[STDIN_FILENO]) == -1)
			ms_print_cmd_error("close()", strerror(errno));
		s_cmd->fd[STDIN_FILENO] = STDIN_FILENO;
	}
	if (s_cmd->fd[STDOUT_FILENO] != STDOUT_FILENO)
	{
		if (close(s_cmd->fd[STDOUT_FILENO]) == -1)
			ms_print_cmd_error("close()", strerror(errno));
		s_cmd->fd[STDOUT_FILENO] = STDOUT_FILENO;
	}
}

static int exec_cmd(t_cmd* s_cmd)
{
	if (s_cmd->fd[STDIN_FILENO] != STDIN_FILENO)
	{
		if (dup2(s_cmd->fd[STDIN_FILENO], STDIN_FILENO) == -1)
			return (errno);
	}
	else if (s_cmd->pipe_fd)
	{
		if (dup_fd(s_cmd->pipe_fd, STDIN_FILENO) != 0)
			return (errno);
	}
	if (dup_fd(s_cmd->fd[STDOUT_FILENO], STDOUT_FILENO) != 0)
		return (errno);

	if (s_cmd->fbuiltin)
		return (s_cmd->fbuiltin(s_cmd));
	else if (execve(s_cmd->exec_file, s_cmd->cmd, g_envp) == -1)
		return (errno);
	return (0);
}

static int create_pipe_first(t_cmd* s_cmd)
{
	int fd[2];

	if (s_cmd->is_piped && s_cmd->fd[STDOUT_FILENO] == STDOUT_FILENO)
	{
		if (pipe(fd) == -1)
		{
			ms_print_cmd_error("pipe()", strerror(errno));
			return (errno);
		}
		s_cmd->return_pipe_fd = fd[STDIN_FILENO];
		s_cmd->fd[STDOUT_FILENO] = fd[STDOUT_FILENO];
	}
	return (0);
}

static int create_pipe_second(t_cmd* s_cmd)
{
	int fd[2];

	if (s_cmd->is_piped && s_cmd->return_pipe_fd == 0
	    && s_cmd->fd[STDOUT_FILENO] != STDOUT_FILENO)
	{
		if (pipe(fd) == -1)
		{
			ms_print_cmd_error("pipe()", strerror(errno));
			return (errno);
		}
		s_cmd->return_pipe_fd = fd[STDIN_FILENO];
		if (dup_fd(s_cmd->fd[STDOUT_FILENO], fd[STDOUT_FILENO]) != 0)
			return (errno);
	}
	return (0);
}

static int exec_cmd_fork(t_cmd* s_cmd)
{
	int code;
	pid_t pid;

	if (create_pipe_first(s_cmd) != 0)
		return (errno);
	pid = fork();
	set_shell_pid(pid);
	if (pid < 0)
	{
		ms_print_cmd_error("fork()", strerror(errno));
		return (errno);
	}
	else if (pid == 0)
		exit(exec_cmd(s_cmd));

	code = wait_process(pid);
	set_shell_pid(0);
	if (code == 0 && create_pipe_second(s_cmd) != 0)
		return (errno);
	close_cmd_fd(s_cmd);
	return (code);
}

static int call_cmd(t_cmd* s_cmd)
{
	int res;
	int saved_fd[2];

	if (check_cmd(s_cmd) == 1)
	{
		set_shell_pcode(127);
		return (1);
	}
	if (s_cmd->fbuiltin)
	{
		if (s_cmd->fbuiltin == exit_builtin)
		{
			set_shell_exit(s_cmd->fbuiltin(s_cmd));
			return (1);
		}
		else
		{
			saved_fd[0] = dup(0);
			saved_fd[1] = dup(1);
			if (create_pipe_first(s_cmd) != 0)
				return (errno);
			res = exec_cmd(s_cmd);
			set_shell_pcode(res);
			if (res == 0 && create_pipe_second(s_cmd) != 0)
				return (errno);
			close_cmd_fd(s_cmd);
			if (dup_fd(saved_fd[0], STDIN_FILENO) != 0)
				return (errno);
			if (dup_fd(saved_fd[1], STDOUT_FILENO) != 0)
				return (errno);
		}
	}
	else
	{
		res = exec_cmd_fork(s_cmd);
		if (!shell_pcode_is_signal())
			set_shell_pcode(res);
		else
			set_shell_is_signal(0);
	}
	return (res);
}

void run_cmds(t_dlst* tokens)
{
	int pipe_fd_in;
	t_cmd* s_cmd;

	pipe_fd_in = 0;
	while (tokens)
	{
		s_cmd = tokens->content;
		if (pipe_fd_in != 0)
		{
			s_cmd->pipe_fd = pipe_fd_in;
			pipe_fd_in = 0;
		}
		if (call_cmd(s_cmd) != 0)
			return;
		if (s_cmd->is_piped)
			pipe_fd_in = s_cmd->return_pipe_fd;
		tokens = tokens->prev;
	}
}
