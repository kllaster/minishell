#include "minishell.h"

void	check_path(char	**exec_file, t_cmd *s_cmd)
{
	char	*tmp_path;
	char	*tmp_path2;

	while (s_cmd->exec_file == NULL && exec_file && *exec_file)
	{
		tmp_path2 = ft_strjoin(*exec_file, "/");
		tmp_path = ft_strjoin(tmp_path2, s_cmd->cmd[0]);
		free(tmp_path2);
		if (!access(tmp_path, 1))
			s_cmd->exec_file = ft_strdup(tmp_path);
		free(tmp_path);
		exec_file++;
	}
}

int	check_cmd(t_cmd *s_cmd)
{
	char	*error;
	char	**exec_file;
	char	**exec_file_p;

	exec_file_p = NULL;
	if (ft_strchr(s_cmd->cmd[0], '/') != NULL)
	{
		if (ft_strncmp(s_cmd->cmd[0], "./", 2) == 0)
			s_cmd->exec_file = ft_strdup(s_cmd->cmd[0] + 2);
		else
			s_cmd->exec_file = ft_strdup(s_cmd->cmd[0]);
		return (0);
	}
	if (g_envp)
		exec_file_p = ft_split(get_env("PATH"), ':');
	exec_file = exec_file_p;
	check_path(exec_file, s_cmd);
	kl_free_arr(exec_file_p);
	if (s_cmd->exec_file)
		return (0);
	error = kl_strjoin_free(ft_strdup("command not found: "),
			ft_strdup(s_cmd->cmd[0]));
	ms_print(STDERR_FILENO, COLOR_RED, error);
	return (1);
}
