#include "minishell.h"

int wait_process(pid_t pid)
{
	int status;

	waitpid(pid, &status, WUNTRACED);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (0);
}

int dup_fd(int fd_new, int fd_old)
{
	if (fd_new != fd_old && dup2(fd_new, fd_old) == -1)
		return (errno);
	return (0);
}
