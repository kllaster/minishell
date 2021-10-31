#include "minishell.h"

int	dup_fd(int fd_new, int fd_old)
{
	if (fd_new != fd_old && dup2(fd_new, fd_old) == -1)
	{
		ms_print(STDERR_FILENO, COLOR_RED, "dup2() ");
		return (errno);
	}
	return (0);
}
