#include "minishell.h"

static int	wait_processes(t_cmd *s_cmd)
{
	int		status;

	waitpid(s_cmd->pid, &status, WUNTRACED);
	if (s_cmd->fd[0] != STDIN_FILENO)
	{
		close(s_cmd->fd[0]);
		s_cmd->fd[0] = STDIN_FILENO;
	}
	if (s_cmd->fd[1] != STDOUT_FILENO)
	{
		close(s_cmd->fd[1]);
		s_cmd->fd[1] = STDOUT_FILENO;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		s_cmd->error = WTERMSIG(status);
		return (s_cmd->error);
	}
	return (0);
}

static int	exec_cmd(t_cmd *s_cmd)
{
	int	saved_fd[2];

	saved_fd[0] = dup(0);
	saved_fd[1] = dup(1);
	if (dup_fd(s_cmd->fd[0], STDIN_FILENO) != 0)
		return (errno);
	if (dup_fd(s_cmd->fd[1], STDOUT_FILENO) != 0)
		return (errno);
	if (s_cmd->fbuiltin)
		return (s_cmd->fbuiltin(s_cmd));
	else if (execve(s_cmd->exec_file, s_cmd->cmd, g_envp) == -1)
	{
		ms_print(STDERR_FILENO, COLOR_RED, "execve()");
		return (errno);
	}
	if (dup_fd(saved_fd[0], STDIN_FILENO) != 0)
		return (errno);
	if (dup_fd(saved_fd[1], STDOUT_FILENO) != 0)
		return (errno);
	return (0);
}

static int	exec_cmd_fork(t_cmd *s_cmd)
{
	s_cmd->pid = fork();
	if (s_cmd->pid < 0)
	{
		ms_print(STDERR_FILENO, COLOR_RED, "fork()");
		return (errno);
	}
	else if (s_cmd->pid == 0)
		exit(exec_cmd(s_cmd));
	if (wait_processes(s_cmd) != 0 && s_cmd->error != 0)
	{
		ms_print_cmd_error(s_cmd->cmd[0], strerror(errno));
		return (errno);
	}
	return (0);
}

static int	call_cmd(t_cmd *s_cmd)
{
	int	res;

	if (check_cmd(s_cmd) == 1)
		return (1);
	if (s_cmd->is_pipe == 0)
	{
		if (s_cmd->fbuiltin)
		{
			if (s_cmd->fbuiltin == exit_builtin)
			{
				g_exit = 1;
				g_exit_code = s_cmd->fbuiltin(s_cmd);
				res = 1;
			}
			else
				res = exec_cmd(s_cmd);
		}
		else
			res = exec_cmd_fork(s_cmd);
	}
	else
		res = exec_cmd_fork(s_cmd);
	return (res);
}

void	run_cmds(t_dlst *tokens)
{
	t_cmd	*s_cmd;

	while (tokens)
	{
		s_cmd = tokens->content;
		if (call_cmd(s_cmd) != 0)
			return ;
		tokens = tokens->prev;
	}
}
