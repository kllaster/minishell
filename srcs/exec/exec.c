#include "minishell.h"

static void close_cmd_fd(t_cmd* s_cmd)
{
	if (s_cmd->fd[STDIN_FILENO] != STDIN_FILENO)
	{
		close(s_cmd->fd[STDIN_FILENO]);
		s_cmd->fd[STDIN_FILENO] = STDIN_FILENO;
	}
	if (s_cmd->fd[STDOUT_FILENO] != STDOUT_FILENO)
	{
		close(s_cmd->fd[STDOUT_FILENO]);
		s_cmd->fd[STDOUT_FILENO] = STDOUT_FILENO;
	}
}

static int exec_cmd(t_cmd* s_cmd)
{
	if (dup_fd(s_cmd->fd[0], STDIN_FILENO) != 0)
		return (errno);
	if (dup_fd(s_cmd->fd[1], STDOUT_FILENO) != 0)
		return (errno);

	if (s_cmd->fbuiltin)
		return (s_cmd->fbuiltin(s_cmd));
	else if (execve(s_cmd->exec_file, s_cmd->cmd, g_envp) == -1)
		return (errno);
	return (0);
}

static int exec_cmd_fork(t_cmd* s_cmd)
{
	int error;

	s_cmd->pid = fork();
	if (s_cmd->pid < 0)
	{
		ms_print_cmd_error("fork()", strerror(errno));
		return (errno);
	}
	else if (s_cmd->pid == 0)
		exit(exec_cmd(s_cmd));

	error = wait_process(s_cmd->pid);
	close_cmd_fd(s_cmd);
	return (error);
}

static int call_cmd(t_cmd* s_cmd)
{
	int res;
	int saved_fd[2];

	if (check_cmd(s_cmd) == 1)
		return (1);
	if (s_cmd->fbuiltin)
	{
		if (s_cmd->fbuiltin == exit_builtin)
		{
			g_exit = 1;
			g_exit_code = s_cmd->fbuiltin(s_cmd);
			res = 1;
		}
		else
		{
			saved_fd[0] = dup(0);
			saved_fd[1] = dup(1);
			res = exec_cmd(s_cmd);
			close_cmd_fd(s_cmd);
			if (dup_fd(saved_fd[0], STDIN_FILENO) != 0)
				return (errno);
			if (dup_fd(saved_fd[1], STDOUT_FILENO) != 0)
				return (errno);
		}
	}
	else
		res = exec_cmd_fork(s_cmd);
	return (res);
}

void run_cmds(t_dlst* tokens)
{
	t_cmd* s_cmd;

	while (tokens)
	{
		s_cmd = tokens->content;
		if (call_cmd(s_cmd) != 0)
			return;
		tokens = tokens->prev;
	}
}
