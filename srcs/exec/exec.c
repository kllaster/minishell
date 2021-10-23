#include "minishell.h"

int	wait_processes(t_cmd *s_cmd)
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

void	exec_cmd(t_cmd *s_cmd)
{
	if (check_cmd(s_cmd) == 1)
		return ;
	s_cmd->pid = fork();
	if (s_cmd->pid < 0)
		kl_end("fork()", errno);
	else if (s_cmd->pid == 0)
	{
		if (dup2(s_cmd->fd[0], STDIN_FILENO) == -1)
			kl_end("dup2() STDIN", errno);
		if (dup2(s_cmd->fd[1], STDOUT_FILENO) == -1)
			kl_end("dup2() STDOUT", errno);
		if (execve(s_cmd->exec_file, s_cmd->cmd, g_envp) == -1)
			kl_end("execve()", errno);
		exit(0);
	}
	if (wait_processes(s_cmd) != 0 && s_cmd->error != 0)
	{
		ft_putstr_fd(COLOR_RED, 2);
		perror(NULL);
		ft_putstr_fd("\n", 2);
	}
}

void	run_cmds(t_dlst *lexemes)
{
	while (lexemes)
	{
		exec_cmd(lexemes->content);
		lexemes = lexemes->prev;
	}
}
