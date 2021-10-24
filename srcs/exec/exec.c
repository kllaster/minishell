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

int	exec_cmd(t_cmd *s_cmd)
{
	char	*error;

	if (check_cmd(s_cmd) == 1)
		return (1);
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
		error = kl_strjoin_free(ft_strdup(s_cmd->cmd[0]), ft_strdup(": "));
		error = kl_strjoin_free(error, ft_strdup(strerror(errno)));
		ms_print(STDERR_FILENO, COLOR_RED, error);
		free(error);
		return (errno);
	}
	return (0);
}

void	run_cmds(t_dlst *lexemes)
{
	int		res;
	t_cmd	*s_cmd;

	while (lexemes)
	{
		s_cmd = lexemes->content;
		if (ft_strncmp(s_cmd->cmd[0], "cd", ft_strlen(s_cmd->cmd[0])) == 0)
			res = cd_builtin(s_cmd);
		else if (ft_strncmp(s_cmd->cmd[0], "exit", ft_strlen(s_cmd->cmd[0])) == 0)
		{
			g_exit = 1;
			res = exit_builtin(s_cmd);
			g_exit_code = res;
			break ;
		}
		else if (ft_strncmp(s_cmd->cmd[0], "echo", ft_strlen(s_cmd->cmd[0])) == 0)
			res = echo_builtin(s_cmd);
		// else if (ft_strncmp(s_cmd->cmd[0], "pwd", ft_strlen(s_cmd->cmd[0])) == 0)
		// 	res = pwd_builtin(s_cmd);
		else if (ft_strncmp(s_cmd->cmd[0], "env", ft_strlen(s_cmd->cmd[0])) == 0)
			res = env_builtin(s_cmd);
		// else if (ft_strncmp(s_cmd->cmd[0], "unset", ft_strlen(s_cmd->cmd[0])) == 0)
		// 	res = unset_builtin(s_cmd);
		// else if (ft_strncmp(s_cmd->cmd[0], "export", ft_strlen(s_cmd->cmd[0])) == 0)
		// 	res = export_builtin(s_cmd);
		else
			res = exec_cmd(s_cmd);
		if (res != 0)
			return ;
		lexemes = lexemes->prev;
	}
}
