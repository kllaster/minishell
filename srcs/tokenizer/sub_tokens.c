#include "minishell.h"

void	free_cmd(void *p)
{
	t_cmd	*s_cmd;

	s_cmd = p;
	if (s_cmd->fd[STDIN_FILENO] != STDIN_FILENO)
		close(s_cmd->fd[STDIN_FILENO]);
	if (s_cmd->fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(s_cmd->fd[STDOUT_FILENO]);
	if (s_cmd->exec_file)
		free(s_cmd->exec_file);
	kl_free_arr(s_cmd->cmd);
	free(s_cmd);
}
