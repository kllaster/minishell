#include "minishell.h"

static void	check_path(char	**exec_file, t_cmd *s_cmd)
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

t_fbuiltin	is_builtin(char *str)
{
	if (kl_strcmp(str, "cd") == 0)
		return (cd_builtin);
	else if (kl_strcmp(str, "exit") == 0)
		return (exit_builtin);
	else if (kl_strcmp(str, "echo") == 0)
		return (echo_builtin);
	else if (kl_strcmp(str, "pwd") == 0)
		return (pwd_builtin);
	else if (kl_strcmp(str, "env") == 0)
		return (env_builtin);
	else if (kl_strcmp(str, "unset") == 0)
		return (unset_builtin);
	return (NULL);
}

int	check_cmd(t_cmd *s_cmd)
{
	char	**exec_file;
	char	**exec_file_p;

	s_cmd->fbuiltin = is_builtin(s_cmd->cmd[0]);
	if (s_cmd->fbuiltin)
		return (0);
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
	ms_print_cmd_error(s_cmd->cmd[0], "command not found");
	return (1);
}
